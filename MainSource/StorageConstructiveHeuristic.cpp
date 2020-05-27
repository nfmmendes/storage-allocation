#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include<algorithm> 
#include<queue>
#include<exception> 
#include "Product.h"
#include "Vertex.h"
#include "Heuristic.h"
#include "Warehouse.h"
#include "DistanceMatrix.h"
#include "Order.h"
#include "OptimizationConstraints.h"
#include "StorageConstructiveHeuristic.h"
#include "ProductAllocationProhibition.h"
#include "WarehouseToGraphConverter.h"
#include "IsolatedFamily.h"
#include "TSP.h"
using namespace std;
using namespace QuickTSP; 


/***
 * Member constructor
 **/
StorageConstructiveHeuristic::StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> &distMatrix,
														   map<pair<Cell, int>, Vertex> vertexByCell, vector<Order> &orders, OptimizationConstraints &cons){
	this->distanceMatrix = &distMatrix; 
	this->warehouse = &wh; 
	this->orders= orders; 
	this->constraints = cons; 
	this->products = prods; 	
	this->vertexByCell = vertexByCell; 
	
	InitializeAuxiliaryDataStructures(); 
}

/**
 * Initialize all the relevant data structures that will be used by the algorithm
 * Most of structures initialized here will be used in more than one function and several times, then is not 
 * elegant to initialize them all the time it is needed 
 **/
void StorageConstructiveHeuristic::InitializeAuxiliaryDataStructures(){
	
	
	vector<IsolatedFamily> isolatedFamiliesList = constraints.getIsolatedFamilies(); 
	vector<ProductAllocationProhibitions> prohibitions = constraints.getProduAllocationProhibitions();
	
	//Initialize isolated families structures
	for(unsigned int i=0; i< isolatedFamiliesList.size(); i++){
		familyIsolationsByFamilyCode[isolatedFamiliesList[i].getCode()] = isolatedFamiliesList[i];
		isolatedFamilies.insert(isolatedFamiliesList[i].getCode());
	}		
	
	//Initialize product allocation prohibitions structures 
	for(unsigned int i= 0;i< prohibitions.size(); i++){
		productAllocationsByProductName[prohibitions[i].getProduct().getName()] = prohibitions[i];
		restrictedProducts.insert(prohibitions[i].getProduct().getName());
	}
	
	//Initialize structures to recover quickly information about store positions on graph
	for(auto &[key, value] : vertexByCell){
		cellByVertex[value] = key; 
		vertexByType[value.getType()].push_back(value); 
	}
	
	
	//Decompose the warehouse layout to quick search in the algorithm
	vector<Block> blocks = warehouse->getBlocks(); 
	std::transform(blocks.begin(), blocks.end(), std::inserter(blocksByName, blocksByName.end()),
				   [](const Block &b) { return std::make_pair(b.getName(), b); });
	for(unsigned int i=0;i<blocks.size(); i++){
		map<long int, Shelf> shelves = blocks[i].getShelvesById(); 
		for(unsigned int j=0;j<shelves.size(); j++)
			shelvesById[shelves[i].getId()] = shelves[i]; 
	}
	
	//Group products by family
	for(unsigned int i=0;i<products.size();i++)
		productsByFamily[products[i].getType()].push_back(products[i]);
	
	productsByFrequence = getProductOrderByFrequence();
	
	
	InitializeClosestDeliveryPoint(); 	
	
	storageVertexTypes.insert(WarehouseToGraphConverter::UPPER_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::UNIQUE_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::FIRST_LEVEL_CELL);
	
}


/**
 * Set the closest expedition point of each storage point in both senses, storage -> expedition, expedition -> storage
 **/
void StorageConstructiveHeuristic::InitializeClosestDeliveryPoint(){
	
	vector<Vertex> storagePoints = getStoragePoints(); 
	vector<Vertex> expeditionPoints = vertexByType[WarehouseToGraphConverter::EXPEDITION_POINT_VERTEX]; 
	TSP tsp(*this->distanceMatrix);
	
	for(unsigned int i=0;i<storagePoints.size();i++){
		double minStartDistance = 1e100;
		double minEndDistance = 1e100; 
		Vertex bestStart, bestEnd; 
		
		for(unsigned int j=0;j<expeditionPoints.size();j++){
			double startDistance = distanceMatrix->getDistance(expeditionPoints[j], storagePoints[i]);
			double endDistance = distanceMatrix->getDistance(storagePoints[i], expeditionPoints[j]); 
			
			if(startDistance < minStartDistance){
				minStartDistance = startDistance; 
				bestStart = expeditionPoints[j]; 
			}
			
			if(endDistance < minEndDistance){
				minEndDistance = endDistance; 
				bestEnd = expeditionPoints[j]; 
			}
		}
		closestStartPoint[storagePoints[i]] = bestStart;
		closestEndPoint[storagePoints[i] ] = bestEnd; 
		
	}
}


