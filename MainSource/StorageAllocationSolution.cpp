#include "StorageAllocationSolution.h"
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
#include <chrono>
#include <memory>
#include "OptimizationConstraints.h"
#include "OptimizationParameters.h"
#include "Vertex.h"
#include "Arc.h"
#include "Cell.h"
#include "StorageSolutionEvaluator.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
using namespace QuickTSP; 
using std::ofstream;
using std::shared_ptr;
using std::to_string;
using std::cout;
using std::flush;
using std::make_pair;
using std::map;
using std::vector;
using std::pair;


StorageSolutionEvaluator * StorageAllocationSolution::Evaluator = NULL;
int StorageAllocationSolution::countSolutions = 0;

StorageAllocationSolution::StorageAllocationSolution(){
	StorageAllocationSolution::countSolutions++;
}

StorageAllocationSolution::StorageAllocationSolution(const StorageAllocationSolution *other){
	StorageAllocationSolution::countSolutions++;
	this->solutionValue = other->solutionValue;
	this->runtime = other->runtime;
	this->minDelta = other->minDelta;
	isMaximization = other->isMaximization; 
	this->totalPenalty = other->totalPenalty; 

	copy(begin(other->notAllocatedProducts), end(other->notAllocatedProducts), 
		inserter(notAllocatedProducts, end(notAllocatedProducts)));
	
	copy(begin(other->productsAllocation), end(other->productsAllocation), 
		inserter(productsAllocation, end(productsAllocation)));

	for(const auto&product : other->routesByProduct){
		this->routesByProduct[product.first].resize(product.second.size());
		
		for(unsigned int i =0;i<product.second.size(); i++){
			//cout<<product.first.getName()<<" "<<i<<" "<<product.second.size()<<" " <<endl;
			this->routesByProduct[product.first][i] = new PickingRoute();
			this->routesByProduct[product.first][i]->first = product.second[i]->first; 
			this->routesByProduct[product.first][i]->second = product.second[i]->second; 
		}
	}
}

StorageAllocationSolution::StorageAllocationSolution(const StorageAllocationSolution &other):AbstractSolution(other){
	
	StorageAllocationSolution::countSolutions++;
	this->solutionValue = other.solutionValue;
	this->runtime = other.runtime;
	this->minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	this->totalPenalty = other.totalPenalty; 
	
	copy(begin(other.notAllocatedProducts), end(other.notAllocatedProducts), 
		inserter(notAllocatedProducts, end(notAllocatedProducts)));
	
	copy(begin(other.productsAllocation), end(other.productsAllocation), 
		inserter(productsAllocation, end(productsAllocation)));

	for(const auto& product : other.routesByProduct){
		this->routesByProduct[product.first].resize(product.second.size());

		for(unsigned int i =0;i< product.second.size(); i++){
			this->routesByProduct[product.first][i] = new PickingRoute();
			this->routesByProduct[product.first][i]->first = product.second[i]->first; 
			this->routesByProduct[product.first][i]->second = product.second[i]->second; 
		}
	}
	
}

StorageAllocationSolution::StorageAllocationSolution(double value, double time, double minDelta,bool maximization){
	StorageAllocationSolution::countSolutions++;
	this->solutionValue = value;
	this->runtime = time;
	this->minDelta = minDelta;
	isMaximization = maximization; 
	this->notAllocatedProducts.clear(); 
	this->productsAllocation.clear();
}


void StorageAllocationSolution::setEvaluator(const DistanceMatrix<Vertex> *distanceMatrix, map<Position , shared_ptr<Vertex> > &vertexByPosition,
											const vector<Block> &blocks, OptimizationConstraints &constraints){
	if(Evaluator != NULL)
		delete Evaluator;
	Evaluator = new StorageSolutionEvaluator(distanceMatrix,vertexByPosition, blocks, constraints);
}

StorageAllocationSolution::~StorageAllocationSolution(){
	StorageAllocationSolution::countSolutions--;
	 
	this->notAllocatedProducts.clear();
	this->productsAllocation.clear(); 
	for(map<Product, vector<PickingRoute *> >::iterator it = this->routesByProduct.begin(); it != this->routesByProduct.end();it++ ){
		for(unsigned int i=0;i< it->second.size(); i++){ 
			it->second[i]->first.clear(); 
			delete it->second[i]; 
		}
		it->second.clear();
	}
	this->routesByProduct.clear();
}

