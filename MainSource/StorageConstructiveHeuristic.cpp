#include<cmath>
#include<iomanip>
#include<algorithm> 
#include<exception> 
#include "Heuristic.h"
#include "Warehouse.h"
#include "DistanceMatrix.h"
#include "OptimizationConstraints.h"
#include "OptimizationParameters.h"
#include "StorageConstructiveHeuristic.h"
#include "ProductAllocationProhibition.h"
#include "WarehouseToGraphConverter.h" 
#include "StorageSolutionEvaluator.h"
#include "IsolatedFamily.h"
#include "TSP.h"
using std::map;
using std::vector;
using std::queue;
using std::make_pair;
using std::min;
using namespace QuickTSP; 

StorageConstructiveHeuristic::StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh, const DistanceMatrix<Vertex> *distMatrix,
														   map<Position, Vertex>& vertexByCell, vector<Order> &orders, OptimizationConstraints &cons){
	this->distanceMatrix = distMatrix; 
	this->warehouse = &wh; 
	this->orders= orders; 
	this->constraints = cons; 
	this->products = prods; 	
	this->vertexByCell = vertexByCell; 
	
	InitializeAuxiliaryDataStructures(); 
}

void StorageConstructiveHeuristic::InitializeAuxiliaryDataStructures(){

	vector<IsolatedFamily> isolatedFamiliesList = constraints.getIsolatedFamilies(); 
	vector<ProductAllocationProhibitions> prohibitions = constraints.getProductAllocationProhibitions();

	//Initialize isolated families structures
	for(const auto& isolatedFamily : isolatedFamiliesList){
		familyIsolationsByFamilyCode[isolatedFamily.getCode()] = isolatedFamily;
		isolatedFamilies.insert(isolatedFamily.getCode());
	}		

	//Initialize product allocation prohibitions structures 
	for(const auto& prohibition : prohibitions){
		productAllocationsByProductName[prohibition.getProduct().getName()] = prohibition;
		restrictedProducts.insert(prohibition.getProduct().getName());
	}

	//Initialize structures to recover quickly information about store positions on graph
	for(auto &[key, value] : vertexByCell)
		cellByVertex[value] = key;

	vector<Vertex> allVertexes = distanceMatrix->getKeys();
	for(auto key : allVertexes)
		vertexByType[key.getType()].push_back(key); 
	

	//Decompose the warehouse layout to quick search in the algorithm
	vector<Block> blocks = warehouse->getBlocks(); 
	std::transform(blocks.begin(), blocks.end(), std::inserter(blocksByName, blocksByName.end()),
				   [](const Block &b) { return std::make_pair(b.getName(), b); });
	for(unsigned int i=0;i<blocks.size(); i++){
		map<long int, Shelf> shelves = blocks[i].getShelvesById(); 
		for(auto &[id, shelf] : shelves)
			shelvesById[id] = shelf; 
	}

	//Group products by family
	for(unsigned int i=0;i<products.size();i++)
		productsByFamily[products[i].getFamily()].push_back(products[i]);

	productsSortedByFrequence = getProductOrderByFrequence();

	for(unsigned int i=0; i<productsSortedByFrequence.size();i++)
		frequenceByProduct[productsSortedByFrequence[i].first ] = productsSortedByFrequence[i].second; 

	InitializeClosestDeliveryPoint(); 	

	storageVertexTypes.insert(WarehouseToGraphConverter::UPPER_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::UNIQUE_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::FIRST_LEVEL_CELL);
}

void StorageConstructiveHeuristic::InitializeClosestDeliveryPoint(){
	
	vector<Vertex> storagePoints = getStoragePoints(); 
	vector<Vertex> expeditionPoints = vertexByType[WarehouseToGraphConverter::EXPEDITION_POINT_VERTEX]; 
	
	for(const auto& storagePoint : storagePoints){
		double minStartDistance = 1e100;
		double minEndDistance = 1e100; 
		Vertex bestStart, bestEnd; 

		for(const auto& expeditionPoint : expeditionPoints){
			double startDistance = distanceMatrix->getDistance(expeditionPoint, storagePoint);
			double endDistance = distanceMatrix->getDistance(storagePoint, expeditionPoint); 

			if(startDistance < minStartDistance){
				minStartDistance = startDistance; 
				bestStart = expeditionPoint; 
			}
			
			if(endDistance < minEndDistance){
				minEndDistance = endDistance; 
				bestEnd = expeditionPoint; 
			}
		}
		
		closestStartPoint[storagePoint] = bestStart;
		closestEndPoint[storagePoint ] = bestEnd; 
	}	
}

