#include "StorageAllocationSolution.h"
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
#include "Vertex.h"
#include "Arc.h"
#include "Cell.h"
#include "StorageSolutionEvaluator.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
using namespace std;
using namespace QuickTSP; 


StorageSolutionEvaluator * StorageAllocationSolution::evaluator = new StorageSolutionEvaluator();

StorageAllocationSolution::StorageAllocationSolution(){
	
}

StorageAllocationSolution::StorageAllocationSolution(StorageAllocationSolution *other){
	this->solutionValue = other->solutionValue;
	this->runtime = other->runtime;
	this->minDelta = other->minDelta;
	isMaximization = other->isMaximization; 
}


StorageAllocationSolution::StorageAllocationSolution(double value, double time, double minDelta,bool maximization){
	this->solutionValue = value;
	this->runtime = time;
	this->minDelta = minDelta;
	isMaximization = maximization; 
}


StorageAllocationSolution::~StorageAllocationSolution(){
	
	
}

/**
 * 
 */
void StorageAllocationSolution::setMinDelta(double minDelta){
    this->minDelta = minDelta;
}

/**
 * 
 */
void StorageAllocationSolution::setRuntime(double time){
    this->runtime = time;
}

/**
 * 
 */
void StorageAllocationSolution::setSolutionValue(double value){
    this->solutionValue = value; 
}

/**
 * 
 */
void StorageAllocationSolution::printSolution() const{

}

/**
 * 
 */
void StorageAllocationSolution::printToFile(ofstream & out) const{
	out<<"Teste \n"; 
}

/**
 * 
 */
map<pair<Cell,int>, Product> & StorageAllocationSolution::getProductAllocations(){
	return this->productAllocation;
}

/**
 * 
 */
void StorageAllocationSolution::setAllocation(const Cell &cell, int level, const Product &product){
	this->productAllocation[make_pair(cell,level)] = product; 
}

/**
 * 
 */
void StorageAllocationSolution::removeAllocation(const Cell &cell, int level){
	this->productAllocation.erase(make_pair(cell, level));	
}

/**
 * 
 */
void StorageAllocationSolution::proceedSwap(pair<Cell,int> &first, pair<Cell,int> &second, bool useTSPEvaluator){
		
	Product firstProduct = productAllocation[first];
	Product secondProduct = productAllocation[second]; 
	
	productAllocation[first] = secondProduct; 
	productAllocation[second] = firstProduct;
	
	
	vector<PickingRoute *> firstRoutes = routesByProduct[firstProduct];
	vector<PickingRoute *> secondRoutes = routesByProduct[secondProduct];
	
	//if a same route has both products in the swap the evaluation don't need to be done
	for(unsigned int i=0; i<firstRoutes.size(); i++){
		if(find(secondRoutes.begin(),secondRoutes.end(), firstRoutes[i]) != secondRoutes.end())
			continue; 
		else if(useTSPEvaluator)
			firstRoutes[i]->second = evaluator->DoRouteEvaluation(firstRoutes[i]->first);
		else
			firstRoutes[i]->second = evaluator->DoRouteEstimation(firstRoutes[i]->first);
	}
	
	//if a same route has both products in the swap the evaluation don't need to be done	
	for(unsigned int i=0; i<secondRoutes.size(); i++){
		if(find(firstRoutes.begin(),firstRoutes.end(), secondRoutes[i]) != firstRoutes.end())
			continue; 
		else if(useTSPEvaluator)
			secondRoutes[i]->second = evaluator->DoRouteEvaluation(secondRoutes[i]->first);
		else
			secondRoutes[i]->second = evaluator->DoRouteEstimation(secondRoutes[i]->first);
	}
}

/**
 * 
 */
void StorageAllocationSolution::evaluateSolutionWithTSP(){
	
}

/**
 * 
 */
void StorageAllocationSolution::evaluateSolutionWithoutTSP(){
	
}

/**
 * 
 */
void StorageAllocationSolution::updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool useTSP){
	double oldSum =0;
	double newSum = 0;
	
	for(unsigned int i=0;i<oldRoutes.size(); i++)
		oldSum += oldRoutes[i].second; 
	
	for(unsigned int i=0;i<newRoutes.size();i++)
		if(useTSP)
			newSum += StorageAllocationSolution::evaluator->DoRouteEvaluation(newRoutes[i].first);
		else
			newSum += StorageAllocationSolution::evaluator->DoRouteEstimation(newRoutes[i].first);
	
	this->solutionValue += (newSum - oldSum);  
}
