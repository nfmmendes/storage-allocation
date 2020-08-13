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
#include "StorageSolutionEvaluator.h"
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
#include "Util.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
#include <chrono>
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
	delete startSolution;
}

/**
 * 
 */
InsideShelfSwap::InsideShelfSwap(AbstractSolution *initial, OptimizationConstraints *constr, Shelf &shelf){
	this->startSolution = initial;
	this->shelf = shelf; 
	this->constraints = constr;
	//this->products = products; 
}

/**
 * 
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	map<Product , pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
 
	vector<AbstractSolution *> solutions; 
	srand(this->randomSeed); 

	//It is not possible to do swaps 
	int allocationsSize = shelfAllocations.size();
	
	if(shelfAllocations.size() <=2)
		return solutions;
	
	set<pair<int,int> > swapsDone; 
	int first, second; 
	
	for(unsigned int i=0; i< min(numberOfNeighbors, ((unsigned int) (allocationsSize-1)*allocationsSize) ); i++){
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		map< Position , Product>::iterator it = shelfAllocations.begin();
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
		delete startSolution;
}

/**
 * 
 */
InsideBlockSwap::InsideBlockSwap(StorageAllocationSolution *initial, OptimizationConstraints * constr, Block & block){
	this->startSolution = initial;
	this->constraints = constr;
	this->block = block; 
	
}


/**
 * 
 */
vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	map<Product, pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	blockAllocations.clear(); 
	
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
	
	int numIterations = min(numberOfNeighbors, (allocationsSize-1)*allocationsSize);
	for( int i=0; i< numIterations; i++){
	
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
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
	delete startSolution;
}

/**
 *
 */
MostFrequentSwap::MostFrequentSwap(StorageAllocationSolution *initial, OptimizationConstraints *constr, vector<Product> &products){
	this->startSolution = initial;
	this->interchangeableProducts = products; 
	this->constraints = constr; 
}

/**
 *
 **/
AbstractSolution * MostFrequentSwap::getStartSolution() const{
	return this->startSolution; 
}

/**
 *
 **/
vector<AbstractSolution *> MostFrequentSwap::createNeighbors(){

	vector<AbstractSolution *> solutions;
	MapAllocation allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();

	if(this->interchangeableProducts.size()<3)
		return solutions; 

	int first; 
	int second; 
	set<pair<int,int> >swapsDone; 
	int numInterchangeableProducts = this->interchangeableProducts.size(); 
	StorageAllocationSolution * newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution);

	for(int i=0;i<this->numberOfNeighbors;i++){
		if(!Util::ChooseTwoProductIndexes(first ,second,numInterchangeableProducts, swapsDone))
			break;
		newSolution->proceedSwap(this->interchangeableProducts[first], this->interchangeableProducts[second],true); 
		solutions.push_back(newSolution);
	}
	
	return solutions; 
}

//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation pertubation region
/////////////////////////////////////////////////////////////////////////////////////////
AbstractSolution * StorageAllocationPertubation::getStartSolution() const{
	return this->startSolution; 
} 

/**
 * Function to control if a 
 * */
bool StorageAllocationPertubation::isValidSwap(Product &first, Product &second, MapAllocation &allocations){
	string firstFamily = first.getFamily(); 
	string secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	if(allocations.find(first) != allocations.end() || allocations.find(second) == allocations.end() )
		return false; 

	//Check the prohibitions
	Position firstPosition =  allocations[first];
	Position secondPosition = allocations[second];
	set<string> prohibitedProducts = this->constraints->getProductsCodeWithProhibition(); 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = this->constraints->IsAllocationAllowed(first, secondPosition);
		bool isSecondAllowed = this->constraints->IsAllocationAllowed(second, firstPosition);

		if(!isFirstAllowed || !isSecondAllowed)
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	auto stronglyIsolatedFamilies = this->constraints->getStronglyIsolatedFamilyCodes(); 
	if(stronglyIsolatedFamilies.find(firstFamily) == stronglyIsolatedFamilies.end() && 
	   stronglyIsolatedFamilies.find(secondFamily) == stronglyIsolatedFamilies.end())
			return true; 

	/**
	 * 
	 * */
	if(firstPosition.first.getCode() == secondPosition.first.getCode())
		return true; 
	
	return false;  
}

/**
 * 
 * */
vector<AbstractSolution *> StorageAllocationPertubation::createNeighbors(){
	vector<AbstractSolution *> solutions;	
	int first, second;
	int numIterations = interchangeableProducts.size()/20;  
	set<pair<int,int> > swapsDone;
	int numTries=0; 

	StorageAllocationSolution *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution); 
	auto allocations = newSolution->getProductAllocations(); 

	for( int i=0; i<  numIterations; i++){
		if(!Util::ChooseTwoProductIndexes(first ,second,interchangeableProducts.size(), swapsDone) || ++numTries > 2*numIterations                                                                                                                                                        )
			break;

		Product firstProduct  = interchangeableProducts[first]; 
		Product secondProduct = interchangeableProducts[second];

		bool isValid = isValidSwap(firstProduct, secondProduct, allocations); 

		if(!isValid){
			i--;
			continue; 
		}

		newSolution->proceedSwap(firstProduct, secondProduct,true); 
		 allocations = newSolution->getProductAllocations();		
	}
	solutions.push_back(newSolution); 
	return solutions; 	
}