bool StorageConstructiveHeuristic::StopCriteriaReached(){
	
	return false; 
}

bool StorageConstructiveHeuristic::isForbiddenStore(const Product &product, const Vertex &vertex){
	
	//If the cell does not exist (is not found in the set of cells) so obviously it is forbidden store something there 
	if(cellByVertex.find(vertex) == cellByVertex.end())
		return true; 
	else if(productAllocationsByProductName.find(product.getName()) !=  productAllocationsByProductName.end()){
		ProductAllocationProhibitions allocationProhibition = productAllocationsByProductName[product.getName()];
		
		Position location = cellByVertex[vertex]; 
		Cell cell = location.first; 
		long int shelfId = cell.getIdShelf(); 
		
		//If the shelf or the block does not exist, then the allocation is forbidden
		if(shelvesById.find(shelfId) == shelvesById.end() || blocksByName.find(shelvesById[shelfId].getBlockName() ) == blocksByName.end() )
			return true;
		
		Block block = blocksByName[shelvesById[shelfId].getBlockName()];
	
		//The default return to this function is false 
		bool forbidden = false;
		const auto& forbiddenShelves { allocationProhibition.getForbiddenShelves() };
		const auto& forbiddenCells { allocationProhibition.getForbiddenCells() };
		const auto& forbiddenBlocks { allocationProhibition.getForbiddenBlocks() }; 
		
		//If there is a forbidden cell (shelf or block) with a code equals to the code of cell (shelf or block) represented by the 
		//vertex passed as parameter, then the 
		if(forbiddenCells.size() > 0)
			forbidden |= any_of(forbiddenCells.begin(),forbiddenCells.end(), [&cell](const Cell &itCell){ return itCell.getCode() == cell.getCode(); });
		if(forbiddenShelves.size() > 0 && !forbidden)
			forbidden |= any_of(forbiddenShelves.begin(),forbiddenShelves.end(), [shelfId](const Shelf &shelf){ return shelf.getId() == shelfId; });
		if(forbiddenBlocks.size() >0 && !forbidden)
			forbidden |= any_of(forbiddenBlocks.begin(),forbiddenBlocks.end(), [&block](const Block &itBlock){ return itBlock.getName() == block.getName(); }); 
		return forbidden; 
	}
	
	//If the cell exists and there is not an allocation prohibition to the product, then the allocation is always permitted
	return false; 
}


bool StorageConstructiveHeuristic::isIsolatedFamily(const Product &product){
	return isolatedFamilies.find(product.getFamily()) != isolatedFamilies.end();
}

bool StorageConstructiveHeuristic::hasConstraints(const Product &prod){
	return restrictedProducts.find(prod.getName()) != restrictedProducts.end() || 
		   isolatedFamilies.find(prod.getFamily()) != isolatedFamilies.end();
}

double StorageConstructiveHeuristic::getBestRouteWithTwoPoints(const vector<Product> &items, MapAllocation &productAllocation){
																	 
	Vertex location = vertexByCell[ productAllocation[items[0] ] ]; 
	Vertex begin = closestStartPoint[ location  ];
	Vertex end =   closestEndPoint[   location  ] ; 
	double dist1 = this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
	
	location = vertexByCell[ productAllocation[items[1] ] ]; 
	begin = closestStartPoint[ location  ];
	end =   closestEndPoint[   location  ] ; 
	double dist2 = this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
	
	return min(dist1, dist2); 
	
}