void StorageAllocationSolution::setMinDelta(double minDelta){
    this->minDelta = minDelta;
}

void StorageAllocationSolution::setRuntime(double time){
    this->runtime = time;
}

void StorageAllocationSolution::setSolutionValue(double value){
    this->solutionValue = value; 
}

void StorageAllocationSolution::setRoutesByProduct(map<Product, vector<PickingRoute * > > &other){

	for(map<Product, vector<PickingRoute *> >::iterator it = this->routesByProduct.begin(); it != this->routesByProduct.end(); it++ ){
		for(unsigned int i=0;i<it->second.size(); i++){			
			it->second[i]->first.clear();
			delete it->second[i];
		}
		it->second.clear(); 
	}

	for(map<Product,vector<PickingRoute*> >::iterator it = other.begin(); it!= other.end(); it++){
		this->routesByProduct[it->first].resize(it->second.size());
		for(unsigned int i =0;i<it->second.size(); i++){
			this->routesByProduct[it->first][i] = new PickingRoute();
			this->routesByProduct[it->first][i]->first = it->second[i]->first; 
			this->routesByProduct[it->first][i]->second = it->second[i]->second; 
		}
	}
}

void StorageAllocationSolution::printSolution() const{

    auto end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

	ofstream file("results/solutions_"+to_string(end_time) + ".txt");
	printToFile(file); 
	ofstream fileToInterface("results/solutions.txt");
	printToFile(fileToInterface); 
}

void StorageAllocationSolution::Evaluate(bool evaluateWithTSP){
	set<PickingRoute *> routes; 
	double distance = 0.0; 
	
	for(auto [key, routeList] : routesByProduct)
		for(unsigned int i=0; i<routeList.size(); i++)
			routes.insert(routeList[i]); 
	if(evaluateWithTSP){
		for(auto route : routes){
			route->second =  StorageAllocationSolution::Evaluator->DoRouteEvaluation(route->first);
			distance += route->second; 
		}
	}else{
		for(auto route : routes){
			route->second =  StorageAllocationSolution::Evaluator->DoRouteEstimation(route->first);
			distance += route->second; 
		}
	}
	
}

void StorageAllocationSolution::printToFile(ofstream & out) const{
	out<<productsAllocation.size()<<endl;
	
	for(auto & [product, position] : productsAllocation)
		out<<product.getName()<<" "<<position.first.getCode()<<" "<<position.second<<endl;
	cout<<flush;
	out.close(); 
}

map<Product, pair<Cell,int> > & StorageAllocationSolution::getProductAllocations(){
	return this->productsAllocation;
}

double StorageAllocationSolution::getTotalPenalty(){
	return this->totalPenalty;
}

set<Product> & StorageAllocationSolution::getNonAllocatedProducts(){
	return this->notAllocatedProducts; 
}

void StorageAllocationSolution::setAllocation(const Cell &cell, int level, const Product &product){
	this->productsAllocation[product] =  make_pair(cell,level); 
}

void StorageAllocationSolution::removeAllocation(const Product &product){	
	this->productsAllocation.erase(product);	
} 

void StorageAllocationSolution::setTotalPenalty(const double value){ 
	this->totalPenalty = value; 
} 
 
void StorageAllocationSolution::proceedSwap(const Product &firstProduct, const Product &secondProduct, bool useTSPEvaluator){
		
	pair<Cell,int> first = productsAllocation[firstProduct];
	pair<Cell,int> second	= productsAllocation[secondProduct];
	auto firstVertex = Evaluator->getVertex(first);
	auto secondVertex = Evaluator->getVertex(second);
	double delta = 0.0; 

	double penaltyDelta = StorageAllocationSolution::Evaluator->evaluatePenaltyDelta(getProductAllocations(), firstProduct, secondProduct);
	totalPenalty  += penaltyDelta; 
	
	productsAllocation[firstProduct] = second; 
	productsAllocation[secondProduct] = first;
	
	vector<PickingRoute *> firstRoutes = routesByProduct[firstProduct];
	vector<PickingRoute *> secondRoutes = routesByProduct[secondProduct];
	
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for(unsigned int i=0; i<firstRoutes.size(); i++)
		delta += getVariationAndUpdateAfterSwap(firstRoutes[i], *firstVertex, *secondVertex, useTSPEvaluator);

	for(unsigned int i=0; i<secondRoutes.size(); i++)
		delta += getVariationAndUpdateAfterSwap(secondRoutes[i], *secondVertex, *firstVertex, useTSPEvaluator);

	this->solutionValue += delta + penaltyDelta; 
}

