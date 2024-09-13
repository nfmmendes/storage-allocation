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
using std::make_unique;
using std::min;
using std::make_shared;
using std::unique_ptr;


//////////////////////////////////////////////////////////////////////////////////////////
////                                 INSIDE SHELF SWAP
////
/////////////////////////////////////////////////////////////////////////////////////////

InsideShelfSwap::InsideShelfSwap(){
	startSolution = NULL; 
	numberOfNeighbors = 5;
	randomSeed = 1;
	
}

InsideShelfSwap::~InsideShelfSwap(){
	//delete startSolution;
}

bool InsideShelfSwap::isValidSwap(const Product &first, const Product &second, const MapAllocation &allocations){
	const auto& firstFamily = first.getFamily(); 
	const auto& secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	const auto firstAlocation { allocations.find(first) };
	const auto secondAllocation { allocations.find(second) };
	if(firstAlocation == allocations.end() || secondAllocation == allocations.end() )
		return false; 

	//Check the prohibitions
	const auto& prohibitedProducts = constraints->getProductsCodeWithProhibition(); 
	auto& firstProhibition = prohibitedProducts.find(first.getName());
	auto& secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = constraints->IsAllocationAllowed(first, secondAllocation->second);
		bool isSecondAllowed = constraints->IsAllocationAllowed(second, firstAlocation->second);

		if(! (isFirstAllowed && isSecondAllowed) )
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	auto stronglyIsolatedFamilies = constraints->getStronglyIsolatedFamilyCodes(); 
	if(stronglyIsolatedFamilies.find(firstFamily) == stronglyIsolatedFamilies.end() && 
	   stronglyIsolatedFamilies.find(secondFamily) == stronglyIsolatedFamilies.end())
			return true; 

	if(firstAlocation->second.first.getCode() == secondAllocation->second.first.getCode())
		return true; 
	
	return false;  
}