double StorageConstructiveHeuristic::evaluatePenaltiesByNonIsolation(MapAllocation & allocations){
	map<string, vector<string> > familiesByCell; 
	map<long, vector<string> > familiesByShelf; 
	map<string, vector<string> > familiesByBlock;

	double totalPenalty = 0.0; 	
		
	for(auto &[product, position] : allocations ){
		if(position.first.getLevels() > 1)
			familiesByCell[position.first.getCode()].push_back(product.getFamily());
		familiesByShelf[position.first.getIdShelf()].push_back(product.getFamily());
		familiesByBlock[shelvesById[position.first.getIdShelf()].getBlockName()].push_back(product.getFamily());
	}
	
	for(auto &[key, value] : familiesByCell)
		totalPenalty += evaluatePenaltyOnLevel(value, CELL_LEVEL); 

	for(auto &[key, value] : familiesByShelf){
		totalPenalty += evaluatePenaltyOnLevel(value, SHELF_LEVEL);	
	} 

	for(auto &[key, value] : familiesByBlock)
		totalPenalty += evaluatePenaltyOnLevel(value, BLOCK_LEVEL);	 	
	
	return totalPenalty;
} 

double StorageConstructiveHeuristic::evaluatePenaltyOnLevel(const vector<string>& familyAllocated, const string& isolation){
	
	double totalPenalty = 0; 
	map<string, int> countByFamily; 	
	int isolatedAccum = 0;
	int notIsolatedAccum = 0; 
	int higherIsolatedQuantity = 0;
	map<string, int> allocationsByFamily; 

	for(unsigned int i=0;i<familyAllocated.size();i++){
		if(allocationsByFamily.find(familyAllocated[i]) == allocationsByFamily.end())
		   allocationsByFamily[familyAllocated[i]] =0;
		allocationsByFamily[familyAllocated[i]]++; 
	}

	if(allocationsByFamily.size() == 1)
		return 0; 

	for(auto [familyCode, quantity] : allocationsByFamily){
		if(isolatedFamilies.find(familyCode) != isolatedFamilies.end() && familyIsolationsByFamilyCode[familyCode].getLevel() == isolation){
			isolatedAccum+= quantity;
			higherIsolatedQuantity = (higherIsolatedQuantity < quantity) ? quantity : higherIsolatedQuantity;
		}else
			notIsolatedAccum += quantity;
	}

	int numAllocations = isolatedAccum + notIsolatedAccum; 
	int remainingIsolated = (isolatedAccum - higherIsolatedQuantity);
	totalPenalty = isolatedAccum > notIsolatedAccum ? (pow(notIsolatedAccum,2) + remainingIsolated)*1.0/numAllocations: pow(isolatedAccum,2)*1.0/numAllocations;
	totalPenalty *= OptimizationParameters::instance()->WEAK_ISOLATED_FAMILY_ALLOCATION_PENALTY;

	return totalPenalty; 
}

double StorageConstructiveHeuristic::evaluatePenaltiesByAllocationProhibition(MapAllocation & allocation){
	double totalPenalty = 0.0;

	vector<ProductAllocationProhibitions> prohibitions = this->constraints.getProductAllocationProhibitions();
	for(auto & prohibition : prohibitions){
		const auto& product { prohibition.getProduct() }; 
		const auto& cell { allocation[product].first }; 
		const auto& shelf { shelvesById[cell.getIdShelf()] };
		const auto& block { blocksByName[shelf.getBlockName()] } ;
		
		auto& forbiddenCells { prohibition.getForbiddenCells() }; 
		auto& forbiddenShelves { prohibition.getForbiddenShelves() };
		auto& forbiddenBlocks { prohibition.getForbiddenBlocks() }; 
		totalPenalty += count_if(begin(forbiddenCells), end(forbiddenCells), [&](const Cell &o){ return  cell.getCode() == o.getCode(); }) +
						count_if(begin(forbiddenShelves), end(forbiddenShelves), [&](const Shelf &o){ return shelf.getId()== o.getId(); }) +
						count_if(begin(forbiddenBlocks), end(forbiddenBlocks), [&](const Block &o){ return block.getName() == o.getName();});
		totalPenalty *= 20000;
	}
 
	return totalPenalty; 
}