double StorageAllocationSolution::getVariationAndUpdateAfterSwap(PickingRoute *original,const Vertex &oldVertex, const Vertex &newVertex, bool useTSPEvaluator){

	//if a same route has both products in the swap the evaluation don't need to be done
	if(find_if(original->first.begin(),original->first.end(), [newVertex](auto v){ return *v == newVertex; }) != original->first.end())
		return 0;

	std::replace_if(original->first.begin(),original->first.end(), [oldVertex](shared_ptr<Vertex> v){
		return *(v.get()) == oldVertex;
	}, shared_ptr<Vertex>(new Vertex(newVertex)));

	double oldValue = original->second; 

	original->second = useTSPEvaluator ? Evaluator->DoRouteEvaluation(original->first) : Evaluator->DoRouteEstimation(original->first);
	
	if(original->first.size() <= 4){
	
	}

	return original->second - oldValue; 
}

void StorageAllocationSolution::setAllocation(MapAllocation &allocations, const vector<Order> &orders){
	
	for(auto &[product,allocation] : allocations)
		this->productsAllocation[product] = allocation; 

	for(const Order & order : orders){
		vector<pair<Product,double> > items = order.getOrderItems();
		vector<pair<Cell,int> > positions; 

		for(unsigned int i=0; i< items.size(); i++ ){
			if(allocations.find(items[i].first) != allocations.end() )
				positions.push_back(allocations[items[i].first]); 
		}

		PickingRoute vertexes = StorageAllocationSolution::Evaluator->getVertexes(positions); 
		for(auto &[product, quantity] : items ){
			this->routesByProduct[product].push_back(new PickingRoute());
			PickingRoute *inserted = this->routesByProduct[product][this->routesByProduct[product].size()-1];
			for(unsigned int i=0;i<vertexes.first.size();i++)
				inserted->first.push_back(vertexes.first[i]);
		}
	}
}

void StorageAllocationSolution::updateSolutionValue(vector<PickingRoute> &oldRoutes, const vector<PickingRoute> &newRoutes, bool useTSP){
	double oldSum =0;
	double newSum = 0;
	
	for(unsigned int i=0;i<oldRoutes.size(); i++)
		oldSum += oldRoutes[i].second; 
	
	for(unsigned int i=0;i<newRoutes.size();i++)
		if(useTSP)
			newSum += StorageAllocationSolution::Evaluator->DoRouteEvaluation(newRoutes[i].first);
		else
			newSum += StorageAllocationSolution::Evaluator->DoRouteEstimation(newRoutes[i].first);

	this->solutionValue += (newSum - oldSum);  
}

StorageAllocationSolution & StorageAllocationSolution::operator=(const StorageAllocationSolution &other){
	
	this->solutionValue = other.solutionValue;
	this->runtime = other.runtime;
	this->minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	//this->totalPenalty = other.totalPenalty;
	
	this->notAllocatedProducts.clear();
	this->productsAllocation.clear(); 
	
	for(auto & key : other.notAllocatedProducts)
		this->notAllocatedProducts.insert(key); 
	for(auto & [key, value] : other.productsAllocation)
		this->productsAllocation[key] = value; 
	for(auto & [key, value] : other.routesByProduct)
		this->routesByProduct[key] = value; 
	
	return *this; 
}


bool StorageAllocationSolution::checkSolution(){

	set<pair<string,int>> positions; 
	set<long> prods;
	for(auto [key, value]: productsAllocation){
		//cout<<key.getID()<<" "<<value.first.getCode()<<" "<<value.second<<endl; 
		positions.insert(make_pair(value.first.getCode(), value.second)); 
		prods.insert(key.getID());
	}

	return prods.size() == positions.size();
}

shared_ptr<AbstractSolution> StorageAllocationSolution::createSharedPtrCopy(shared_ptr<const AbstractSolution> pointer)
{
	auto castPointer = static_cast<const StorageAllocationSolution*>(pointer.get());
    return shared_ptr<AbstractSolution>(new StorageAllocationSolution(castPointer));
}
