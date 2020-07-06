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
#include "StorageConstructiveHeuristic.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "DistanceMatrix.h"
#include "Warehouse.h"
#include "OptimizationConstraints.h"
#include "Vertex.h"
#include "Order.h"
#include "Arc.h"
#include "ABCAnalysis.h"
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

InsideShelfSwap::~InsideShelfSwap(){

}

/**
 * 
 */
InsideShelfSwap::InsideShelfSwap(AbstractSolution *initial, unsigned int numNeigh, int randomSeed, Shelf &shelf){
	this->startSolution = initial;
	this->numberOfNeighbors = numNeigh;
	this->randomSeed = randomSeed;
	this->shelf = shelf; 
	//this->products = products; 
}


/**
 * 
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	map<Product , pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	vector<Cell> cells = this->shelf.getCells(); 
	map<pair<Cell, int> , Product> shelfAllocations; 
	vector<AbstractSolution *> solutions; 
	
	
	for(const auto &[product, position] : allocations){
		if(position.first.getIdShelf() != shelf.getId())
			continue; 
		//int numLevels = position.second;
		shelfAllocations[position] = product;
	}
	
	//It is not possible to do swaps 
	if(shelfAllocations.size() <=2)
		return solutions;
	
	srand(this->randomSeed); 
	set<pair<int,int> > swapsDone; 
	
	int allocationsSize = shelfAllocations.size();
	int first, second; 
	for(unsigned int i=0; i< min(numberOfNeighbors, ((unsigned int) allocationsSize*allocationsSize) ); i++){
	    first = rand()%allocationsSize;
		second = rand()%allocationsSize; 
		
		int countTries = 0; 
		while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
			first = rand()%allocationsSize;
			second = rand()%allocationsSize; 
			if( ((unsigned int) countTries) >= shelfAllocations.size()*shelfAllocations.size())
				break;
		}
		
		if(((unsigned int) countTries) >= shelfAllocations.size()*shelfAllocations.size())
			break;
		
		map< pair<Cell, int> , Product>::iterator it = shelfAllocations.begin();
		advance(it,first); 
		Product firstProduct = it->second; 
		
		it = shelfAllocations.begin(); 
		advance(it,second); 
		Product secondProduct = it->second; 
		
		StorageAllocationSolution *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution); 
		newSolution->proceedSwap(firstProduct, secondProduct); 
	}
	
	return solutions;
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

InsideBlockSwap::~InsideBlockSwap(){


}

/**
 * 
 */
InsideBlockSwap::InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh, int randomSeed, Block & block){
	this->startSolution = initial;
	this->numberOfNeighbors= numNeigh;
	this->randomSeed = randomSeed;
	this->block = block; 
	
}


/**
 * 
 */
vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	map<Product, pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	map<pair<Cell, int> , Product> blockAllocations; 
	vector<Shelf> shelves = this->block.getShelves(); 
	vector<AbstractSolution *> solutions; 
	
	for(unsigned int i=0;i<shelves.size();i++){
		vector<Cell> cells = shelves[i].getCells();
		
		for(unsigned int j=0;j<cells.size();j++){
			int numLevels = cells[j].getLevels();
			for(int k=0;k<numLevels; k++){
				pair<Cell, int> key(cells[j],k); 
				//TODO: Remember how it works 
			//	if(allocations.find(key) != allocations.end())
			//		shelfAllocations[key] = allocations[key];
			}
		}		
	}
	
	//Get all allocations of the shelf
	return solutions;
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

MostFrequentSwap::~MostFrequentSwap(){

	
}

/**
 *
 */