//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation isolated family swap region
////
/////////////////////////////////////////////////////////////////////////////////////////
IsolatedFamilySwap::IsolatedFamilySwap(){
	
}

IsolatedFamilySwap::~IsolatedFamilySwap(){

}

IsolatedFamilySwap::IsolatedFamilySwap(StorageAllocationSolution *initial, OptimizationConstraints *constr, vector<Product> &products){
	this->startSolution = new StorageAllocationSolution(initial);
	this->interchangeableProducts = products; 
	this->constraints = constr; 
}
AbstractSolution * IsolatedFamilySwap::getStartSolution() const{
	return startSolution; 
}

vector<AbstractSolution *> IsolatedFamilySwap::createNeighbors(){
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
	this->productClasses = getProductABCClasses();
	
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
	this->productClasses = getProductABCClasses();
	InitializeNeighborhoods();
}

/**
 * 
 */
bool StorageILS::StopCriteriaReached(){
    return  this->numIterationsWithoutImprovement >= OptimizationParameters::MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}


/**
 * 
 */
void StorageILS::InitializeNeighborhoods(){
	this->neighborhoodStructures.push_back(new MostFrequentSwap());
	this->neighborhoodStructures.push_back(new InsideShelfSwap());
	this->neighborhoodStructures.push_back(new InsideBlockSwap());
	this->neighborhoodStructures.push_back(new IsolatedFamilySwap());

	((MostFrequentSwap   *) (this->neighborhoodStructures[0]))->setOptimizationConstraints(&constraints);
	((InsideShelfSwap    *) (this->neighborhoodStructures[1]))->setOptimizationConstraints(&constraints);
	((InsideBlockSwap    *) (this->neighborhoodStructures[2]))->setOptimizationConstraints(&constraints);
	((IsolatedFamilySwap *) (this->neighborhoodStructures[3]))->setOptimizationConstraints(&constraints);
	
	neighborhoodType.push_back("MostFrequentSwap");
	neighborhoodType.push_back("InsideShelfSwap");
	neighborhoodType.push_back("InsideBlockSwap");
	neighborhoodType.push_back("IsolatedFamilySwap"); 
}

/**
 * 
 **/
AbstractSolution * StorageILS::SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	
	vector<Product> mostFrequentProducts;
	for(auto &[product, cl]: productClasses)
		if(cl == 'A')
			mostFrequentProducts.push_back(product);

	int maxNumberSwaps = sqrt(mostFrequentProducts.size()); 
	for(int i=0; i <maxNumberSwaps; i++){
		vector<AbstractSolution *> neighbors;
		((MostFrequentSwap *) neighborhoodStructure)->setRandomSeed(randomSeed*products.size()+i);
		((MostFrequentSwap *) neighborhoodStructure)->setNumberOfNeighbors( mostFrequentProducts.size()/4 );
		((MostFrequentSwap *) neighborhoodStructure)->setInterchangeableProducts( mostFrequentProducts);
		neighborhoodStructure->setStartSolution(currentSolution); 
		neighbors = ((MostFrequentSwap *) neighborhoodStructure)->createNeighbors(); 
		cout<<"Neighbors size: " << neighbors.size()<<endl;

		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();
		for(unsigned int k=0;k<neighbors.size();k++){
			newSolutionValue = neighbors[k]->getSolutionValue();
			//cout<<"Neighbor "<<k<<"\t value: "<<newSolutionValue<<endl;
			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			//cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete currentSolution;
				currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[k]);
				currentSolutionValue = currentSolution->getSolutionValue();
			}

			delete neighbors[k];
		}
		
	}
	//cout<<"Current solution value Most frequent: "<<currentSolution->getSolutionValue()<< endl; 
	return currentSolution; 
}

/**
 * 
 **/
AbstractSolution * StorageILS::SwapInsideBlockLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
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
			//cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete currentSolution;
				currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[k]);
				currentSolutionValue = currentSolution->getSolutionValue();
			}

			delete neighbors[k];
		}
	}
 
	return currentSolution;
}

/**
 * 
 * */
AbstractSolution * StorageILS::SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	
	vector<Block> blocks = this->warehouse->getBlocks(); 
	map<Product, Position > allocations = ((StorageAllocationSolution *) currentSolution)->getProductAllocations();
	map<long, map<Position,Product> > shelfAllocations; 
	
	for(auto &[product, position] : allocations)
		shelfAllocations[position.first.getIdShelf()][position] = product;
	
	for(unsigned int j=0;j<blocks.size();j++){
		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;
	
		for(unsigned int k=0;k<shelves.size();k++){
			int indexShelf = rand()%shelves.size();
			((InsideShelfSwap *) neighborhoodStructure)->setShelf(shelves[indexShelf]);
			((InsideShelfSwap *) neighborhoodStructure)->setShelfAllocations(shelfAllocations[shelves[indexShelf].getId()]); 
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
				//cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
				if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
					delete currentSolution;
					currentSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbors[w]);
					currentSolutionValue = currentSolution->getSolutionValue();
				}

				delete neighbors[w];
			}
		}
	}

	//cout<<"Current solution value inside Shelf: "<<currentSolution->getSolutionValue()<<" "<<currentSolution<< endl; 
	return currentSolution;
}

