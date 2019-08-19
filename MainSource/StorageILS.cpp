//
//  ILS.cpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#include "StorageILS.h"
#include "StorageAllocationSolution.h"
#include "StorageAllocationSolution.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "DistanceMatrix.h";
#include "Warehouse.h"
#include "Graph.h"
#include "Vertex.h"
#include "Arc.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
using namespace std; 


//////////////////////////////////////////////////////////////////////////////////////////
////                                 INSIDE SHELF SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
InsideShelfSwap::InsideShelfSwap(){

}

/**
 * 
 */
InsideShelfSwap::InsideShelfSwap(AbstractSolution *initial):base(initial){

}

/**
 * 
 */
void InsideShelfSwap::setStartSolution(AbstractSolution *) const{

}

/**
 * 
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){

}



//////////////////////////////////////////////////////////////////////////////////////////
////                                 INSIDE BLOCK SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////
InsideBlockSwap::InsideBlockSwap(){

}

InsideBlockSwap::InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh, 
                                 int randomSeed, vector<int> &products):base(initial){

    }

void InsideBlockSwap::setStartSolution(AbstractSolution *) const{

}

vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){

}



//////////////////////////////////////////////////////////////////////////////////////////
////                                 MOST FREQUENT PRODUCTS SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////
MostFrequentSwap::MostFrequentSwap(){

}

MostFrequentSwap::MostFrequentSwap(StorageAllocation *initial, int numNeigh, 
                                  int randomSeed, vector<int> &products):base(initial){


}


void MostFrequentSwap::setStartSolution(AbstractSolution *) const{

}

AbstractSolution * MostFrequentSwap::getStartSolution() const{

}

vector<AbstractSolution *> MostFrequentSwap::createNeighbors(){

}





//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation ILS region
////
/////////////////////////////////////////////////////////////////////////////////////////



StorageALlocationSolution * StorageILS::CreateInitialSolution(){

}

/**
 * 
 */
StorageAllocationSolution * StorageILS::ExecutePertubation(StorageAllocationSolution *){

}

/**
 * 
 */
void StorageILS::EvaluateSolution(AbstractSolution * solution){

}

/**
 * 
 */
 StorageILS::StorageILS(){

 }

/**
 * 
 */
StorageILS::StorageILS(StorageILS &other){

}

/**
 * 
 */
StorageILS::StorageILS(DistanceMatrix *distances, Graph *graph, Warehouse *warehouse){
    
}

/**
 * 
 */
bool StorageILS::StopCriteriaReached(){
    return this->numPertubations == MAX_PERTUBATIONS && this->numIterationsWithoutImprovement > MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}

/**
 * 
 */
StorageILS::virtual AbstractSolution * Execute(){

    this->numPertubations = 0;
    this->numIterationsWithoutImprovement = 0;

    AbstractSolution * initialSolution = CreateInitialSolution();

}

