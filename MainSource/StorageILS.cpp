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

bool InsideShelfSwap::ChooseTwoProductIndexes(int &first, int &second, int allocationsSize, const set<pair<int,int> > & swapsDone){
	first = rand()%allocationsSize;
	second = rand()%allocationsSize; 
	
	int countTries = 0; 
	while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
		first = rand()%allocationsSize;
		second = rand()%allocationsSize; 
		if( countTries >= allocationsSize*allocationsSize)
			break;
	}

	return countTries < allocationsSize*allocationsSize;
}


/**
 * 
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	map<Product , pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	map<pair<Cell, int> , Product> shelfAllocations; 
	vector<AbstractSolution *> solutions; 
	srand(this->randomSeed); 

	for(auto &[product, position] : allocations){
		if(position.first.getIdShelf() == shelf.getId())
			shelfAllocations[position] = product;
	}
	
	//It is not possible to do swaps 
	int allocationsSize = shelfAllocations.size();
	if(shelfAllocations.size() <=2)
		return solutions;
	
	set<pair<int,int> > swapsDone; 
	int first, second; 

	for(unsigned int i=0; i< min(numberOfNeighbors, ((unsigned int) (allocationsSize-1)*allocationsSize) ); i++){
		if(!ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		map< pair<Cell, int> , Product>::iterator it = shelfAllocations.begin();
		advance(it,first); 
		Product firstProduct = it->second; 
		
		it = shelfAllocations.begin(); 
		advance(it,second); 
		Product secondProduct = it->second; 
		
		StorageAllocationSolution *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution); 
		newSolution->proceedSwap(firstProduct, secondProduct,true); 
		
		solutions.push_back(newSolution); 
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

bool InsideBlockSwap::ChooseTwoProductIndexes(int &first, int &second, int allocationsSize, const set<pair<int,int> > & swapsDone){
	first = rand()%allocationsSize;
	second = rand()%allocationsSize; 
	
	int countTries = 0; 
	while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
		first = rand()%allocationsSize;
		second = rand()%allocationsSize; 
		if( countTries >= allocationsSize*allocationsSize)
			break;
	}

	return countTries < allocationsSize*allocationsSize;
}


/**
 * 
 */
vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	map<Product, pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	map<pair<Cell, int> , Product> blockAllocations; 
	vector<Shelf> shelves = this->block.getShelves(); 
	vector<AbstractSolution *> solutions; 
	set<long> shelfIds; 

	for(unsigned int i=0; i < shelves.size(); i++)
		shelfIds.insert(shelves[i].getId()); 


	for(auto &[product, position] : allocations){
		if(shelfIds.find(position.first.getIdShelf()) != shelfIds.end())
			blockAllocations[position] = product;
	}

	int allocationsSize = blockAllocations.size();
	if(allocationsSize <=2)
		return solutions;
	
	set<pair<int,int> > swapsDone; 
	int first, second; 

	for(unsigned int i=0; i< min(numberOfNeighbors, (allocationsSize-1)*allocationsSize) ; i++){
		if(!ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		map< pair<Cell, int> , Product>::iterator it = blockAllocations.begin();
		advance(it,first); 
		Product firstProduct = it->second; 
		
		it = blockAllocations.begin(); 
		advance(it,second); 
		Product secondProduct = it->second; 
		
		StorageAllocationSolution *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution); 
		newSolution->proceedSwap(firstProduct, secondProduct,true); 
		
		solutions.push_back(newSolution); 
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
 **/
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
	int numInterchangeableProducts = this->interchangeableProducts.size(); 
	
	for(int i=0;i<this->numberOfNeighbors;i++){
		first = rand()%numInterchangeableProducts; 
		second = rand()%numInterchangeableProducts; 
		
		int countTries = 0; 
		while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
			first = rand()%numInterchangeableProducts; 
			second = rand()%numInterchangeableProducts; 
			//If anti-loop
			if( countTries >=  numInterchangeableProducts*numInterchangeableProducts)
				break;
		}
		
		if( countTries >= numInterchangeableProducts)
			break;
			
		StorageAllocationSolution * newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution);
		newSolution->proceedSwap(this->interchangeableProducts[first], this->interchangeableProducts[second]); 
		
		solutions.push_back(newSolution);
	}
	return solutions; 
}

//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation pertubation region
////
/////////////////////////////////////////////////////////////////////////////////////////
AbstractSolution * StorageAllocationPertubation::getStartSolution() const{
	return this->startSolution; 
} 

vector<AbstractSolution *> StorageAllocationPertubation::createNeighbors(){
	vector<AbstractSolution *> solutions;	
	
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

	StorageConstructiveHeuristic constr(this->products,*warehouse,*distanceMatrix,vertexByCell, orders,constraints); 
	return  constr.Execute(); 
}

