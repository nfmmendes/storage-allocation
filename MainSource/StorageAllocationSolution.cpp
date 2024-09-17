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
using std::copy;
using std::back_inserter;
using std::make_shared;


StorageSolutionEvaluator * StorageAllocationSolution::Evaluator = NULL;
int StorageAllocationSolution::countSolutions = 0;

StorageAllocationSolution::StorageAllocationSolution(){
	StorageAllocationSolution::countSolutions++;
}

StorageAllocationSolution::StorageAllocationSolution(const StorageAllocationSolution *other){
	StorageAllocationSolution::countSolutions++;
	solutionValue = other->solutionValue;
	runtime = other->runtime;
	minDelta = other->minDelta;
	isMaximization = other->isMaximization; 
	totalPenalty = other->totalPenalty; 

	copy(begin(other->notAllocatedProducts), end(other->notAllocatedProducts), 
		inserter(notAllocatedProducts, end(notAllocatedProducts)));
	
	copy(begin(other->productsAllocation), end(other->productsAllocation), 
		inserter(productsAllocation, end(productsAllocation)));

	for(const auto& [product, pickingRoutes] : other->routesByProduct){
		transform(begin(pickingRoutes), end(pickingRoutes), back_inserter(routesByProduct[product]), [](auto* v){
				return new PickingRoute(v->first, v->second);
		});
	}
}