AbstractSolution * StorageILS::RunPerturbation(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure){

	((StorageAllocationPertubation *) neighborhoodStructure)->setInterchangeableProducts(products); 
	((StorageAllocationPertubation *) neighborhoodStructure)->setNumberOfNeighbors(1);
	neighborhoodStructure->setStartSolution(currentSolution); 
	vector<AbstractSolution *> neighbors = ((StorageAllocationPertubation *) neighborhoodStructure)->createNeighbors(); 

	return neighbors[0]; 
}

/**
 * 
 * */
map<Product, char> StorageILS::getProductABCClasses(){
	vector<double> thresholds;
	thresholds.push_back(OptimizationParameters::A_THRESHOLD_CLASS);
	thresholds.push_back(OptimizationParameters::B_THRESHOLD_CLASS); 
	
	ABCAnalysis abcAnalysis(orders,3, thresholds);
	abcAnalysis.execute();

	auto frequences = abcAnalysis.getProductFrequences();
	return abcAnalysis.getFrequenceClasses();
}

/**
 * 
 */
AbstractSolution * StorageILS::Execute(){

    this->numIterationsWithoutImprovement = 0;
	double bestGlobalSolutionValue; 
    AbstractSolution * initialSolution = CreateInitialSolution();
	StorageAllocationSolution * bestGlobalSolution = new StorageAllocationSolution( (StorageAllocationSolution *) initialSolution);
	StorageAllocationSolution * currentSolution = new StorageAllocationSolution(bestGlobalSolution); 
	bestGlobalSolutionValue = bestGlobalSolution->getSolutionValue(); 
	NeighborhoodStructure * perturbation = new StorageAllocationPertubation(&constraints); 
	int randomSeed= 1;
	auto allocations = ((StorageAllocationSolution *) initialSolution)->getProductAllocations(); 
	cout<<"Total penalty init : "<<currentSolution->getTotalPenalty()<<endl; 
	while(!StopCriteriaReached()){
 
		StorageAllocationSolution *bestLocalSearchSolution = new StorageAllocationSolution(*currentSolution);
		StorageAllocationSolution *originalSolution = new StorageAllocationSolution(*currentSolution);

		delete currentSolution;
		double bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue();
		StorageAllocationSolution *auxiliaryPointer = NULL; 
 
		//Perform a local search as a VNS
		for(unsigned int i=0;i< this->neighborhoodStructures.size();i++){

			currentSolution = new StorageAllocationSolution(*originalSolution);
			double currentSolutionValue = currentSolution->getSolutionValue();
			double newSolutionValue = 0;
		
			if(neighborhoodType[i] == "InsideShelfSwap"){	
				auxiliaryPointer = (StorageAllocationSolution *) SwapInsideShelfLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();	
			}else if(neighborhoodType[i] == "InsideBlockSwap"){	
				auxiliaryPointer = (StorageAllocationSolution *) SwapInsideBlockLocalSearch(currentSolution, this->neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();
			}else if(neighborhoodType[i] == "MostFrequentSwap"){
				std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				auxiliaryPointer = (StorageAllocationSolution *) SwapMostFrequentLocalSearch(currentSolution, neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();
				std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds_s]" << std::endl;
			}else{
			//	auxiliaryPointer = new StorageAllocationSolution(currentSolution);
				continue;
			}

			if((newSolutionValue-bestLocalSearchSolutionValue)*100.0/bestLocalSearchSolutionValue <= -0.1){
				delete bestLocalSearchSolution; 
				bestLocalSearchSolution = new StorageAllocationSolution(auxiliaryPointer);
				bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue(); 
			}
			delete auxiliaryPointer;

		}
		 
		this->numIterationsWithoutImprovement++;
		
		if((bestLocalSearchSolutionValue - bestGlobalSolutionValue)*100/bestGlobalSolutionValue <= -0.1){
			delete bestGlobalSolution;
			bestGlobalSolution = new StorageAllocationSolution(bestLocalSearchSolution);
			bestGlobalSolutionValue = bestLocalSearchSolution->getSolutionValue();
			this->numIterationsWithoutImprovement = 0; 
		}
	
		delete bestLocalSearchSolution; 
		delete originalSolution; 
		cout<<"Without improvement \t"<<this->numIterationsWithoutImprovement<<"\tValue:"<<bestGlobalSolution->getSolutionValue()<<endl;
		
		
	//	delete currentSolution;
		currentSolution = (StorageAllocationSolution *) RunPerturbation(bestGlobalSolution,perturbation);
		randomSeed++; 
	}
	
	cout<<"End function"<<endl;
	return bestGlobalSolution;
}
