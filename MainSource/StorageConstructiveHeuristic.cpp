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

void StorageConstructiveHeuristic::InitializeAuxiliaryDataStructures(){
	
	
}


bool StorageConstructiveHeuristic::StopCriteriaReached(){
	
	return false; 
}

bool StorageConstructiveHeuristic::isNotForbiddenStore(Product &product, Vertex &vertex){
	
}

bool StorageConstructiveHeuristic::hasConstraints(Product &prod){
	
}

void StorageConstructiveHeuristic::EvaluateSolution(AbstractSolution * solution){
	
	
	TSP tsp(*distanceMatrix); 
	vector<pair<Product, double> > items; 
	vector<Vertex> storagePoints; 
	
	for(unsigned int i=0;i< orders.size();i++){
		items = orders[i].getOrderItems(); 
		storagePoints.clear();
		
		for(unsigned int j = 0; j<items.size();j++){
			
		}
	}
		
	
}

StorageAllocationSolution * StorageConstructiveHeuristic::Execute(){
	
	map<string, vector<Vertex> > vertexByType = getVertexesByType(); 
	map<Vertex,Product> allocation; 
	
	//vector<Vertex> expeditionPoints = vertexByType["ExpeditionPointVertex"]; 
	vector<Vertex> storePoints;// = getStorePoints();
	
	vector<Vertex> vertexesOrderedByDistance = getStorageVertexesOrderedByDistance(); 
	vector<pair< Product , int> > productsByFrequence = getProductOrderByFrequence();

	vector<bool> usedVertex; 
	int lastOnSequence = 0; 
	usedVertex.resize(vertexByCell.size(), false); 
	for(auto & item : productsByFrequence){
		if(!hasConstraints(item.first)){
			while(usedVertex[lastOnSequence])lastOnSequence++;
			usedVertex[lastOnSequence] = true; 
			allocation[vertexesOrderedByDistance[lastOnSequence]] = item.first; 
		}else{
			int tryInsertIndex = lastOnSequence; 
			while(!isNotForbiddenStore(item.first, vertexesOrderedByDistance[tryInsertIndex]) || usedVertex[tryInsertIndex]) 
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
	///ExpeditionPointVertex
}