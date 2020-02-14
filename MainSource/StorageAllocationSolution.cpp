#include "StorageAllocationSolution.h"
#include <iotream>
#include <vector>
#include <string> 
#include <cmath>
#include "Vertex.h"
#include "Arc.h"
#include "StorageAllocationSolution.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
using namespace std;
using namespace QuickTSP; 

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
void StorageAllocationSolution::printToFile(const ofstream & out) const{

}

/**
 * 
 */
map<pair<Cell,int>, Product> & StorageAllocationSolution::getProductAllocation() const{
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
void StorageAllocationSolution::proceedSwap(map<Cell,int> &first, map<Cell,int> &second, bool useTSPEvaluator){
		
	Product firstProduct = productAllocation[first];
	Product secondProduct = productAllocation[second]; 
	
	productAllocation[first] = second; 
	productAllocation[second] = first;
	
	
	vector<PickingRoute *> firstRoutes = routesByProduct[first];
	vector<PickingRoute *> secondRoutes = routesByProduct[second];
	
	//if a same route has both products in the swap the evaluation don't need to be done
	for(int i=0; i<firstRoutes.size(); i++){
		if(find(secondRoutes.begin(),secondRoutes.end(), firstRoutes[i]->first) != secondRoutes.end())
			continue; 
		else if(useTSP)
			firstRoutes[i]->second = evaluator->DoRouteEvaluation(firstRoutes[i]->first);
		else
			firstRoutes[i]->second = evaluator->DoRouteEvaluation(firstRoutes[i]->second);
	}
	
	//if a same route has both products in the swap the evaluation don't need to be done	
	for(int i=0; i<secondRoutes.size(); i++){
		if(find(firstRoutes.begin(),firstRoutes.end(), secondRoutes[i]->first) != firstRoutes.end())
			continue; 
		else if(useTSP)
			secondRoutes[i]->second = evaluator->DoRouteEvaluation(secondRoutes[i]->first);
		else
			secondRoutes[i]->second = evaluator->DoRouteEvaluation(secondRoutes[i]->second);
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
	doublle newSum = 0;
	
	for(int i=0;i<oldRoutes.size(); i++)
		oldSum += oldRoutes[i].second; 
	
	for(int i=0;i<newRoutes.size();i++)
		newSum += StorageAllocationSolution::evaluator.evaluateRoute(newRoutes[i], useTSP);
	
	this->solutionValue += (newSum - oldSum);  
}