MostFrequentSwap::MostFrequentSwap(StorageAllocationSolution *initial, int numNeigh, int randomSeed, vector<Product> &products){
	this->startSolution = initial;
	this->numberOfNeighbors= numNeigh;
	this->randomSeed = randomSeed;
	this->interchangeableProducts = products; 
	srand(this->randomSeed); 
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
	map< Product, pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	
	if(this->interchangeableProducts.size()<3)
		return solutions; 

	int first; 
	int second; 
	set<pair<int,int> >swapsDone; 
	
	
	for(int i=0;i<this->numberOfNeighbors;i++){
		first = rand()%this->interchangeableProducts.size(); 
		second = rand()%this->interchangeableProducts.size(); 
		
		int countTries = 0; 
		while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
			first = rand()%this->interchangeableProducts.size(); 
			second = rand()%this->interchangeableProducts.size(); 
			//If anti-loop
			if(  ((unsigned int)countTries) >=  interchangeableProducts.size()*interchangeableProducts.size())
				break;
		}
		
		if( ((unsigned int)countTries) >= interchangeableProducts.size()*interchangeableProducts.size())
			break;
			
		StorageAllocationSolution * newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution);
		newSolution->proceedSwap(this->interchangeableProducts[first], this->interchangeableProducts[second]); 
		
		solutions.push_back(newSolution);
	}
	return solutions; 
}



//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation ILS region
////
/////////////////////////////////////////////////////////////////////////////////////////
StorageILS::StorageILS(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> &distMatrix,
					   map<pair<Cell, int>, Vertex> vertexByCell, vector<Order> &orders, OptimizationConstraints &cons){
	this->distanceMatrix = &distMatrix; 
	this->warehouse = &wh; 
	this->orders= orders; 
	this->vertexByCell = vertexByCell; 
	this->constraints = cons; 
	this->products = prods; 
	InitializeNeighborhoods(); 
	
}


/**
 *	Create a initial product allocation based on the ABC class of each product and the distance 
 *  between each cell and the closest delivery point  
 */
StorageAllocationSolution * StorageILS::CreateInitialSolution(){
	StorageAllocationSolution *initial = new StorageAllocationSolution();
	
	
	StorageConstructiveHeuristic constr(this->products,*warehouse,*distanceMatrix,vertexByCell, orders,constraints); 
	StorageAllocationSolution constructiveSolution = constr.Execute();


	return initial; 
}

/**
 * 
 */
StorageAllocationSolution * StorageILS::ExecutePertubation(StorageAllocationSolution *_currentSolution){
	double value = _currentSolution->getSolutionValue();
//	cout<<value<<endl;
	return NULL;
}

/**
 * 
 */
void StorageILS::EvaluateSolution(AbstractSolution * solution){
	double value = solution->getSolutionValue(); 
	//cout<<value<<endl;
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
	this->distanceMatrix = other.distanceMatrix;
	this->warehouse = other.warehouse;
	this->orders = other.orders; 
	InitializeNeighborhoods();
}

/**
 * 
 */
bool StorageILS::StopCriteriaReached(){
	
    return this->numPertubations >= OptimizationParameters::MAX_PERTUBATIONS && 
		   this->numIterationsWithoutImprovement >= OptimizationParameters::MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}


/**
 * 
 */
void StorageILS::InitializeNeighborhoods(){
	this->neighborhoodStructures.push_back(new MostFrequentSwap());
	this->neighborhoodStructures.push_back(new InsideShelfSwap());
	this->neighborhoodStructures.push_back(new InsideBlockSwap());
	
}

void StorageILS::SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){

}


void StorageILS::SwapInsideBlockLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	vector<Block> blocks = this->warehouse->getBlocks(); 
				
	for(unsigned int j=0;j<blocks.size();j++){
		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;
		

		((InsideBlockSwap *) neighborhoodStructure)->setBlock(blocks[j]); 
		((InsideBlockSwap *) neighborhoodStructure)->setRandomSeed(randomSeed+j*shelves.size());
		((InsideBlockSwap *) neighborhoodStructure)->setNumberOfNeighbors((int)sqrt(blocks[j].getShelves().size()));
		neighborhoodStructure->setStartSolution(currentSolution); 
		neighbors = ((InsideShelfSwap *) neighborhoodStructure)->createNeighbors(); 
	
		
		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();
		
		for(unsigned int k=0;k<neighbors.size();k++){
			newSolutionValue = neighbors[k]->getSolutionValue();
			
			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete currentSolution;
				currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[k]);
				currentSolutionValue = currentSolution->getSolutionValue();
			}
		}
	}
}