void StorageConstructiveHeuristic::EvaluateSolution(AbstractSolution * solution){	
	
	TSP tsp(distanceMatrix); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	double penalty = 0.0; 
	double nonExistentPositionPenalty = 0.0;  
	
	double totalDistance =0.0; 
	MapAllocation productAllocation = ((StorageAllocationSolution *) solution)->getProductAllocations();
	map<Product, vector<PickingRoute *> > routesByProduct; 
	double isolatedFamilyPenalty = evaluatePenaltiesByNonIsolation(productAllocation);
	//double forbiddenAllocationPenalty = evaluatePenaltiesByAllocationProhibition(productAllocation); 
	
	for(unsigned int i=0;i< orders.size();i++){
		items = orders[i].getOrderItems(); 

		storagePoints.clear();
		vector<Product> allocated;
		for(unsigned int j = 0; j<items.size();j++){
			auto position = productAllocation[items[j].first ];
					
			if(vertexByCell.find(position) != vertexByCell.end()){
				allocated.push_back(items[j].first);
				storagePoints.push_back( vertexByCell[ productAllocation[items[j].first ] ] );
			}else {//If some item is not allocated it should be penalized 
				nonExistentPositionPenalty += OptimizationParameters::instance()->NON_ALLOCATED_PRODUCT_PENALTY; 
			}
		}

		if(allocated.size() == 1) {
			Vertex location = vertexByCell[ productAllocation[allocated[0] ] ]; 
			Vertex begin = closestStartPoint[ location  ];
			Vertex end =   closestEndPoint[   location  ] ; 
			totalDistance += this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
		}else if(allocated.size() == 2){
			totalDistance += this->getBestRouteWithTwoPoints(allocated, productAllocation);
		}else{
			if(allocated.size() == 0)continue; 

			pair<double, vector<Vertex> > route; 
			//This is just a limit to use the brute force TSP algorithm
			if(storagePoints.size() < OptimizationParameters::instance()->BRUTE_FORCE_TSP_THRESHOLD){ 
				route = tsp.bruteForceTSP(storagePoints, closestStartPoint, closestEndPoint); 
			}else if(storagePoints.size() < OptimizationParameters::instance()->INSERTION_TSP_THRESHOLD){ //This is a limit to use 
				route = tsp.quickLocalSearchTSP(storagePoints, closestStartPoint, closestEndPoint);
			}else{ //All the other cases will use a closest neighbor inserction procedure 
				route = tsp.closestNeighborTSP(storagePoints, closestStartPoint, closestEndPoint);
			}
			totalDistance += route.first; 

			PickingRoute *newPickingRoute = new PickingRoute();
			newPickingRoute->second = route.first; 
			copy(begin(route.second), end(route.second), back_inserter(newPickingRoute->first));

			for(unsigned int j = 0; j<items.size();j++)
				routesByProduct[items[j].first].push_back(newPickingRoute);
		}
	}
	penalty = nonExistentPositionPenalty + isolatedFamilyPenalty; 
	((StorageAllocationSolution *)solution)->setTotalPenalty(penalty);
	solution->setSolutionValue(totalDistance+penalty);
	((StorageAllocationSolution*)solution)->setRoutesByProduct(routesByProduct);
	
}


tuple <map<string, queue<Product> >, map<string, int> > StorageConstructiveHeuristic::getProductAndFrequenceByFamily(const set<Product> &notUsedProducts){
	map<string, queue<Product> > productsByFamily; 
	map<string, int> frequenceByFamily; 
	
	for(unsigned int i=0; i< productsSortedByFrequence.size();i++){
		string familyName = productsSortedByFrequence[i].first.getFamily(); 
		if(frequenceByFamily.find(familyName) == frequenceByFamily.end())
			frequenceByFamily[familyName] = productsSortedByFrequence[i].second;
		else
			frequenceByFamily[familyName] += productsSortedByFrequence[i].second;
		
		if(notUsedProducts.find(productsSortedByFrequence[i].first) != notUsedProducts.end())
			productsByFamily[familyName].push(productsSortedByFrequence[i].first); 
	}
	
	return {productsByFamily,  frequenceByFamily};
}

vector<pair<int, string > > StorageConstructiveHeuristic::orderFamilyByFrequence(const map<string, int> &frequenceByFamily){
	vector<pair < int, string > > result; 
	
	auto inverter = [](auto& v){ return make_pair(v.second, v.first); };
	transform(begin(frequenceByFamily), end(frequenceByFamily), inserter(result,end(result)), inverter);
	sort(result.begin(), result.end());
	
	return result; 
}


