#include "StorageAllocationSolution.h"
#include <iotream>
#include <vector>
#include <string> 
#include <cmath>
using namespace std;

/**
 * 
 */
void StorageAllocationSolution::etMinDelta(double minDelta){
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