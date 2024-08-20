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
#include <cassert>


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
 * Function to control if a 
 * */
bool InsideShelfSwap::isValidSwap(Product &first, Product &second, MapAllocation &allocations){
	std::string firstFamily = first.getFamily(); 
	std::string secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	if(allocations.find(first) == allocations.end() || allocations.find(second) == allocations.end() )
		return false; 

	//Check the prohibitions
	Position firstPosition =  allocations[first];
	Position secondPosition = allocations[second];
	set<std::string> prohibitedProducts = this->constraints->getProductsCodeWithProhibition(); 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = this->constraints->IsAllocationAllowed(first, secondPosition);
		bool isSecondAllowed = this->constraints->IsAllocationAllowed(second, firstPosition);

		if(! (isFirstAllowed && isSecondAllowed) )
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
 */
vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	std::map<Product , pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
 
	std::vector<AbstractSolution *> solutions; 
	srand(this->randomSeed); 

	//It is not possible to do swaps 
	int allocationsSize = (int) shelfAllocations.size();
	
	if(shelfAllocations.size() <=2)
		return solutions;
	
	set<pair<int,int> > swapsDone; 
	int first, second; 
	unsigned int numIterations = min(numberOfNeighbors, ((unsigned int) (allocationsSize-1)*allocationsSize) );
	unsigned int numTries = 0; 

	for(unsigned int i=0; i< numIterations && numTries < 2*numIterations; i++, numTries++){
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		std::map< Position , Product>::iterator it = shelfAllocations.begin();
		advance(it,first); 
		Product firstProduct = it->second; 
		
		it = shelfAllocations.begin(); 
		advance(it,second); 
		Product secondProduct = it->second; 
		
		bool isValid = isValidSwap(firstProduct, secondProduct, allocations); 
		if(!isValid){
			i--;
			continue; 
		}

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
 * Function to control if a 
 * */
bool InsideBlockSwap::isValidSwap(Product &first, Product &second, MapAllocation &allocations){
	string firstFamily = first.getFamily(); 
	string secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	if(allocations.find(first) == allocations.end() || allocations.find(second) == allocations.end() )
		return false; 

	//Check the prohibitions
	Position firstPosition =  allocations[first];
	Position secondPosition = allocations[second];
	std::set<std::string> prohibitedProducts = this->constraints->getProductsCodeWithProhibition(); 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = this->constraints->IsAllocationAllowed(first, secondPosition);
		bool isSecondAllowed = this->constraints->IsAllocationAllowed(second, firstPosition);

		if(! (isFirstAllowed && isSecondAllowed) )
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
 */
vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	std::map<Product, pair<Cell,int> > allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	blockAllocations.clear(); 
	
	std::vector<Shelf> shelves = this->block.getShelves(); 
	std::vector<AbstractSolution *> solutions; 
	set<long> shelfIds; 

	for(unsigned int i=0; i < shelves.size(); i++)
		shelfIds.insert(shelves[i].getId()); 
	
	for(auto &[product, position] : allocations){
		if(shelfIds.find(position.first.getIdShelf()) != shelfIds.end())
			blockAllocations[position] = product;
	}
	
	int allocationsSize = (int)blockAllocations.size();
	if(allocationsSize <=2)
		return solutions;
	
	std::set<pair<int,int> > swapsDone; 
	int first, second; 
	int numTries = 0; 

	int numIterations = min(numberOfNeighbors, (allocationsSize-1)*allocationsSize);
	for( int i=0; i< numIterations && numTries < 2*numIterations; i++, numTries++){
	
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		std::map< pair<Cell, int> , Product>::iterator it = blockAllocations.begin();
		advance(it,first); 
		Product firstProduct = it->second; 

		it = blockAllocations.begin(); 
		advance(it,second); 
		Product secondProduct = it->second; 

		bool isValid = isValidSwap(firstProduct, secondProduct, allocations); 
		if(!isValid){
			i--;
			continue; 
		}

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
 * Function to control if a 
 * */
bool MostFrequentSwap::isValidSwap(Product &first, Product &second, MapAllocation &allocations){
	std::string firstFamily = first.getFamily(); 
	std::string secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	if(allocations.find(first) == allocations.end() || allocations.find(second) == allocations.end() )
		return false; 

	//Check the prohibitions
	Position firstPosition =  allocations[first];
	Position secondPosition = allocations[second];
	set<std::string> prohibitedProducts = this->constraints->getProductsCodeWithProhibition(); 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = this->constraints->IsAllocationAllowed(first, secondPosition);
		bool isSecondAllowed = this->constraints->IsAllocationAllowed(second, firstPosition);

		if(! (isFirstAllowed && isSecondAllowed) )
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	auto stronglyIsolatedFamilies = this->constraints->getStronglyIsolatedFamilyCodes(); 
	if(stronglyIsolatedFamilies.find(firstFamily) == stronglyIsolatedFamilies.end() && 
	   stronglyIsolatedFamilies.find(secondFamily) == stronglyIsolatedFamilies.end())
			return true; 

	if(firstPosition.first.getCode() == secondPosition.first.getCode())
		return true; 
	
	return false;  
}


/**
 *
 **/
vector<AbstractSolution *> MostFrequentSwap::createNeighbors(){
	//cout<<"A"<<endl;
	vector<AbstractSolution *> solutions;
	MapAllocation allocations = ((StorageAllocationSolution *)this->startSolution)->getProductAllocations();
	//cout<<"B"<<endl;
	if(this->interchangeableProducts.size()<3)
		return solutions; 

	int numTries = 0; 
	int first; 
	int second; 
	set<pair<int,int> >swapsDone; 
	int numInterchangeableProducts = (int)this->interchangeableProducts.size(); 
	//cout<<"C"<<endl;

	for(int i=0;i<this->numberOfNeighbors && numTries < 2*numberOfNeighbors;i++, numTries++){
		
		if(!Util::ChooseTwoProductIndexes(first ,second,numInterchangeableProducts, swapsDone))
			break;
		//cout<<first<<" "<<second<<" "<<interchangeableProducts.size()<<endl; 
		bool isValid = isValidSwap(this->interchangeableProducts[first], this->interchangeableProducts[second], allocations); 
		if(!isValid){
			i--;
			continue; 
		}
		
		StorageAllocationSolution * newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution);
		newSolution->proceedSwap(this->interchangeableProducts[first], this->interchangeableProducts[second],true);  
		solutions.push_back(newSolution);
	}
	//cout<<"D"<<endl;
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
	if(allocations.find(first) == allocations.end() || allocations.find(second) == allocations.end() )
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
	int numIterations = (int) interchangeableProducts.size()/20;  
	set<pair<int,int> > swapsDone;
	int numTries=0; 
 
	StorageAllocationSolution *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)this->startSolution); 
	auto allocations = newSolution->getProductAllocations(); 

	for( int i=0; i<  numIterations && numTries < 2*numIterations; i++, numTries++){
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
IsolatedFamilySwap::IsolatedFamilySwap(){}

IsolatedFamilySwap::~IsolatedFamilySwap(){}

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
StorageILS::StorageILS(vector<Product> & prods, Warehouse &wh,const DistanceMatrix<Vertex> *distMatrix,
					   map<pair<Cell, int>, Vertex> vertexByCell, vector<Order> &orders, OptimizationConstraints &cons){
	this->distanceMatrix = distMatrix; 
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
	
	StorageConstructiveHeuristic constr(this->products,*warehouse, distanceMatrix,vertexByCell, orders,constraints); 
	return  constr.Execute(); 
}

void StorageILS::EvaluateSolution(AbstractSolution * solution){
	((StorageAllocationSolution *)solution)->Evaluate(true);
}

StorageILS::StorageILS(){}

StorageILS::StorageILS(StorageILS &other){
	this->distanceMatrix = other.distanceMatrix;
	this->warehouse = other.warehouse;
	this->orders = other.orders; 
	this->productClasses = getProductABCClasses();
	InitializeNeighborhoods();
}

bool StorageILS::StopCriteriaReached(){
    return  this->numIterationsWithoutImprovement >= OptimizationParameters::instance()->MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}

void StorageILS::InitializeNeighborhoods(){
	this->neighborhoodStructures.push_back(new MostFrequentSwap());
	this->neighborhoodStructures.push_back(new InsideShelfSwap());
	this->neighborhoodStructures.push_back(new InsideBlockSwap());
	this->neighborhoodStructures.push_back(new IsolatedFamilySwap());

	this->neighborhoodStructures[0]->setOptimizationConstraints(&constraints);
	this->neighborhoodStructures[1]->setOptimizationConstraints(&constraints);
	this->neighborhoodStructures[2]->setOptimizationConstraints(&constraints);
	this->neighborhoodStructures[3]->setOptimizationConstraints(&constraints);
	
	neighborhoodType.push_back("MostFrequentSwap");
	neighborhoodType.push_back("InsideShelfSwap");
	neighborhoodType.push_back("InsideBlockSwap");
	neighborhoodType.push_back("IsolatedFamilySwap"); 
}

AbstractSolution * StorageILS::SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	
	vector<Product> mostFrequentProducts;
	for(auto &[product, cl]: productClasses)
		if(cl == 'A')
			mostFrequentProducts.push_back(product);

	int maxNumberSwaps = (int) sqrt((int) mostFrequentProducts.size()); 
	for(int i=0; i <maxNumberSwaps; i++){
		vector<AbstractSolution *> neighbors;
		((MostFrequentSwap *) neighborhoodStructure)->setRandomSeed(randomSeed*((int)products.size())+i);
		((MostFrequentSwap *) neighborhoodStructure)->setNumberOfNeighbors( (int) mostFrequentProducts.size()/4 );
		((MostFrequentSwap *) neighborhoodStructure)->setInterchangeableProducts( mostFrequentProducts);
		neighborhoodStructure->setStartSolution(currentSolution); 
		neighbors = ((MostFrequentSwap *) neighborhoodStructure)->createNeighbors(); 

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

			delete neighbors[k];
		}
		
	}

	return currentSolution; 
}

AbstractSolution * StorageILS::SwapInsideBlockLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	vector<Block> blocks = this->warehouse->getBlocks(); 
				
	for(unsigned int j=0;j<blocks.size();j++){

		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;

		((InsideBlockSwap *) neighborhoodStructure)->setBlock(blocks[j]); 
		((InsideBlockSwap *) neighborhoodStructure)->setRandomSeed(randomSeed+j*((int) shelves.size()));
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

AbstractSolution * StorageILS::SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed){
	
	vector<Block> blocks = this->warehouse->getBlocks(); 
	map<Product, Position > allocations = ((StorageAllocationSolution *) currentSolution)->getProductAllocations();
	map<long, map<Position,Product> > shelfAllocations; 
	
	for(auto &[product, position] : allocations)
		shelfAllocations[position.first.getIdShelf()][position] = product;

	auto insideShelfSwap = static_cast<InsideShelfSwap *>(neighborhoodStructure);
	assert(insideShelfSwap != nullptr);
	
	for(unsigned int j=0;j<blocks.size();j++){
		vector<Shelf> shelves = blocks[j].getShelves();
		vector<AbstractSolution *> neighbors;
	
		for(unsigned int k=0;k<shelves.size();k++){
			int indexShelf = rand()%shelves.size();
			insideShelfSwap->setShelf(shelves[indexShelf]);
			insideShelfSwap->setShelfAllocations(shelfAllocations[shelves[indexShelf].getId()]); 
			insideShelfSwap->setRandomSeed(randomSeed+j*((int)shelves.size())+k);
			insideShelfSwap->setNumberOfNeighbors((int)sqrt(shelves[k].getCells().size()));

			neighborhoodStructure->setStartSolution(currentSolution); 
			neighbors = insideShelfSwap->createNeighbors(); 
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

	return currentSolution;
}

AbstractSolution * StorageILS::RunPerturbation(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure){

	((StorageAllocationPertubation *) neighborhoodStructure)->setInterchangeableProducts(products); 
	((StorageAllocationPertubation *) neighborhoodStructure)->setNumberOfNeighbors(1);
	neighborhoodStructure->setStartSolution(currentSolution); 
	vector<AbstractSolution *> neighbors = ((StorageAllocationPertubation *) neighborhoodStructure)->createNeighbors(); 

	return neighbors[0]; 
}

map<Product, char> StorageILS::getProductABCClasses(){
	vector<double> thresholds;
	thresholds.push_back(OptimizationParameters::instance()->A_THRESHOLD_CLASS);
	thresholds.push_back(OptimizationParameters::instance()->B_THRESHOLD_CLASS); 
	ABCAnalysis abcAnalysis(orders,3, thresholds);
	abcAnalysis.execute();

	auto frequences = abcAnalysis.getProductFrequences();
	return abcAnalysis.getFrequenceClasses();
}

AbstractSolution * StorageILS::Execute(){

    this->numIterationsWithoutImprovement = 0;
	double bestGlobalSolutionValue; 
	
    auto* initialSolution = CreateInitialSolution();
	auto* bestGlobalSolution = new StorageAllocationSolution( (StorageAllocationSolution *) initialSolution);
	auto* currentSolution = new StorageAllocationSolution(bestGlobalSolution); 

	bestGlobalSolutionValue = bestGlobalSolution->getSolutionValue(); 
	cout<<"Greed value : "<<bestGlobalSolutionValue<< " penalty: "<< initialSolution->getTotalPenalty()<<endl;
	auto * perturbation = new StorageAllocationPertubation(&constraints); 

	int randomSeed= 1;
	auto allocations = initialSolution->getProductAllocations(); 
	//cout<<"Total penalty init : "<<currentSolution->getTotalPenalty()<<endl; 
	while(!StopCriteriaReached()){
		
		auto bestLocalSearchSolution { make_unique<StorageAllocationSolution>(new StorageAllocationSolution(*currentSolution)) };
		auto originalSolution { make_unique<StorageAllocationSolution>(new StorageAllocationSolution(*currentSolution)) };

		delete currentSolution;
		double bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue();
		StorageAllocationSolution *auxiliaryPointer = NULL; 
		
		//Perform a local search as a VNS
		for(unsigned int i=0;i< this->neighborhoodStructures.size();i++){

			currentSolution = new StorageAllocationSolution(*originalSolution);

			double newSolutionValue = 0;
		
			if(neighborhoodType[i] == "InsideShelfSwap"){	
				cout<<"Inside Shelf Swap"<<endl;
				auxiliaryPointer = (StorageAllocationSolution *) SwapInsideShelfLocalSearch(currentSolution, neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();	
			}else if(neighborhoodType[i] == "InsideBlockSwap"){	 
				cout<<"Inside Block Swap"<<endl;
				auxiliaryPointer = (StorageAllocationSolution *) SwapInsideBlockLocalSearch(currentSolution, neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();
			}else if(neighborhoodType[i] == "MostFrequentSwap"){
				cout<<"Most frequent Swap"<<endl;
				//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
				auxiliaryPointer = (StorageAllocationSolution *) SwapMostFrequentLocalSearch(currentSolution, neighborhoodStructures[i], randomSeed);
				newSolutionValue = auxiliaryPointer->getSolutionValue();
				//std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
				//std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milliseconds_s]" << std::endl;
			}else{
			//	auxiliaryPointer = new StorageAllocationSolution(currentSolution); 
				continue;
			}
			
			cout<<"Best local search solution: "<<bestGlobalSolutionValue<<endl;
			if((newSolutionValue-bestLocalSearchSolutionValue)*100.0/bestLocalSearchSolutionValue <= -0.1){ 
				bestLocalSearchSolution.reset(new StorageAllocationSolution(auxiliaryPointer));
				bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue(); 
			}
			delete auxiliaryPointer;
		}
		
		this->numIterationsWithoutImprovement++;
		
		if((bestLocalSearchSolutionValue - bestGlobalSolutionValue)*100/bestGlobalSolutionValue <= -0.1){
			delete bestGlobalSolution;
			bestGlobalSolution = new StorageAllocationSolution(*bestLocalSearchSolution);
			bestGlobalSolutionValue = bestLocalSearchSolution->getSolutionValue();
			this->numIterationsWithoutImprovement = 0; 
		}
		
		cout<<"Iterations without improvement: " << numIterationsWithoutImprovement<<" Best global solution: "<<bestGlobalSolution->getSolutionValue()<<endl;  
		
		currentSolution = (StorageAllocationSolution *) RunPerturbation(bestGlobalSolution,perturbation);
		randomSeed++; 
	}
	
	//	cout<<"End function"<<endl;
	return bestGlobalSolution;
}