tuple<int, map<Vertex,Product> >  StorageConstructiveHeuristic::testFamilyAllocation(queue<Product>& products, const vector<Vertex> &vertexes){
	
	int contFrequence = 0;
	map<Vertex,Product> currentAllocation; 

	while(!products.empty()){
		auto prod = products.front();

		products.pop(); 
		int cont =0; 
		int tryInsert=0; 
		while(isForbiddenStore(prod, vertexes[tryInsert%vertexes.size()]) && (unsigned)cont++ < vertexes.size())
			tryInsert++;
		
		if(cont < (int) vertexes.size()){
			currentAllocation[vertexes[tryInsert] ] = prod; 
			contFrequence += frequenceByProduct[prod];
		}
	}
	
	return {contFrequence, currentAllocation};
}

bool StorageConstructiveHeuristic::AllocateBestFamily(map<Vertex, Product> & allocations, vector<Vertex>& vertexes, 
										vector<string> familyCodes,  map<string, queue<Product> > &orderedProductsByFamily){

	//Order the vertexes in the block by distance from the closest delivery point 
	//Maybe it could be pre-evaluated 
	auto &closestStartPointDistance = [this](const Vertex & v){ return distanceMatrix->getDistance(closestStartPoint[v], v); };
	sort(vertexes.begin(), vertexes.end(), [this,&closestStartPointDistance](const Vertex &a,const Vertex &b){ 
		return closestStartPointDistance(a) < closestStartPointDistance(b); 
	});
	 
	string bestFamily; 
	int maxFrequence=0; 
	map<Vertex,Product> bestAllocation;  

	for(auto code : familyCodes){
		auto [contFrequence, currentAllocation] = testFamilyAllocation(orderedProductsByFamily[code], vertexes); 
		
		if(contFrequence> maxFrequence){
			maxFrequence = contFrequence; 
			bestFamily = code; 
			bestAllocation = currentAllocation; 
		}
	} 
	
	if(maxFrequence <= 0)
		return false;
	
	set<Product> allocatedProducts;
	for(auto &[vertex, prod] : bestAllocation)
		allocatedProducts.insert(prod);

	queue<Product> remainingOrderedProducts; 

	while(orderedProductsByFamily[bestFamily].size() > 0){
		Product prod = orderedProductsByFamily[bestFamily].front(); 
		if(allocatedProducts.find(prod)== allocatedProducts.end()) 
			remainingOrderedProducts.push(prod); 
		orderedProductsByFamily[bestFamily].pop();
	}

	orderedProductsByFamily[bestFamily] = remainingOrderedProducts; 
	for(auto &[vertex, prod] : bestAllocation)
		allocations[vertex] = prod; 	 
	
	return false;
}