/**
 * 
 */
StorageAllocationSolution * StorageILS::ExecutePertubation(StorageAllocationSolution *_currentSolution){
	//double value = _currentSolution->getSolutionValue();
//	cout<<value<<endl;
	return NULL;
}

/**
 * 
 */
void StorageILS::EvaluateSolution(AbstractSolution * solution){
	((StorageAllocationSolution *)solution)->Evaluate(true);
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
	
	neighborhoodType.push_back("MostFrequentSwap");
	neighborhoodType.push_back("InsideShelfSwap");
	neighborhoodType.push_back("InsideBlockSwap");

}

/**
 * Class constructor
 **/
void StorageILS::SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	
	int maxNumberSwaps = 0.10*products.size(); 
	for(int i=0; i <maxNumberSwaps; i++){
		vector<AbstractSolution *> neighbors;
		((MostFrequentSwap *) neighborhoodStructure)->setRandomSeed(randomSeed*products.size()+i);
		neighborhoodStructure->setStartSolution(currentSolution); 
		neighbors = ((MostFrequentSwap *) neighborhoodStructure)->createNeighbors(); 
	}
	
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
		neighbors = ((InsideBlockSwap *) neighborhoodStructure)->createNeighbors(); 
	
		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();

		for(unsigned int k=0;k<neighbors.size();k++){
			newSolutionValue = neighbors[k]->getSolutionValue();
			
			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete currentSolution;
				currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[k]);
				currentSolutionValue = currentSolution->getSolutionValue();
			}
		}
	}
	cout<<"Current solution value : "<<currentSolution->getSolutionValue()<< endl; 
}

/**
 * 
 * */
void StorageILS::SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	vector<Block> blocks = this->warehouse->getBlocks(); 

			
	for(unsigned int j=0;j<blocks.size();j++){
		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;
		
		for(unsigned int k=0;k<shelves.size();k++){
			((InsideShelfSwap *) neighborhoodStructure)->setShelf(shelves[rand()%shelves.size()]); 
			((InsideShelfSwap *) neighborhoodStructure)->setRandomSeed(randomSeed+j*shelves.size()+k);
			((InsideShelfSwap *) neighborhoodStructure)->setNumberOfNeighbors((int)sqrt(shelves[k].getCells().size()));
			neighborhoodStructure->setStartSolution(currentSolution); 
			neighbors = ((InsideShelfSwap *) neighborhoodStructure)->createNeighbors(); 
		
			double currentSolutionValue = currentSolution->getSolutionValue();
			double newSolutionValue = neighbors[0]->getSolutionValue();
			for(unsigned int w=0;w<neighbors.size();w++){
				newSolutionValue = neighbors[w]->getSolutionValue(); 
				//If the neighbor has a better value than the current solution value, so update the current solution
				//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
				//are not significantly better 
				cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
				if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
					delete currentSolution;
					currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[w]);
					currentSolutionValue = currentSolution->getSolutionValue();
				}
			}
		}
	}
	cout<<"Current solution value : "<<currentSolution->getSolutionValue()<< endl; 
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
	int randomSeed= 1;
	
	while(!StopCriteriaReached()){
		
		
		StorageAllocationSolution *bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
		StorageAllocationSolution *originalSolution = new StorageAllocationSolution(*currentSolution);
		double bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue();
		
		//Perform a local search as a VNS
		for(unsigned int i=0;i< this->neighborhoodStructures.size();i++){
			
			delete currentSolution;
			
			currentSolution = new StorageAllocationSolution(*originalSolution);
			double currentSolutionValue = currentSolution->getSolutionValue();
			double newSolutionValue = 0;
			
			if(neighborhoodType[i] == "InsideShelfSwap"){	
				
				SwapInsideShelfLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = currentSolution->getSolutionValue();	
			}else if(neighborhoodType[i] == "InsideBlockSwap"){
				
				SwapInsideBlockLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				double newSolutionValue = currentSolution->getSolutionValue();

			}else if(neighborhoodType[i] == "MostFrequentSwap"){
				currentSolution = new StorageAllocationSolution(*originalSolution);currentSolution = new StorageAllocationSolution(*originalSolution);
				continue; 
				
				SwapMostFrequentLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = currentSolution->getSolutionValue();
			}

			if((newSolutionValue-bestLocalSearchSolutionValue)*100.0/bestLocalSearchSolutionValue <= -0.1){
				
				delete bestLocalSearchSolution; 
				bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
				bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue(); 
			}
			cout<<"Pertubation \n"<<this->numPertubations<<"\tValue:"<<currentSolution->getSolutionValue()<<endl; 
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
	
	cout<<"End function"<<endl;
	return bestGlobalSolution;
}

