#include<iostream>
#include<cmath>
#include<iomanip>
#include<vector>
#include<algorithm> 
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



StorageConstructiveHeuristic::StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> distMatrix,
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
 *
 **/
void StorageConstructiveHeuristic::InitializeAuxiliaryDataStructures(){
	
	vector<IsolatedFamily> isolatedFamiliesList = constraints.getIsolatedFamilies(); 
	vector<ProductAllocationProhibitions> prohibitions = constraints.getProduAllocationProhibitions();
	
	for(unsigned int i=0; i< isolatedFamiliesList.size(); i++){
		familyIsolationsByFamilyCode[isolatedFamiliesList[i].getCode()].push_back(isolatedFamiliesList[i]);
		isolatedFamilies.insert(isolatedFamiliesList[i].getCode());
	}		
	
	for(unsigned int i= 0;i< prohibitions.size(); i++){
		productAllocationsByProductName[prohibitions[i].getProduct().getName()] = prohibitions[i];
		restrictedProducts.insert(prohibitions[i].getProduct().getName());
	}
	
	for(auto &[key, value] : vertexByCell){
		cellByVertex[value] = key; 
		vertexByType[value.getType()].push_back(value); 
	}
	
	vector<Block> blocks = warehouse->getBlocks(); 
	std::transform(blocks.begin(), blocks.end(), std::inserter(blocksByName, blocksByName.end()),
				   [](const Block &b) { return std::make_pair(b.getName(), b); });
	for(unsigned int i=0;i<blocks.size(); i++){
		map<long int, Shelf> shelves = blocks[i].getShelvesById(); 
		for(unsigned int j=0;j<shelves.size(); j++)
			shelvesById[shelves[i].getId()] = shelves[i]; 
	}
	
	
	
	for(unsigned int i=0;i<products.size();i++){
		productsByFamily[products[i].getType()].push_back(products[i]);
	}
	
	
	storageVertexTypes.insert(WarehouseToGraphConverter::UPPER_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::UNIQUE_LEVEL_CELL);
	storageVertexTypes.insert(WarehouseToGraphConverter::FIRST_LEVEL_CELL);
	
}


/**
 *
 **/
bool StorageConstructiveHeuristic::StopCriteriaReached(){
	
	return false; 
}

/**
 *
 **/
bool StorageConstructiveHeuristic::isForbiddenStore(Product &product, Vertex &vertex){
	
	if(cellByVertex.find(vertex) == cellByVertex.end())
		return true; 
	else if(productAllocationsByProductName.find(product.getName()) !=  productAllocationsByProductName.end()){
		ProductAllocationProhibitions allocationProhibition = productAllocationsByProductName[product.getName()];
		pair<Cell,int> location = cellByVertex[vertex]; 
		Cell cell = location.first; 
		long int shelfId = cell.getIdShelf(); 
		
		
		if(shelvesById.find(shelfId) == shelvesById.end() || blocksByName.find(shelvesById[shelfId].getBlockName() ) == blocksByName.end() )
			return false;
		
		Block block = blocksByName[shelvesById[shelfId].getBlockName()];
	
		bool result = false;
		vector<Shelf> forbiddenShelves = allocationProhibition.getForbiddenShelves();
		vector<Cell> forbiddenCells = allocationProhibition.getForbiddenCells();
		vector<Block> forbiddenBlocks = allocationProhibition.getForbiddenBlocks(); 
		
		if(forbiddenCells.size() > 0)
			result = count_if(forbiddenCells.begin(),forbiddenCells.end(), [&cell](Cell &itCell){return itCell.getCode() == cell.getCode();}) >0;
		if(forbiddenShelves.size() > 0)
			result = count_if(forbiddenShelves.begin(),forbiddenShelves.end(), [shelfId](Shelf &shelf){return shelf.getId() == shelfId;}) >0;
		if(forbiddenBlocks.size() >0)
			result = count_if(forbiddenBlocks.begin(),forbiddenBlocks.end(), [&block](Block &itBlock){return itBlock.getName() == block.getName();}) >0;
		
		return result; 
	
		
	}
	
	return false; 
}

bool StorageConstructiveHeuristic::hasConstraints(Product &prod){
	return restrictedProducts.find(prod.getName()) == restrictedProducts.end() || 
		   isolatedFamilies.find(prod.getType()) == isolatedFamilies.end();
}

void StorageConstructiveHeuristic::EvaluateSolution(AbstractSolution * solution){	
	
	TSP tsp(*distanceMatrix); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	double penalty = 0.0; 
	
	map<Product, pair<Cell,int> > productAllocation = ((StorageAllocationSolution *) solution)->getProductAllocations();
	
	for(unsigned int i=0;i< orders.size();i++){
		items = orders[i].getOrderItems(); 
		storagePoints.clear();
		
		for(unsigned int j = 0; j<items.size();j++){
			if(vertexByCell.find(productAllocation[items[j].first ]) != vertexByCell.end())
				storagePoints.push_back(productAllocation[items[j].first ]);
			else 
				penalty += 5000; 
		}
		
	}
		
	
}

StorageAllocationSolution * StorageConstructiveHeuristic::Execute(){
	
	map<string, vector<Vertex> > vertexByType = getVertexesByType(); 	///< Store the vertex classification
	map<Vertex,Product> allocation; 									///< Store the product allocation on the vertexes
	vector<bool> usedVertex; 											///< Stores if vertex is used or not
	
	vector<Vertex> storePoints = getStorageVertexes(vertexByType);
	
	vector<Vertex> vertexesOrderedByDistance = getStorageVertexesOrderedByDistance(); 
	vector<pair< Product , int> > productsByFrequence = getProductOrderByFrequence();
	
	
	int lastOnSequence = 0; 
	usedVertex.resize(vertexByCell.size(), false); 
	for(auto & item : productsByFrequence){
		if(!hasConstraints(item.first)){
			while(usedVertex[lastOnSequence])lastOnSequence++;
			usedVertex[lastOnSequence] = true; 
			allocation[vertexesOrderedByDistance[lastOnSequence]] = item.first; 
		}else{
			unsigned int tryInsertIndex = lastOnSequence; 
			while(isForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) 
				tryInsertIndex++;
			
			if(tryInsertIndex < vertexesOrderedByDistance.size()){
				usedVertex[tryInsertIndex];
				allocation[vertexesOrderedByDistance[tryInsertIndex]] = item.first; 
			}
		}
		
	} 
	
	int countNotAllocated = count_if(usedVertex.begin(), usedVertex.end(), [](bool a){ return !a; } );
	cout<<countNotAllocated<<endl;
	
	
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
 *
 * 
 */
vector<Vertex> StorageConstructiveHeuristic::getStorageVertexesOrderedByDistance(){
	
	vector<pair< double,Vertex> > vertexesOrderedByDistance; 
	vector<Vertex> expeditionPoints = vertexByType["ExpeditionPointVertex"];
	vector<Vertex> storagePoints; 
	
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
	
	vector<Vertex> vertexes = this->distanceMatrix->getKeys();
	map<string, vector<Vertex> > result; 
	
	for(unsigned int i=0; i<vertexes.size();i++)
		result[vertexes[i].getType()].push_back(vertexes[i]);

	return result;

}