/**
 * Overload function used to define if the algorithm has reached the stop criteria or not 
 **/
bool StorageConstructiveHeuristic::StopCriteriaReached(){
	
	return false; 
}

/**
 * Analyse if a product can be allocated in a vertex based in the allocations prohibitions 
 * @param product Product that will be evaluated 
 * @param vertex Vertex were we are trying to put the product 
 **/
bool StorageConstructiveHeuristic::isForbiddenStore(Product &product, Vertex &vertex){
	
	//If the cell does not exist (is not found in the set of cells) so obviously it is forbidden store something there 
	if(cellByVertex.find(vertex) == cellByVertex.end())
		return true; 
	else if(productAllocationsByProductName.find(product.getName()) !=  productAllocationsByProductName.end()){
		ProductAllocationProhibitions allocationProhibition = productAllocationsByProductName[product.getName()];
		pair<Cell,int> location = cellByVertex[vertex]; 
		Cell cell = location.first; 
		long int shelfId = cell.getIdShelf(); 
		
		//If the shelf or the block does not exist, then the allocation is forbidden
		if(shelvesById.find(shelfId) == shelvesById.end() || blocksByName.find(shelvesById[shelfId].getBlockName() ) == blocksByName.end() )
			return true;
		
		Block block = blocksByName[shelvesById[shelfId].getBlockName()];
	
		//The default return to this function is false 
		bool result = false;
		vector<Shelf> forbiddenShelves = allocationProhibition.getForbiddenShelves();
		vector<Cell> forbiddenCells = allocationProhibition.getForbiddenCells();
		vector<Block> forbiddenBlocks = allocationProhibition.getForbiddenBlocks(); 
		
		//If there is a forbidden cell (shelf or block) with a code equals to the code of cell (shelf or block) represented by the 
		//vertex passed as parameter, then the 
		if(forbiddenCells.size() > 0)
			result = count_if(forbiddenCells.begin(),forbiddenCells.end(), [&cell](Cell &itCell){return itCell.getCode() == cell.getCode();}) >0;
		if(forbiddenShelves.size() > 0)
			result = count_if(forbiddenShelves.begin(),forbiddenShelves.end(), [shelfId](Shelf &shelf){return shelf.getId() == shelfId;}) >0;
		if(forbiddenBlocks.size() >0)
			result = count_if(forbiddenBlocks.begin(),forbiddenBlocks.end(), [&block](Block &itBlock){return itBlock.getName() == block.getName();}) >0;
		
		return result; 
	
		
	}
	
	//If the cell exists and there is not an allocation prohibition to the product, then the allocation is always permitted
	return false; 
}

/**
 *
 **/
bool StorageConstructiveHeuristic::isIsolatedFamily(Product &product){
	return isolatedFamilies.find(product.getType()) != isolatedFamilies.end();
}

/**
 *
 **/
bool StorageConstructiveHeuristic::hasConstraints(Product &prod){
	return restrictedProducts.find(prod.getName()) != restrictedProducts.end() || 
		   isolatedFamilies.find(prod.getType()) != isolatedFamilies.end();
}

/**
 *
 **/
double StorageConstructiveHeuristic::getBetterRouteWithTwoPoints(vector<pair<Product, double> > &items, 
																 map<Product, pair<Cell,int> > &productAllocation){
																	 
	Vertex location = vertexByCell[ productAllocation[items[0].first ] ]; 
	Vertex begin = closestStartPoint[ location  ];
	Vertex end =   closestEndPoint[   location  ] ; 
	double dist1 = this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
	
	location = vertexByCell[ productAllocation[items[1].first ] ]; 
	begin = closestStartPoint[ location  ];
	end =   closestEndPoint[   location  ] ; 
	double dist2 = this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
	
	return min(dist1, dist2); 
	
}


/**
 * Full evaluate a solution 
 **/
