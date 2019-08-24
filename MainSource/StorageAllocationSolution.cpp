#include "StorageAllocationSolution.h"
#include <iotream>
#include <vector>
#include <string> 
#include <cmath>
using namespace std;

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
void StorageAllocationSolution::proceedSwap(map<Cell,int> &first, map<Cell,int> &second, bool useTSP){
	
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
