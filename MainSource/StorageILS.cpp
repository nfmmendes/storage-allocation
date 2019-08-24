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
InsideShelfSwap::InsideShelfSwap(AbstractSolution *initial, unsigned int numNeigh, int randomSeed, Shelf &shelf):base(initial){
	this->startSolution = initial;
	this->numNeigh= numNeigh;
	this->randomSeed = randomSeed;
	this->shelf = shelf; 
	this->products = products; 
}

/**
 * 
 */
void InsideShelfSwap::setStartSolution(AbstractSolution *initial) const{
	this->startSolution = initial; 
}

/**
 * 
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	map<pair<Cell,int>, Product > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	vector<Cell> cells = this->shelf.getCells(); 
	map<pair<Cell, int> , Product> shelfAllocations; 
	
	
	//Get all allocations of the shelf
	for(int i=0;i<cells.size();i++){
		int numLevels = cells[i].getLevels();
		for(int j=0;j<numLevels; j++){
			pair<Cell, int> key(cells[i],j); 
			if(allocations.find(key) != allocations.end())
				shelfAllocations[key] = allocations[key];
		}
	}
	
	//It is not possible to do swaps 
	if(shelfAllocations <=2)
		return this->startSolution; 
	
	srand(this->randomSeed); 
	set<pair<int,int> > swapsDone; 
	
	int allocationsSize = shelfAllocations.size();
	int first, second; 
	for(int i=0; i< min(numNegh, allocationSize*allocationSize); i++){
	    first = rand()%allocationSize;
		second = rand()%allocationSize; 
		
		int countTries = 0; 
		while(swapsDone.find(make_pair(first, second)) != swaps.end() || swapsDone.find(make_pair(second,first)) != swaps.end() || second == first){
			first = rand()%allocationSize;
			second = rand()%allocationSize; 
			if(countTries >= shelfAllocations*shelfAllocations)
				break;
		}
		
		if(countTries >= shelfAllocations*shelfAllocations)
			break;
		
		pair<Cell,int> firstCell = (shelfAllocations.begin()+first).first; 
		pair<Cell,int> secondAllocation = (shelfAllocations.begin()+second).first; 
		
		StorageAllocation newSolution = ((StorageAllocationSolution *)this->startSolution)->proceedSwap(firstCell, secondCell); 
	}
	
}



//////////////////////////////////////////////////////////////////////////////////////////
////                                 INSIDE BLOCK SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////
InsideBlockSwap::InsideBlockSwap(){

}

InsideBlockSwap::InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh, 
                                 int randomSeed, Block & block):base(initial){

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

