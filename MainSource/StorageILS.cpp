//
//  ILS.cpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#include "OptimizationParameters.h"
#include "StorageILS.h"
#include "Order.h"
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
	this->startSolution = NULL; 
	this->numberOfNeighbors = 5;
	this->randomSeed = 1;
	
}

/**
 * 
 */
InsideShelfSwap::InsideShelfSwap(AbstractSolution *initial, unsigned int numNeigh, int randomSeed, Shelf &shelf):base(initial){
	this->startSolution = initial;
	this->numberOfNeighbors = numNeigh;
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
		
		pair<Cell,int> firstAllocation = (shelfAllocations.begin()+first).first; 
		pair<Cell,int> secondAllocation = (shelfAllocations.begin()+second).first; 
		
		StorageAllocation newSolution = ((StorageAllocationSolution *)this->startSolution)->proceedSwap(firstAllocation, secondAllocation); 
	}
	
}



//////////////////////////////////////////////////////////////////////////////////////////
////                                 INSIDE BLOCK SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////
InsideBlockSwap::InsideBlockSwap(){
	this->startSolution = NULL; 
	this->numberOfNeighbors = 5;
	this->randomSeed = 1;
}

/**
 * 
 */
InsideBlockSwap::InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh, int randomSeed, Block & block):base(initial){
	this->startSolution = initial;
	this->numberOfNeighbors= numNeigh;
	this->randomSeed = randomSeed;
	this->blok = block; 
	
}

/**
 * 
 */
void InsideBlockSwap::setStartSolution(AbstractSolution *initial) const{
	this->startSolution = initial;
}

/**
 * 
 */
vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	map<pair<Cell,int>, Product > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	map<pair<Cell, int> , Product> blockAllocations; 
	vector<Shelf> shelves = this->block.getShelves(); 
	
	for(int i=0;i<shelves.getLevels();i++){
		vector<Cell> cells = this->getCells();
		
		for(int j=0;j<cells.size();j++){
			int numLevels = cells[j].getLevels();
			for(int k=0;k<numLevels; k++){
				pair<Cell, int> key(cells[j],k); 
				if(allocations.find(key) != allocations.end())
					shelfAllocations[key] = allocations[key];
			}
		}		
	}
	
	//Get all allocations of the shelf
	
}



//////////////////////////////////////////////////////////////////////////////////////////
////                                 MOST FREQUENT PRODUCTS SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////
/**
 *
 */
MostFrequentSwap::MostFrequentSwap(){
	this->startSolution = NULL; 
	this->numberOfNeighbors = 5;
	this->randomSeed = 1;
}

/**
 *
 */
MostFrequentSwap::MostFrequentSwap(StorageAllocation *initial, int numNeigh, int randomSeed, vector<int> &products):base(initial){
	this->startSolution = initial;
	this->numberOfNeighbors= numNeigh;
	this->randomSeed = randomSeed;
	this->interchageableProducts = products; 
	srand(this->randomSeed); 
}

/**
 *
 */
void MostFrequentSwap::setStartSolution(AbstractSolution *initial) const{
	this->startSolution = new StorageAllocationSolution(*initial);
}

/**
 *
 */
AbstractSolution * MostFrequentSwap::getStartSolution() const{
	return this->startSolution; 
}

/**
 *
 */
vector<AbstractSolution *> MostFrequentSwap::createNeighbors(){

	vector<AbstractSolution *> solutions;
	map<pair<Cell,int>, Product > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	map<Product, pair<Cell,int> > productPosition; 
	
	for(map<pair<Cell, int> , Product >::iterator it=allocation.begin();it != allocations.end(); it++)
		productPosition[*it->second] = it->first; 
	
	if(this->interchageableProducts.size()<3)
		return solutions; 

	int first; 
	int second; 
	set<pair<int,int> >swapsDone; 
	
	
	for(int i=0;i<this->numberOfNeighbors;i++){
		first = rand()%this->interchageableProducts.size(); 
		second = rand()%this->interchageableProducts.size(); 
		
		int countTries = 0; 
		while(swapsDone.find(make_pair(first, second)) != swaps.end() || swapsDone.find(make_pair(second,first)) != swaps.end() || second == first){
			first = rand()%this->interchageableProducts.size(); 
			second = rand()%this->interchageableProducts.size(); 
			//If anti-loop
			if(countTries >= interchageableProducts.size()*interchageableProducts.size())
				break;
		}
		
		if(countTries >= interchageableProducts.size()*interchageableProducts.size())
			break;
		
		//Here we can suppose that all products in the intercheableProduct vector are allocated in the warehouses,
		//thus in the productPosition map
		pair<Cell,int> firstAllocation  = productPosition[this->interchageableProducts[first]];
		pair<Cell,int> secondAllocation = productPosition[this->interchageableProducts[second]];
			
		StorageAllocation newSolution = ((StorageAllocationSolution *)this->startSolution)->proceedSwap(firstAllocation, secondAllocation); 
		solutions.push_back(newSolution);
	}
	return solution; 
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
	InitilizeNeighborhoods();
}