void StorageConstructiveHeuristic::allocateStronglyIsolatedFamilies(map<Vertex,Product> & allocations){

	//First of all it is needed to know which cells were used (or not) as well as the shelves and blocks, in this way we are 
	//able to evaluate available positions for the isolated families 
	
	set<Product> notAllocatedProducts = getNotUsedProducts(allocations); 
	auto [notUsedCells, notUsedShelves, notUsedBlocks] = getNonUsedStructures(allocations);
	
	// After it is needed to know which products were not allocated in each family and put them in frequence order 
	// It is also useful to know the total frequence of each family, then we can try allocated those with a higher 
    // number of requests first
	auto [orderedProductsByFamily, frequenceByFamily] = getProductAndFrequenceByFamily(notAllocatedProducts); 
	vector< pair<int, string> > familiesOrderedByFrequence = orderFamilyByFrequence(frequenceByFamily); 
	map<string, vector<string> > familiesByIsolationLevel;
	
	//Allocate families with "BLOCK" isolation level
	for(auto [code, family] : familyIsolationsByFamilyCode)
		familiesByIsolationLevel[family.getLevel()].push_back(code); 
	
	for(auto block: notUsedBlocks){
 
		map<long int, Shelf> shelves = block.getShelvesById(); 
		vector<Vertex> vertexes; 
		for(auto [id, shelf] : shelves){
			vector<Cell> shelfCells =  shelf.getCells();
			for(unsigned i=0;i<shelfCells.size();i++){
				for(int j=0;j<shelfCells[i].getLevels();j++)
					vertexes.push_back(vertexByCell[make_pair(shelfCells[i],j+1)]); 
			}
		}
 
		bool allocated = AllocateBestFamily(allocations, vertexes, familiesByIsolationLevel[BLOCK_LEVEL], orderedProductsByFamily); 
		if(allocated){
			vector<Shelf> blockShelves= block.getShelves(); 
			//Remove all the shelves of the block (they cannot be used by other family
			for(unsigned int i=0;i<blockShelves.size(); i++)
				if(notUsedShelves.find(blockShelves[i]) != notUsedShelves.end())
					notUsedShelves.erase(blockShelves[i]);
			
			notUsedBlocks.erase(block);
		}

	}
	
	//Allocate families with "SHELF" isolation level
	for(auto shelf : notUsedShelves){
	
		vector<Cell> shelfCells =  shelf.getCells();
		vector<Vertex> vertexes;
	
		for(unsigned i=0;i<shelfCells.size();i++)
			for(int j=0;j<shelfCells[i].getLevels();j++)
				vertexes.push_back(vertexByCell[make_pair(shelfCells[i],j+1)]); 
		bool allocated = AllocateBestFamily(allocations, vertexes, familiesByIsolationLevel[SHELF_LEVEL], orderedProductsByFamily);
	
		if(allocated){
			vector<Cell> shelfCells = shelf.getCells(); 
			//Remove all cells of this shelf from the list of not used cells
	
			for(unsigned int i=0;i<shelfCells.size(); i++)
				if(notUsedCells.find(shelfCells[i]) != notUsedCells.end())
					notUsedCells.erase(shelfCells[i]);
			notUsedShelves.erase(shelf);
	
		}
	}
	
	for(auto cell : notUsedCells){
		vector<Vertex> vertexes;
		for(int j=0;j<cell.getLevels();j++)
			vertexes.push_back(vertexByCell[make_pair(cell,j+1)]); 
		
		bool allocated = AllocateBestFamily(allocations, vertexes, familiesByIsolationLevel[CELL_LEVEL], orderedProductsByFamily);
		if(allocated)
			notUsedCells.erase(cell);
	}
	
}

void StorageConstructiveHeuristic::fillFrequenceByProduct(){
	if(productsSortedByFrequence.size() == 0){
		productsSortedByFrequence = getProductOrderByFrequence();
		for(unsigned int i=0; i<productsSortedByFrequence.size();i++)
			frequenceByProduct[productsSortedByFrequence[i].first ] = productsSortedByFrequence[i].second; 
	}
}

void StorageConstructiveHeuristic::setBestSolution(map<Vertex, Product> &allocation){
	bestSolution = new StorageAllocationSolution(0.0, 0.0, 1e-02,false); 
	map<Product, pair<Cell, int> > allocationByProduct; 
	for(auto & [vertex, product] : allocation){
		allocationByProduct[product] = cellByVertex[vertex]; 
	}
	
	((StorageAllocationSolution *)bestSolution)->setAllocation(allocationByProduct,orders); 
	EvaluateSolution(bestSolution);
}