StorageAllocationSolution::StorageAllocationSolution(const StorageAllocationSolution &other):AbstractSolution(other){
	
	StorageAllocationSolution::countSolutions++;
	solutionValue = other.solutionValue;
	runtime = other.runtime;
	minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	totalPenalty = other.totalPenalty; 
	
	copy(begin(other.notAllocatedProducts), end(other.notAllocatedProducts), 
		inserter(notAllocatedProducts, end(notAllocatedProducts)));
	
	copy(begin(other.productsAllocation), end(other.productsAllocation), 
		inserter(productsAllocation, end(productsAllocation)));

	for(const auto& [product, pickingRoutes] : other.routesByProduct){
		transform(begin(pickingRoutes), end(pickingRoutes), back_inserter(routesByProduct[product]), [](auto* v){
				return new PickingRoute(v->first, v->second);
		});
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
	for(auto& [product, pickingRoutes] : routesByProduct){
		for(auto & pickingRoute : pickingRoutes){ 
			pickingRoute->first.clear(); 
			delete pickingRoute; 
		}
		pickingRoutes.clear();
	}

	routesByProduct.clear();
}

void StorageAllocationSolution::setMinDelta(double minDelta){
    minDelta = minDelta;
}

void StorageAllocationSolution::setRuntime(double time){
    runtime = time;
}

void StorageAllocationSolution::setSolutionValue(double value){
    solutionValue = value; 
}

void StorageAllocationSolution::setRoutesByProduct(map<Product, vector<PickingRoute * > > &other){

	for(auto& [product, routes]: routesByProduct){
		for(auto* pickingRoute : routes){			
			pickingRoute->first.clear();
			delete pickingRoute;
		}
		routes.clear(); 
	}

	for(const auto& [product, routes] : other){
		transform(begin(routes), end(routes), back_inserter(routesByProduct[product]), [](auto* v){
				return new PickingRoute(v->first, v->second);
		});
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
	
	for(const auto& [key, routeList] : routesByProduct)
		copy(begin(routeList), end(routeList), inserter(routes, end(routes)));
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

const map<Product, pair<Cell,int> > & StorageAllocationSolution::getProductAllocations() const{
	return productsAllocation;
}

double StorageAllocationSolution::getTotalPenalty() const {
	return totalPenalty;
}

const set<Product> & StorageAllocationSolution::getNonAllocatedProducts() const{
	return notAllocatedProducts; 
}

void StorageAllocationSolution::setAllocation(const Cell &cell, int level, const Product &product){
	productsAllocation[product] =  make_pair(cell,level); 
}

void StorageAllocationSolution::removeAllocation(const Product &product){	
	productsAllocation.erase(product);	
} 

void StorageAllocationSolution::setTotalPenalty(const double value){ 
	totalPenalty = value; 
} 
 
void StorageAllocationSolution::proceedSwap(const Product &firstProduct, const Product &secondProduct, bool useTSPEvaluator){
		
	const auto& first { productsAllocation[firstProduct] };
	const auto& second	{ productsAllocation[secondProduct] };
	const auto& firstVertex { Evaluator->getVertex(first) };
	const auto& secondVertex { Evaluator->getVertex(second) };
	double delta = 0.0; 

	double penaltyDelta = StorageAllocationSolution::Evaluator->evaluatePenaltyDelta(getProductAllocations(), firstProduct, secondProduct);
	totalPenalty  += penaltyDelta; 
	
	productsAllocation[firstProduct] = second; 
	productsAllocation[secondProduct] = first;
	
	const auto& firstRoutes { routesByProduct[firstProduct] };
	const auto& secondRoutes { routesByProduct[secondProduct] };
	
	//std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

	for(const auto& route : firstRoutes)
		delta += getVariationAndUpdateAfterSwap(route, *firstVertex, *secondVertex, useTSPEvaluator);

	for(const auto& route : secondRoutes)
		delta += getVariationAndUpdateAfterSwap(route, *secondVertex, *firstVertex, useTSPEvaluator);

	this->solutionValue += delta + penaltyDelta; 
}

double StorageAllocationSolution::getVariationAndUpdateAfterSwap(PickingRoute *original,const Vertex &oldVertex, const Vertex &newVertex, bool useTSPEvaluator){

	auto &route = original->first;

	//if a same route has both products in the swap the evaluation don't need to be done
	if(find_if(begin(route), end(route), [newVertex](auto v){ return *v == newVertex; }) != route.end())
		return 0;

	std::replace_if(route.begin(), route.end(), [oldVertex](const shared_ptr<Vertex>& v){
		return *(v.get()) == oldVertex;
	}, make_shared<Vertex>(newVertex));

	double oldValue = original->second; 
	original->second = useTSPEvaluator ? Evaluator->DoRouteEvaluation(original->first) : 
										 Evaluator->DoRouteEstimation(original->first);
	
	if(original->first.size() <= 4){
	
	}

	return original->second - oldValue; 
}

void StorageAllocationSolution::setAllocation(MapAllocation &allocations, const vector<Order> &orders){
	
	for(auto &[product,allocation] : allocations)
		this->productsAllocation[product] = allocation; 

	for(const Order & order : orders){
		const auto& items { order.getOrderItems() };
		vector<pair<Cell,int> > positions; 

		for(unsigned int i=0; i< items.size(); i++ ){
			if(allocations.find(items[i].first) != allocations.end() )
				positions.push_back(allocations[items[i].first]); 
		}

		const auto& vertexes { StorageAllocationSolution::Evaluator->getVertexes(positions) }; 
		for(auto &[product, quantity] : items ){
			auto* inserted = new PickingRoute(); 
			copy(begin(vertexes.first), end(vertexes.first), back_inserter(inserted->first));
			routesByProduct[product].push_back(inserted);
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

	solutionValue += (newSum - oldSum);  
}

StorageAllocationSolution & StorageAllocationSolution::operator=(const StorageAllocationSolution &other){
	
	solutionValue = other.solutionValue;
	runtime = other.runtime;
	minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	//totalPenalty = other.totalPenalty;
	
	notAllocatedProducts.clear();
	productsAllocation.clear(); 
	
	for(auto & key : other.notAllocatedProducts)
		notAllocatedProducts.insert(key); 
	for(auto & [key, value] : other.productsAllocation)
		productsAllocation[key] = value; 
	for(auto & [key, value] : other.routesByProduct)
		routesByProduct[key] = value; 
	
	return *this; 
}


bool StorageAllocationSolution::checkSolution() const{

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