vector<AbstractSolution *> InsideShelfSwap::createNeighbors(){
	auto& allocations = ((StorageAllocationSolution *)startSolution)->getProductAllocations();
 
	std::vector<AbstractSolution *> solutions; 
	srand(randomSeed); 

	//It is not possible to do swaps 
	auto allocationsSize { shelfAllocations.size() };
	
	if(shelfAllocations.size() <=2)
		return solutions;
	
	set<pair<int,int> > swapsDone; 
	int first, second; 
	auto numIterations { min((size_t) numberOfNeighbors, (allocationsSize-1)*allocationsSize) };
	auto numTries { 0 }; 

	for(auto i=0; i< numIterations && numTries < 2*numIterations; i++, numTries++){
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		auto it = shelfAllocations.begin();
		advance(it,first); 
		const Product& firstProduct = it->second; 
		
		it = shelfAllocations.begin(); 
		advance(it,second); 
		const Product& secondProduct = it->second; 
		
		if(!isValidSwap(firstProduct, secondProduct, allocations)){
			i--;
			continue; 
		}

		auto newSolution = new StorageAllocationSolution((StorageAllocationSolution *)startSolution); 
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
	startSolution = NULL; 
	numberOfNeighbors = 5;
	randomSeed = 1;
}

InsideBlockSwap::~InsideBlockSwap(){
	//delete startSolution;
}

bool InsideBlockSwap::isValidSwap(const Product &first, const Product &second, MapAllocation &allocations){
	const auto& firstFamily { first.getFamily() }; 
	const auto& secondFamily { second.getFamily() }; 

	//if one of products are not allocated, the swap is not valid
	const auto firstAlocation { allocations.find(first) };
	const auto secondAllocation { allocations.find(second) };
	if(firstAlocation == allocations.end() || secondAllocation == allocations.end() )
		return false; 

	//Check the prohibitions
	const auto& firstPosition { allocations[first] };
	const auto& secondPosition { allocations[second] } ;
	const auto& prohibitedProducts { constraints->getProductsCodeWithProhibition() }; 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		auto isFirstAllowed = constraints->IsAllocationAllowed(first, secondAllocation->second);
		auto isSecondAllowed = constraints->IsAllocationAllowed(second, firstAlocation->second);

		if(! (isFirstAllowed && isSecondAllowed) )
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	auto stronglyIsolatedFamilies = constraints->getStronglyIsolatedFamilyCodes();
	auto endIterator = stronglyIsolatedFamilies.end();
	if(stronglyIsolatedFamilies.find(firstFamily) == endIterator && 
	   stronglyIsolatedFamilies.find(secondFamily) == endIterator)
			return true; 

	if(firstPosition.first.getCode() == secondPosition.first.getCode())
		return true; 
	
	return false;  
}

vector<AbstractSolution *> InsideBlockSwap::createNeighbors(){
	auto& allocations = ((StorageAllocationSolution *) startSolution)->getProductAllocations();
	blockAllocations.clear(); 
	
	const auto& shelves = block.getShelves();  
	set<long> shelfIds; 

	transform(begin(shelves), end(shelves), inserter(shelfIds, end(shelfIds)), 
			 [](auto &s){ return s.getId(); });
	
	for(auto &[product, position] : allocations){
		if(shelfIds.find(position.first.getIdShelf()) != shelfIds.end())
			blockAllocations[position] = product;
	}
	
	int allocationsSize = (int)blockAllocations.size();
	if(allocationsSize <=2)
		return {};
	
	std::set<pair<int,int> > swapsDone; 
	int first, second; 
	int numTries = 0; 

	int numIterations = min(numberOfNeighbors, (allocationsSize-1)*allocationsSize);
	std::vector<AbstractSolution *> solutions;
	for( int i=0; i< numIterations && numTries < 2*numIterations; i++, numTries++){
	
		if(!Util::ChooseTwoProductIndexes(first ,second,allocationsSize, swapsDone))
			break;

		auto it = blockAllocations.begin();
		advance(it,first); 
		const auto& firstProduct = it->second; 

		it = blockAllocations.begin(); 
		advance(it,second); 
		const auto& secondProduct = it->second; 

		bool isValid = isValidSwap(firstProduct, secondProduct, allocations); 
		if(!isValid){
			i--;
			continue; 
		}

		auto *newSolution = new StorageAllocationSolution((StorageAllocationSolution *)startSolution); 
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
	startSolution = NULL; 
	numberOfNeighbors = 5;
	randomSeed = 1;
}

MostFrequentSwap::~MostFrequentSwap(){ 
	// TODO: Solve it later
	//if(startSolution != nullptr)
	//	delete startSolution;
}

const AbstractSolution * MostFrequentSwap::getStartSolution() const{
	return startSolution; 
}

bool MostFrequentSwap::isValidSwap(const Product &first, const Product &second, MapAllocation &allocations){

	//if one of products is not allocated, the swap is not valid
	auto firstIt = allocations.find(first);
	auto secondIt = allocations.find(second);
	if(firstIt == allocations.end() || secondIt == allocations.end() )
		return false; 

	const auto& firstFamily = first.getFamily(); 
	const auto& secondFamily = second.getFamily(); 

	//Check the prohibitions
	const auto& firstPosition { firstIt->second };
	const auto& secondPosition { secondIt->second };
	const auto& prohibitedProducts { constraints->getProductsCodeWithProhibition() }; 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		auto isFirstAllowed = constraints->IsAllocationAllowed(first, secondPosition);
		auto isSecondAllowed = constraints->IsAllocationAllowed(second, firstPosition);

		if(!isFirstAllowed || !isSecondAllowed)
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	const auto& stronglyIsolatedFamilies { constraints->getStronglyIsolatedFamilyCodes() }; 
	if(stronglyIsolatedFamilies.find(firstFamily) == stronglyIsolatedFamilies.end() && 
	   stronglyIsolatedFamilies.find(secondFamily) == stronglyIsolatedFamilies.end())
			return true; 

	if(firstPosition.first.getCode() == secondPosition.first.getCode())
		return true; 
	
	return false;  
}


vector<AbstractSolution *> MostFrequentSwap::createNeighbors(){
	vector<AbstractSolution *> solutions;
	MapAllocation allocations = ((StorageAllocationSolution *) startSolution)->getProductAllocations();

	if(interchangeableProducts.size()<3)
		return solutions; 

	int numTries = 0; 
	int first; 
	int second; 
	set<pair<int,int> >swapsDone; 
	int numInterchangeableProducts = (int) interchangeableProducts.size(); 


	for(int i=0;i< numberOfNeighbors && numTries < 2*numberOfNeighbors;i++, numTries++){
		
		if(!Util::ChooseTwoProductIndexes(first ,second,numInterchangeableProducts, swapsDone))
			break;
 
		bool isValid = isValidSwap(interchangeableProducts[first], interchangeableProducts[second], allocations); 
		if(!isValid){
			i--;
			continue; 
		}
		
		StorageAllocationSolution * newSolution = new StorageAllocationSolution((StorageAllocationSolution *) startSolution);
		newSolution->proceedSwap(interchangeableProducts[first], interchangeableProducts[second],true);  
		solutions.push_back(newSolution);
	}

	return solutions; 
}

//////////////////////////////////////////////////////////////////////////////////////////
////                    Storage allocation pertubation region
/////////////////////////////////////////////////////////////////////////////////////////
const AbstractSolution * StorageAllocationPertubation::getStartSolution() const{
	return startSolution; 
} 

bool StorageAllocationPertubation::isValidSwap(const Product &first, const Product &second, MapAllocation &allocations){
	string firstFamily = first.getFamily(); 
	string secondFamily = second.getFamily(); 

	//if one of products are not allocated, the swap is not valid
	auto firstAllocation = allocations.find(first);
	auto secondAllocation = allocations.find(second);
	if(firstAllocation == allocations.end() || secondAllocation == allocations.end() )
		return false; 

	//Check the prohibitions
	const auto& firstPosition = firstAllocation->second;
	const auto& secondPosition = secondAllocation->second;
	const auto& prohibitedProducts = constraints->getProductsCodeWithProhibition(); 
	auto firstProhibition = prohibitedProducts.find(first.getName());
	auto secondProhibition = prohibitedProducts.find(second.getName());

	bool totallyFree =  (firstProhibition == prohibitedProducts.end() && secondProhibition == prohibitedProducts.end()); 

	if(!totallyFree){
		bool isFirstAllowed = constraints->IsAllocationAllowed(first, secondPosition);
		bool isSecondAllowed = constraints->IsAllocationAllowed(second, firstPosition);

		if(!isFirstAllowed || !isSecondAllowed)
			return false; 
	}

	if(firstFamily == secondFamily)
		return true; 
		
	auto stronglyIsolatedFamilies = constraints->getStronglyIsolatedFamilyCodes(); 
	if(stronglyIsolatedFamilies.find(firstFamily) == stronglyIsolatedFamilies.end() && 
	   stronglyIsolatedFamilies.find(secondFamily) == stronglyIsolatedFamilies.end())
			return true; 

	if(firstPosition.first.getCode() == secondPosition.first.getCode())
		return true; 

	return false;  
}

vector<AbstractSolution *> StorageAllocationPertubation::createNeighbors(){
	vector<AbstractSolution *> solutions;	
	int first, second;
	int numIterations = (int) interchangeableProducts.size()/20;  
	set<pair<int,int> > swapsDone;
	int numTries=0; 
 
 	auto *newSolution = new StorageAllocationSolution((StorageAllocationSolution *) startSolution); 
	auto allocations = newSolution->getProductAllocations(); 

	for( int i=0; i<  numIterations && numTries < 2*numIterations; i++, numTries++){
		if(!Util::ChooseTwoProductIndexes(first ,second,interchangeableProducts.size(), swapsDone) || ++numTries > 2*numIterations                                                                                                                                                        )
			break;

		const auto& firstProduct  = interchangeableProducts[first]; 
		const auto& secondProduct = interchangeableProducts[second];

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

const AbstractSolution * IsolatedFamilySwap::getStartSolution() const{
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
StorageILS::StorageILS(const vector<Product> & prods, Warehouse &wh,const DistanceMatrix<Vertex> *distMatrix,
					   map<pair<Cell, int>, Vertex>& vertexByCell, const vector<Order> &orders, const OptimizationConstraints &cons){
	distanceMatrix = distMatrix; 
	warehouse = &wh;
	this->orders= orders;
	this->vertexByCell = vertexByCell;
	constraints = cons;
	products = prods;
	InitializeNeighborhoods();

	productClasses = getProductABCClasses();
}


/**
 *	Create a initial product allocation based on the ABC class of each product and the distance 
 *  between each cell and the closest delivery point  
 */
StorageAllocationSolution * StorageILS::CreateInitialSolution(){
	
	StorageConstructiveHeuristic constr(products,*warehouse, distanceMatrix,vertexByCell, orders,constraints); 
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
	productClasses = getProductABCClasses();
	InitializeNeighborhoods();
}

bool StorageILS::StopCriteriaReached(){
    return  numIterationsWithoutImprovement >= OptimizationParameters::instance()->MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
}

void StorageILS::InitializeNeighborhoods(){
	neighborhoodStructures.push_back(make_shared<MostFrequentSwap>());
	neighborhoodStructures.push_back(make_shared<InsideShelfSwap>());
	neighborhoodStructures.push_back(make_shared<InsideBlockSwap>());
	neighborhoodStructures.push_back(make_shared<IsolatedFamilySwap>());

	neighborhoodStructures[0]->setOptimizationConstraints(&constraints);
	neighborhoodStructures[1]->setOptimizationConstraints(&constraints);
	neighborhoodStructures[2]->setOptimizationConstraints(&constraints);
	neighborhoodStructures[3]->setOptimizationConstraints(&constraints);
	
	neighborhoodType.push_back("MostFrequentSwap");
	neighborhoodType.push_back("InsideShelfSwap");
	neighborhoodType.push_back("InsideBlockSwap");
	neighborhoodType.push_back("IsolatedFamilySwap"); 
}

AbstractSolution * StorageILS::SwapMostFrequentLocalSearch(const AbstractSolution *currentSolution, shared_ptr<NeighborhoodStructure> neighborhoodStructure, int randomSeed){
	vector<Product> mostFrequentProducts;
	StorageAllocationSolution* bestSolution = new StorageAllocationSolution((const StorageAllocationSolution*)currentSolution);
	for(auto &[product, cl]: productClasses)
		if(cl == 'A')
			mostFrequentProducts.push_back(product);

	int maxNumberSwaps = (int) sqrt((int) mostFrequentProducts.size()); 
	for(int i=0; i <maxNumberSwaps; i++){
		auto localNeighborhoodStructurre = static_cast<MostFrequentSwap*>(neighborhoodStructure.get());
		
		if(localNeighborhoodStructurre == nullptr)
			return nullptr;
		localNeighborhoodStructurre->setRandomSeed(randomSeed*((int)products.size())+i);
		localNeighborhoodStructurre->setNumberOfNeighbors( (int) mostFrequentProducts.size()/4 );
		localNeighborhoodStructurre->setInterchangeableProducts( mostFrequentProducts);
		neighborhoodStructure->setStartSolution(bestSolution); 
		const auto neighbors = localNeighborhoodStructurre->createNeighbors(); 

		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();
		for(auto neighbor: neighbors){
			newSolutionValue = neighbor->getSolutionValue();

			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete bestSolution;
				bestSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbor);
				currentSolutionValue = currentSolution->getSolutionValue();
			}

			delete neighbor;
		}
	}

	return bestSolution; 
}

AbstractSolution * StorageILS::SwapInsideBlockLocalSearch(const AbstractSolution *currentSolution, shared_ptr<NeighborhoodStructure> neighborhoodStructure, int randomSeed){
	const auto& blocks { warehouse->getBlocks() }; 
	StorageAllocationSolution* bestSolution = new StorageAllocationSolution((const StorageAllocationSolution*)currentSolution);
	
	int randomMultiplier = 0;
	for(const auto& block : blocks){
		const auto& shelves = block.getShelves();

		auto insideBlockSwap = static_cast<InsideBlockSwap*>(neighborhoodStructure.get());
		assert(insideBlockSwap);

		insideBlockSwap->setBlock(block); 
		insideBlockSwap->setRandomSeed(randomSeed+(randomMultiplier*((int) shelves.size())));
		randomMultiplier++;

		insideBlockSwap->setNumberOfNeighbors((int)sqrt(block.getShelves().size()));
		neighborhoodStructure->setStartSolution(bestSolution); 
		const auto neighbors = insideBlockSwap->createNeighbors(); 

		double currentSolutionValue = currentSolution->getSolutionValue();
		double newSolutionValue = neighbors[0]->getSolutionValue();
		
		for(const auto* neighbor : neighbors){
			newSolutionValue = neighbor->getSolutionValue();

			//If the neighbor has a better value than the current solution value, so update the current solution
			//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
			//are not significantly better 
			//cout<<"Comparison : "<<newSolutionValue<<" | "<<currentSolutionValue<<endl;
			if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
				delete bestSolution;
				bestSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbor);
				currentSolutionValue = currentSolution->getSolutionValue();
			}

			delete neighbor;
		}
	}
 
	return bestSolution;
}

AbstractSolution * StorageILS::SwapInsideShelfLocalSearch(const AbstractSolution *currentSolution, shared_ptr<NeighborhoodStructure> neighborhoodStructure, int randomSeed){
	const auto& blocks = warehouse->getBlocks(); 
	auto& allocations = ((StorageAllocationSolution *) currentSolution)->getProductAllocations();
	StorageAllocationSolution* bestSolution = new StorageAllocationSolution((const StorageAllocationSolution*)currentSolution);
	map<long, map<Position, Product> > shelfAllocations; 
	
	for(auto &[product, position] : allocations)
		shelfAllocations[position.first.getIdShelf()][position] = product;

	auto insideShelfSwap = static_cast<InsideShelfSwap *>(neighborhoodStructure.get());
	assert(insideShelfSwap != nullptr);


	int j { 0 };
	for(const auto& block : blocks){
		const auto& shelves { block.getShelves() };
		vector<AbstractSolution *> neighbors;
	
		int k { 0 };
		for(const auto& shelf : shelves){
			int indexShelf = rand()%shelves.size();
			insideShelfSwap->setShelf(shelves[indexShelf]);
			insideShelfSwap->setShelfAllocations(shelfAllocations[shelves[indexShelf].getId()]); 
			insideShelfSwap->setRandomSeed(randomSeed+j*((int)shelves.size())+k);
			insideShelfSwap->setNumberOfNeighbors((int)sqrt(shelves[k].getCells().size()));

			neighborhoodStructure->setStartSolution(bestSolution); 
			neighbors = insideShelfSwap->createNeighbors(); 
			double currentSolutionValue = currentSolution->getSolutionValue();
			double newSolutionValue = neighbors[0]->getSolutionValue();
			for(const auto neighbor : neighbors){
				newSolutionValue = neighbor->getSolutionValue(); 
				//If the neighbor has a better value than the current solution value, so update the current solution
				//A margin of 0.1% is used to avoid to update constantly the current solution with solutions that 
				//are not significantly better 
				if((newSolutionValue - currentSolutionValue)*100.0/newSolutionValue <= -0.1){
					delete bestSolution;
					bestSolution = new StorageAllocationSolution((StorageAllocationSolution *) neighbor);	
					currentSolutionValue = currentSolution->getSolutionValue();
				}

				delete neighbor;
			}
			k++; 
		}
		j++;
	}

	return bestSolution;
}

AbstractSolution * StorageILS::RunPerturbation(AbstractSolution *currentSolution, shared_ptr<NeighborhoodStructure> neighborhoodStructure){

	auto perturbationNeighborhood = static_cast<StorageAllocationPertubation *>(neighborhoodStructure.get());
	assert(perturbationNeighborhood != nullptr);

	perturbationNeighborhood->setInterchangeableProducts(products); 
	perturbationNeighborhood->setNumberOfNeighbors(1);
	neighborhoodStructure->setStartSolution(currentSolution); 
	auto neighbors = perturbationNeighborhood->createNeighbors(); 


	return neighbors[0]; 
}

const map<Product, char> StorageILS::getProductABCClasses(){
	vector<double> thresholds;
	thresholds.push_back(OptimizationParameters::instance()->A_THRESHOLD_CLASS);
	thresholds.push_back(OptimizationParameters::instance()->B_THRESHOLD_CLASS); 
	ABCAnalysis abcAnalysis(orders,3, thresholds);
	abcAnalysis.execute();

	return abcAnalysis.getFrequenceClasses();
}

AbstractSolution * StorageILS::Execute(){

    numIterationsWithoutImprovement = 0;
	double bestGlobalSolutionValue; 
	
    auto* initialSolution = CreateInitialSolution();
	auto bestGlobalSolution = unique_ptr<StorageAllocationSolution>(new StorageAllocationSolution(initialSolution));
	auto currentSolution = unique_ptr<StorageAllocationSolution>(new StorageAllocationSolution(initialSolution)); 

	bestGlobalSolutionValue = bestGlobalSolution->getSolutionValue(); 

	cout<<"Greed value : "<<bestGlobalSolutionValue<< " penalty: "<< ((StorageAllocationSolution*)initialSolution)->getTotalPenalty()<<endl;
	auto perturbation = make_shared<StorageAllocationPertubation>(&constraints); 

	int randomSeed= 1;
	auto allocations = initialSolution->getProductAllocations(); 
	//cout<<"Total penalty init : "<<currentSolution->getTotalPenalty()<<endl; 
	while(!StopCriteriaReached()){
		
		auto bestLocalSearchSolution { make_unique<StorageAllocationSolution>(new StorageAllocationSolution(*currentSolution)) };
		auto originalSolution { make_unique<StorageAllocationSolution>(new StorageAllocationSolution(*currentSolution)) };

		double bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue();
		unique_ptr<StorageAllocationSolution> auxiliaryPointer; 
		
		//Perform a local search as a VNS
		for(unsigned int i=0;i< neighborhoodStructures.size();i++){
			double newSolutionValue = 0;
		
			if(neighborhoodType[i] == "InsideShelfSwap"){	
				cout<<"Inside Shelf Swap"<<endl;
				auxiliaryPointer.reset((StorageAllocationSolution *) SwapInsideShelfLocalSearch(currentSolution.get(), neighborhoodStructures[i], randomSeed));
				newSolutionValue = auxiliaryPointer->getSolutionValue();	
			}else if(neighborhoodType[i] == "InsideBlockSwap"){	 
				cout<<"Inside Block Swap"<<endl;
				auxiliaryPointer.reset((StorageAllocationSolution *) SwapInsideBlockLocalSearch(currentSolution.get(), neighborhoodStructures[i], randomSeed));
				newSolutionValue = auxiliaryPointer->getSolutionValue();
			}else if(neighborhoodType[i] == "MostFrequentSwap"){
				cout<<"Most frequent Swap"<<endl;
				auxiliaryPointer.reset((StorageAllocationSolution *) SwapMostFrequentLocalSearch(currentSolution.get(), neighborhoodStructures[i], randomSeed));
				newSolutionValue = auxiliaryPointer->getSolutionValue();
			}else{
				continue;
			}
			
			cout<<"Best local search solution: "<<bestGlobalSolutionValue<<endl;
			if((newSolutionValue-bestLocalSearchSolutionValue)*100.0/bestLocalSearchSolutionValue <= -0.1){
				bestLocalSearchSolution.reset(new StorageAllocationSolution(auxiliaryPointer.get()));
				bestLocalSearchSolutionValue = bestLocalSearchSolution->getSolutionValue(); 
			}
			
			auto test = new StorageAllocationSolution(originalSolution.get());
 			currentSolution.reset(new StorageAllocationSolution(originalSolution.get()));
		}
		
		numIterationsWithoutImprovement++;
		
		if((bestLocalSearchSolutionValue - bestGlobalSolutionValue)*100/bestGlobalSolutionValue <= -0.1){
			bestGlobalSolution.reset(new StorageAllocationSolution(bestLocalSearchSolution.get()));
			bestGlobalSolutionValue = bestLocalSearchSolution->getSolutionValue();
			numIterationsWithoutImprovement = 0; 
		}
		
		cout<<"Iterations without improvement: " << numIterationsWithoutImprovement<<" Best global solution: "<<bestGlobalSolution->getSolutionValue()<<endl;  
		
		currentSolution.reset((StorageAllocationSolution*) RunPerturbation(bestGlobalSolution.get(),perturbation));
		randomSeed++; 
	}
	
	auto returnPointer = bestGlobalSolution.release();
	return returnPointer;
}