StorageAllocationSolution * StorageConstructiveHeuristic::Execute(){
	
	map<string, vector<Vertex> > vertexByType = getVertexesByType(); 	///< Store the vertex classification
	map<Vertex,Product> allocation; 									///< Store the product allocation on the vertexes
	
	vector<bool> usedVertex; 											///< Stores if vertex is used or not
	set<Product> allocatedProducts; 
	map<Cell, set<string> > familiesByCell; 							///< Stores all the families that have constraints by cell
	map<Shelf, set<string> > familiesByShelf;							///< Stores all the shelves that have constraints by shelf
	map<Block, set<string> > familiesByBlock;  							///< Stores all families that have constraints by block
	int lastOnSequence = 0; 
	unsigned int countTries = 0; 
	
	vector<Vertex> storePoints = getStorageVertexes(vertexByType);
	vector<Vertex> vertexesOrderedByDistance = getStorageVertexesOrderedByDistance(); 
	fillFrequenceByProduct();
	
	auto numPositions { vertexesOrderedByDistance.size() }; 
	usedVertex.resize(numPositions, false); 

	for(unsigned int i=0;i<productsSortedByFrequence.size();i++){
		auto & item  = productsSortedByFrequence[i]; 
	
		if(!hasConstraints(item.first)){				// All the products that have not a allocation constraint are inserted in 
														// the first available cell
			while(usedVertex[lastOnSequence%numPositions] && numPositions> countTries++)lastOnSequence++;
			usedVertex[lastOnSequence%numPositions] = true; 
			allocation[vertexesOrderedByDistance[lastOnSequence%numPositions]] = item.first; 
		}else if(isIsolatedFamily(item.first)){
			IsolatedFamily isolation = familyIsolationsByFamilyCode[item.first.getFamily()]; 
			unsigned int tryInsertIndex = lastOnSequence%numPositions; 	

			//Looks for the first not forbidden available position			
			while((isForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) && numPositions> countTries++)
				tryInsertIndex = (tryInsertIndex+1)%numPositions;

			if(countTries <= numPositions){ //It means that not all the positions were tested and an insertion is possible 			
				if(isolation.getForce() == WEAK_ISOLATION){							// If it is a weak isolation, we perform the allocation anyway
					usedVertex[tryInsertIndex] = true;
					allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
				}else if(isolation.getForce() == STRONG_ISOLATION ){ //If we have an strong isolation by cell but just one product can be inserted 
																	 // in each cell, so it is ok to insert the product there 
					if(cellByVertex[vertexesOrderedByDistance[tryInsertIndex]].first.getLevels() == 1 && isolation.getLevel() == CELL_LEVEL){
						usedVertex[tryInsertIndex] = true; 
						allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
					}
				}
			}
			
		}else{ //Forbidden allocation products 
			unsigned int tryInsertIndex = lastOnSequence%numPositions; 
			while((isForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) && numPositions > countTries++)
				tryInsertIndex = (tryInsertIndex+1)%numPositions;

			if(countTries <= vertexByCell.size()){
				usedVertex[tryInsertIndex] = true;
				allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
			}
		}
	
		countTries = 0;
	} 
	
	allocateStronglyIsolatedFamilies(allocation);
	setBestSolution(allocation); 
	
	return (StorageAllocationSolution *)bestSolution; 
}

vector<Vertex> StorageConstructiveHeuristic::getStorageVertexes(map<string,vector<Vertex> > &vertexByType){
	vector<Vertex> result; 
	
	for(auto & [key,value] : vertexByType){
		if(storageVertexTypes.find(key) != storageVertexTypes.end()){
			for(unsigned int i=0; i<value.size(); i++)
				result.push_back(value[i]); 
		}
	}
	
	return result; 
}

set<Product>  StorageConstructiveHeuristic::getNotUsedProducts(const map<Vertex,Product> allocations){
	set<Product> result;
	
	for(unsigned int i=0;i<products.size(); i++)
		result.insert(products[i]);
	
	for(const auto &[key, value]: allocations){
		result.erase(value); 
		(void)key; 
	}
	
	return result; 
}

vector<Vertex> StorageConstructiveHeuristic::getStoragePoints(){
	
	storageVertexTypes.insert(WarehouseToGraphConverter::UPPER_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::UNIQUE_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::FIRST_LEVEL_CELL);
	
	vector<Vertex> result;
	
	for( auto &[key, value] : vertexByCell){
		(void) key; //Only to clean warnings about not using this variable
		if(storageVertexTypes.find(value.getType()) != storageVertexTypes.end() )
			result.push_back(value);
	}
	
	return result; 
}

vector<Vertex> StorageConstructiveHeuristic::getStorageVertexesOrderedByDistance(){
	
	vector<pair< double,Vertex> > vertexesOrderedByDistance; 
	vector<Vertex> expeditionPoints = vertexByType["ExpeditionPointVertex"];
	vector<Vertex> storagePoints = getStoragePoints(); 
	
	for(unsigned i=0;i<storagePoints.size(); i++){
		double lowerDistance = 1e200; 
		for(unsigned int j=0; j<expeditionPoints.size();j++)
			if(lowerDistance >distanceMatrix->getDistance(expeditionPoints[j], storagePoints[i]))
				lowerDistance = distanceMatrix->getDistance(expeditionPoints[j], storagePoints[i]);
		
		vertexesOrderedByDistance.push_back(make_pair(lowerDistance, storagePoints[i])); 
	}
	
	sort(vertexesOrderedByDistance.begin(), vertexesOrderedByDistance.end());
	
	vector<Vertex> result;
	for(unsigned int i=0;i< vertexesOrderedByDistance.size(); i++)
		result.push_back(vertexesOrderedByDistance[i].second); 
	
	return result;
}