void StorageConstructiveHeuristic::EvaluateSolution(AbstractSolution * solution){	
	
	TSP tsp(*distanceMatrix); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	double penalty = 0.0; 
	double totalDistance =0.0;
	
	map<Product, pair<Cell,int> > productAllocation = ((StorageAllocationSolution *) solution)->getProductAllocations();
	
	for(unsigned int i=0;i< orders.size();i++){
		items = orders[i].getOrderItems(); 
		
		if(items.size() == 1) {
			Vertex location = vertexByCell[ productAllocation[items[0].first ] ]; 
			Vertex begin = closestStartPoint[ location  ];
			Vertex end =   closestEndPoint[   location  ] ; 
			totalDistance += this->distanceMatrix->getDistance(begin, location) + this->distanceMatrix->getDistance(location, end); 
		}else if(items.size() == 2){
			totalDistance += this->getBetterRouteWithTwoPoints(items, productAllocation);
			
		}else{
			//If some item is not allocated it should be penalized 
			for(unsigned int j = 0; j<items.size();j++){
				if(vertexByCell.find(productAllocation[items[j].first ]) != vertexByCell.end())
					storagePoints.push_back( vertexByCell[ productAllocation[items[j].first ] ] );
				else 
					penalty += 5000; 
			}
			
			pair<double, vector<Vertex> > route; 
			if(storagePoints.size() < 6) //This is just a limit to use the brute force TSP algorithm
				route = tsp.bruteForceTSP(storagePoints, closestStartPoint, closestEndPoint); 
			else if(storagePoints.size() < 12) //This is a limit to use 
				route = tsp.quickLocalSearchTSP(storagePoints, closestStartPoint, closestEndPoint);
			else //All the other cases will use a closest neighbor inserction procedure 
				route = tsp.closestNeighborTSP(storagePoints, closestStartPoint, closestEndPoint);
			
			totalDistance += route.first; 
		}
	}
}

/**
 * Allocate products that belongs to strongly isolated families and were not allocated in the initial solution 
 * @param allocations Maps all the already allocated products to its positions 
 * @param usedVertex Lists which vertex were already used or not 
 **/
void StorageConstructiveHeuristic::allocateStronglyIsolatedFamilies(map<Vertex,Product> & allocations, vector<bool> &usedVertex){
	
	//First of all it is needed to know which cells were used (or not) as well as the shelves and blocks, in this way we are 
	//able to evaluate available positions for the isolated families 
	set<Product> notUsedProducts = getNonUsedProducts(allocations); 
	set<Cell> notUsedCells = getNonUsedCells(allocations);
	set<Cell> usedCells; 
	for(const auto & [key, value] : vertexByCell) { 
		(void) value; 
		if(notUsedCells.find(key.first) == notUsedCells.end() ) 
			usedCells.insert(key.first);
	}
	
	set<Shelf> notUsedShelves = getNonUsedShelves(usedCells);
	set<Shelf> usedShelves; 
	for(const auto & shelf : notUsedShelves) if(notUsedShelves.find(shelf) == notUsedShelves.end() ) usedShelves.insert(shelf);
	
	set<Block> notUsedBlocks = getNonUsedBlocks(usedShelves); 
	
	//After it is needed to know which products were not allocated in each family and put them in frequence order 
	//It is also useful to know the total frequence of each family, then we can try allocated those with a higher 
	//number of requests first 
	map<string, queue<Product> > productsByFamily; 
	map<string, int> frequenceByFamily; 
	
	for(unsigned int i=0; i< productsByFrequence.size();i++){
		string familyName = productsByFrequence[i].first.getType(); 
		if(frequenceByFamily.find(familyName) == frequenceByFamily.end())
			frequenceByFamily[familyName] = productsByFrequence[i].second;
		else
			frequenceByFamily[familyName] += productsByFrequence[i].second;
		
		if(notUsedProducts.find(productsByFrequence[i].first) != notUsedProducts.end())
			productsByFamily[familyName].push(productsByFrequence[i].first); 
	}
	
	//Order the families by number of requests 
	vector< pair<int, string> > familiesOrderedByFrequence; 
	for(const auto &[family,frequence] :  frequenceByFamily)
		familiesOrderedByFrequence.push_back(make_pair(frequence,family));
	
	sort(familiesOrderedByFrequence.begin(), familiesOrderedByFrequence.end()); 

	for(unsigned int i = 0; i<familiesOrderedByFrequence.size(); i++){
		/*** CONTINUE FROM HERE ***/
	}
	
}




/**
 * Overloaded function that runs the algorithm 
 **/