/**
 * 
 */
StorageILS::StorageILS(DistanceMatrix *distances, Graph *graph, Warehouse *warehouse, vector<Order> &orders){
    this->distanceMatrix = distanceMatrix; 
	this->graph = graph; 
	this->warehouse = warehouse; 
	this->orders= orders; 
	InitilizeNeighborhoods(); 
}

/**
 * 
 */
bool StorageILS::StopCriteriaReached(){
    return this->numPertubations == OptimizationParameters::MAX_PERTUBATIONS && 
		   this->numIterationsWithoutImprovement > OptimizationParameters::MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}


/**
 * 
 */
void StorageILS::InitializeNeighborhoods(){
	this->neighborhoodStructures.push_back(new MostFrequentSwap());
	this->neighborhoodStructures.push_back(new InsideShelfSwap());
	this->neighborhoodStructures.push_back(new InsideBlockSwap());
	
}

/**
 * 
 */
StorageILS::virtual AbstractSolution * Execute(){

    this->numPertubations = 0;
    this->numIterationsWithoutImprovement = 0;
	StorageAllocationSolution *bestGlobalSolution;
	StorageAllocationSolution *currentSolution;
	double bestGlobalSolutionValue; 
	
	vector<double> thresholds;
	thresholds.push_back(OptimizationParameters::A_THRESHOLD_CLASS);
	threhsolds.push_bakc(OptimizationParameters::B_THRESHOLD_CLASS); 

	ABCAnalysis abcAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
    AbstractSolution * initialSolution = CreateInitialSolution();
	
	bestGlobalSolution = new StorageAllocationSolution( *( (StorageAllocationSolution *) initialSolution));
	bestGlobalSolutionValue = bestGlobalSolution.getSolutionValue();
	
	int randomSeed= 1;
	
	while(!StopCriteriaReached()){
		
		//Perform a local search as a VNS
		for(int i=0;i< this->neighborhoodStructures.size();i++){
			string typeName = typeid(*this->neighborhoodStructures[i]).name();
			StorageAllocationSolution *bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
			
			if(typeName == "InsideShelfSwap"){
				vector<Block> blocks = this->warehouse->getBlocks(); 
				
				for(int j=0;j<blocks.size();j++){
					vector<Shelf> shelves = this->blocks[j].getShelves();
					vector<AbstractSolution *> neighbors;
					
					for(int k=0;k<shelves.size();k++){
						((InsideShelfSwap *) this->neighborhoodStructures[i])->setShelf(shelves[k]); 
						((InsideShelfSwap *) this->neighborhoodStructures[i])->setRandomSeed(randomSeed+j*shelves.size()+k);
						((InsideShelfSwap *) this->neighborhoodStructures[i])->setNumberOfNeighbors((int)sqrt(shelves[i].getCells().size()));
						((InsideShelfSwap *) this->neighborhoodStructures[i])->setStartSolution(*currentSolution); 
						neighbors = ((InsideShelfSwap *) this->neighborhoodStructures[i])->createNeighbors(*currentSolution); 
					}
					
					double currentSolutionValue = currentSolution->getSolutionValue();
					double newSolutionValue = neighbors[k]->getSolutionValue();
					
					for(int k=0;k<neighbors.size();k++){
						newSolutionValue = neighbors[k]->getSolutionValue();
						
						//If the neighbor has a better value than the current solution value, so update the current solution
						//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
						//are not significantly better 
						if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
							delete currentSolution;
							currentSolution = new StorageAllocationSolution(*neighbors[k]);
							currentSolutionValue = currentSolution->getSolutionValue();
						}
					}
					
					
					if((currentSolutionValue-bestLocalSearchSolutionValue)*100.0/newSolutionValue <= -0.1){
						delete bestLocalSearchSolutionValue; 
						bestLocalSearchSolutionValue = new StorageAllocationSolution(*currentSolution);
						bestGlobalSolutionValue = bestLocalSearchSolutionValue->getSolutionValue();
					}
					
				}
				
				
			}else if(typeName == "InsideBlockSwap"){
			}else if(typeName == "MostFrequentSwap"){
			}

			delete currentSolution;
			currentSolution = new StorageAllocationSolution(*bestLocalSearchSolution);
		}
		randomSeed++; 
		
		
	}

}