vector<pair<Product,int> > StorageConstructiveHeuristic::getProductOrderByFrequence(){
	
	map<Product, int> productCount; 
	vector<pair<Product,double> > orderItems; 
	
	for(unsigned int i=0;i<orders.size();i++){
		orderItems = orders[i].getOrderItems(); 
		for(unsigned int j=0;j<orderItems.size();j++)
			if(productCount.find(orderItems[j].first) == productCount.end())
				productCount[orderItems[j].first] = 1;
			else
				productCount[orderItems[j].first]++;
	}
	
	vector<pair<int,Product> > orderedProducts; 
	for(auto &[key, value] : productCount)
		orderedProducts.push_back(make_pair(value,key));
	
	sort(orderedProducts.begin(), orderedProducts.end()); 
	reverse(orderedProducts.begin(), orderedProducts.end()); 
	
	vector<pair<Product, int> > result;
	
	for(unsigned int i=0;i<orderedProducts.size(); i++)
		result.push_back(make_pair(orderedProducts[i].second, orderedProducts[i].first)); 
	
	return result; 
	
}

map<string, vector<Vertex> > StorageConstructiveHeuristic::getVertexesByType(){
	map<string, vector<Vertex> > result; 
	
	vector<Vertex> vertexes;	
	vertexes = (vector<Vertex> &) this->distanceMatrix->getKeys();

	for(unsigned int i=0; i<vertexes.size();i++)
		result[vertexes[i].getType()].push_back(vertexes[i]);
	
	return result;
}

set<Cell> StorageConstructiveHeuristic::getNotUsedCells(const map<Vertex,Product> &allocations){
	set<Cell> result; 

	transform(begin(vertexByCell), end(vertexByCell), inserter(result, end(result)), [](auto& e) {
		return e.first.first;
	});
	
	for(const auto &[key, value] : allocations){
		(void) value; //Only to clean warnings about not using this variable
		result.erase(cellByVertex[key].first); 
	}
	
	return result; 
}

set<Shelf> StorageConstructiveHeuristic::getNotUsedShelves(const set<Cell> &usedCells){
	set<Shelf> result; 
	
	transform(begin(shelvesById), end(shelvesById), 
			  inserter(result, end(result)), [](auto& a){ return a.second; });

	for(const auto &cell : usedCells)
		result.erase(shelvesById[cell.getIdShelf()]);

	return result; 
}

set<Block> StorageConstructiveHeuristic::getNotUsedBlocks(const set<Shelf> &usedShelves){
	set<Block> result; 
	
	transform(begin(blocksByName), end(blocksByName), 
			  inserter(result, end(result)), [](auto &a){ return a.second; });

	for(const auto &shelf : usedShelves)
		result.erase(blocksByName[shelf.getBlockName()]); 
	
	return result;
} 


tuple<set<Cell> , set<Shelf> , set<Block> > StorageConstructiveHeuristic::getNonUsedStructures(const map<Vertex,Product> &allocations){
	
	set<Cell> notUsedCells = getNotUsedCells(allocations);
	set<Cell> usedCells; 
	for(const auto & [key, value] : vertexByCell) { 
		(void) value; 
		if(notUsedCells.find(key.first) == notUsedCells.end() ) 
			usedCells.insert(key.first);
	}
	
	set<Shelf> notUsedShelves = getNotUsedShelves(usedCells);
	set<Shelf> usedShelves; 
	for(const auto & [id, shelf] : shelvesById) 
		if(notUsedShelves.find(shelf) == notUsedShelves.end() ) 
		usedShelves.insert(shelf);

	set<Block> notUsedBlocks = getNotUsedBlocks(usedShelves); 
	
	return {notUsedCells, notUsedShelves, notUsedBlocks};
	
}