StorageAllocationSolution * StorageConstructiveHeuristic::Execute(){
	map<string, vector<Vertex> > vertexByType = getVertexesByType(); 	///< Store the vertex classification
	map<Vertex,Product> allocation; 									///< Store the product allocation on the vertexes
	
	vector<bool> usedVertex; 											///< Stores if vertex is used or not
	set<Product> allocatedProducts; 
	map<Cell, set<string> > familiesByCell; 
	map<Shelf, set<string> > familiesByShelf;
	map<Block, set<string> > familiesByBlock;  
	
	vector<Vertex> storePoints = getStorageVertexes(vertexByType);
	vector<Vertex> vertexesOrderedByDistance = getStorageVertexesOrderedByDistance(); 
	
	if(productsByFrequence.size() == 0)
		productsByFrequence = getProductOrderByFrequence();
	
	
	int lastOnSequence = 0; 
	usedVertex.resize(vertexByCell.size(), false); 
	
	for(unsigned int i=0;i<productsByFrequence.size();i++){
		auto & item  = productsByFrequence[i]; 
		if(!hasConstraints(item.first)){
			while(usedVertex[lastOnSequence])lastOnSequence++;
			usedVertex[lastOnSequence] = true; 
			allocation[vertexesOrderedByDistance[lastOnSequence]] = item.first; 
		}else if(isIsolatedFamily(item.first)){
			IsolatedFamily isolation = familyIsolationsByFamilyCode[item.first.getType()]; 
			string level = isolation.getLevel(); 
			string force = isolation.getForce();
			
			unsigned int tryInsertIndex = lastOnSequence; 
			while(isForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) 
				tryInsertIndex++;
			
			if(force == "WEAK"){
				usedVertex[tryInsertIndex] = true;
				allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
			}else if(force == "STRONG"){
				if(cellByVertex[vertexesOrderedByDistance[tryInsertIndex]].first.getLevels() == 1 && level == "CELL"){
					usedVertex[tryInsertIndex] = true; 
					allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
				}else				
					continue;
			}
			
		}else{
			unsigned int tryInsertIndex = lastOnSequence; 
			while(isForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) 
				tryInsertIndex++;
			
			if(tryInsertIndex < vertexesOrderedByDistance.size()){
				usedVertex[tryInsertIndex] = true;
				allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
			}
		}
		
	} 
	
	allocateStronglyIsolatedFamilies(allocation, usedVertex);
	

	int countNotAllocated = count_if(usedVertex.begin(), usedVertex.end(), [](bool a){ return !a; } );
	cout<<"Not allocated:\t" <<countNotAllocated<<endl;
	
	return NULL; 
}


/**
 *	Get all the vertexes where is possible to store a product, following the vertex typedef
 *  @param vertexByType A map where each element is a list with vertexes of an unique type (given by the key)
 */
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

/**
 * Get the list of products non allocated in the warehouse after an initial allocation 
 * @param allocations initial allocation 
 **/ 
set<Product>  StorageConstructiveHeuristic::getNonUsedProducts(const map<Vertex,Product> allocations){
	set<Product> result;
	
	for(unsigned int i=0;i<products.size(); i++)
		result.insert(products[i]);
	
	for(const auto &[key, value]: allocations){
		result.erase(value); 
		(void)key; 
	}
	
	return result; 
}


/**
 * Get the list of all the vertexes in the graph that can be used as a storage point 
 **/
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



/**
 * 
 **/
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




/**
 * Get the products ordered by descending order of frequence and with its respective frequencies
 **/
vector<pair<Product,int> > StorageConstructiveHeuristic::getProductOrderByFrequence(){
	
	map<Product, int> productCount; 
	vector<pair<Product,double> > orderItems; 
	
	for(unsigned int i=0;i<orders.size();i++){
		orderItems = orders[i].getOrderItems(); 
		for(unsigned int j=0;j<orders.size();j++)
			if(productCount.find(orderItems[j].first) != productCount.end())
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



/**
 * Get the list of all expedition points
 **/
map<string, vector<Vertex> > StorageConstructiveHeuristic::getVertexesByType(){
	map<string, vector<Vertex> > result; 
	
	vector<Vertex> vertexes;	
	vertexes = (vector<Vertex> &) this->distanceMatrix->getKeys();

	for(unsigned int i=0; i<vertexes.size();i++)
		result[vertexes[i].getType()].push_back(vertexes[i]);
	
	return result;
}

/**
 * Get the set of non used cells after an initial allocation of products
 **/
set<Cell> StorageConstructiveHeuristic::getNonUsedCells(const map<Vertex,Product> &allocations){
	set<Cell> result; 
	
	for(const auto &[key,value] : vertexByCell){
		(void) value; //Only to clean warnings about not using this variable
		result.insert(key.first);
	}
	
	for(const auto &[key, value] : allocations){
		(void) value; //Only to clean warnings about not using this variable
		result.erase(cellByVertex[key].first); 
	}
	
	return result; 
}

/** 
 * Get the set of non used shelves after an initial allocation of products
 **/
set<Shelf> StorageConstructiveHeuristic::getNonUsedShelves(const set<Cell> &usedCells){
	set<Shelf> result; 
	
	for(const auto &[key, value] : shelvesById){
		(void) key; 	//Only to clean warnings about not using this variable
		result.insert(value); 
	}
	
	for(const auto &cell : usedCells)
		result.erase(shelvesById[cell.getIdShelf()]);

	return result; 
}


/**
 * Get the set of non used blocks after an initial allocation of products 
 **/
set<Block> StorageConstructiveHeuristic::getNonUsedBlocks(const set<Shelf> &usedShelves){
	set<Block> result; 
	
	for(const auto &block : blocksByName)
		result.insert(block.second);
	
	for(const auto &shelf : usedShelves)
		result.erase(blocksByName[shelf.getBlockName()]); 

	return result;
} 