void StorageILS::SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	vector<Block> blocks = this->warehouse->getBlocks(); 
				
	for(unsigned int j=0;j<blocks.size();j++){
		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;
		
		for(unsigned int k=0;k<shelves.size();k++){
			((InsideShelfSwap *) neighborhoodStructure)->setShelf(shelves[k]); 
			((InsideShelfSwap *) neighborhoodStructure)->setRandomSeed(randomSeed+j*shelves.size()+k);
			((InsideShelfSwap *) neighborhoodStructure)->setNumberOfNeighbors((int)sqrt(shelves[k].getCells().size()));
			neighborhoodStructure->setStartSolution(currentSolution); 
			neighbors = ((InsideShelfSwap *) neighborhoodStructure)->createNeighbors(); 
		}
		
		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();
		
		for(unsigned int k=0;k<neighbors.size();k++){
			newSolutionValue = neighbors[k]->getSolutionValue();
			
			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete currentSolution;
				currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[k]);
				currentSolutionValue = currentSolution->getSolutionValue();
			}
		}
	}
}



/**
 * 
 */
AbstractSolution * StorageILS::Execute(){

    this->numPertubations = 0;
    this->numIterationsWithoutImprovement = 0;
	double bestGlobalSolutionValue; 
	
	vector<double> thresholds;
	thresholds.push_back(OptimizationParameters::A_THRESHOLD_CLASS);
	thresholds.push_back(OptimizationParameters::B_THRESHOLD_CLASS); 

	ABCAnalysis abcAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
    AbstractSolution * initialSolution = CreateInitialSolution();
	
	StorageAllocationSolution * bestGlobalSolution = new StorageAllocationSolution( *( (StorageAllocationSolution *) initialSolution));
	StorageAllocationSolution * currentSolution = new StorageAllocationSolution(bestGlobalSolution); 
	bestGlobalSolutionValue = bestGlobalSolution->getSolutionValue();
	cout<<"Best value :"<<bestGlobalSolutionValue<<endl; 
	int randomSeed= 1;
	
	while(!StopCriteriaReached()){
		

		StorageAllocationSolution *bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
		StorageAllocationSolution *originalSolution = new StorageAllocationSolution(*currentSolution);
		double bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue();

		//Perform a local search as a VNS
		for(unsigned int i=0;i< this->neighborhoodStructures.size();i++){
			string typeName = typeid(*this->neighborhoodStructures[i]).name();
			
			delete currentSolution;
			currentSolution = new StorageAllocationSolution(*originalSolution);
			double currentSolutionValue = currentSolution->getSolutionValue();
			double newSolutionValue = 0;
		
			if(typeName == "InsideShelfSwap"){	
				SwapInsideShelfLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = currentSolution->getSolutionValue();	
			}else if(typeName == "InsideBlockSwap"){
				SwapInsideBlockLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				double newSolutionValue = currentSolution->getSolutionValue();

			}else if(typeName == "MostFrequentSwap"){
				SwapMostFrequentLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = currentSolution->getSolutionValue();
			}

			if((newSolutionValue-bestLocalSearchSolutionValue)*100.0/bestLocalSearchSolutionValue <= -0.1){
				delete bestLocalSearchSolution; 
				bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
				bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue(); 
			}

			this->numPertubations++;
	
			
		}
		
		this->numIterationsWithoutImprovement++;
		if((bestLocalSearchSolutionValue - bestGlobalSolutionValue)*100/bestGlobalSolutionValue <= -0.1){
			delete bestGlobalSolution;
			bestGlobalSolution = new StorageAllocationSolution(bestLocalSearchSolution);
			bestGlobalSolutionValue = bestLocalSearchSolution->getSolutionValue();
			this->numIterationsWithoutImprovement = 0; 
		}

		delete currentSolution;
		currentSolution = new StorageAllocationSolution(bestLocalSearchSolution);
		randomSeed++; 
		
	}

	return bestGlobalSolution;
}

