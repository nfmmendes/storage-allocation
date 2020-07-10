#include "StorageAllocationSolution.h"
#include <iostream>
#include <vector>
#include <string> 
#include <cmath>
#include "OptimizationConstraints.h"
#include "OptimizationParameters.h"
#include "Vertex.h"
#include "Arc.h"
#include "Cell.h"
#include "StorageSolutionEvaluator.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
using namespace std;
using namespace QuickTSP; 


StorageSolutionEvaluator * StorageAllocationSolution::Evaluator = NULL;

/**
 * Default constructor. Creates an empty solution 
 **/
StorageAllocationSolution::StorageAllocationSolution(){
	
}

/**
 *
 **/
 StorageAllocationSolution::StorageAllocationSolution(StorageAllocationSolution *other){
	this->solutionValue = other->solutionValue;
	this->runtime = other->runtime;
	this->minDelta = other->minDelta;
	isMaximization = other->isMaximization; 
	
	//unsigned long long int solutionIndex;  
		
	for(auto & key : other->notAllocatedProducts)
		this->notAllocatedProducts.insert(key); 
	for(auto & [key, value] : other->productsAllocation)
		this->productsAllocation[key] = value; 

	for(map<Product,vector<PickingRoute*> >::iterator it = other->routesByProduct.begin(); it!= other->routesByProduct.end(); it++){
		this->routesByProduct[it->first].resize(it->second.size());
		for(unsigned int i =0;i<it->second.size(); i++){
			this->routesByProduct[it->first][i] = new PickingRoute();
			this->routesByProduct[it->first][i]->first = it->second[i]->first; 
			this->routesByProduct[it->first][i]->second = it->second[i]->second; 
		}
	}

}

/**
 *
 **/
StorageAllocationSolution::StorageAllocationSolution(StorageAllocationSolution &other){
	this->solutionValue = other.solutionValue;
	this->runtime = other.runtime;
	this->minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	
	//unsigned long long int solutionIndex;  
		
	for(auto & key : other.notAllocatedProducts)
		this->notAllocatedProducts.insert(key); 
	for(auto & [key, value] : other.productsAllocation)
		this->productsAllocation[key] = value; 

	for(map<Product,vector<PickingRoute*> >::iterator it = other.routesByProduct.begin(); it!= other.routesByProduct.end(); it++){
		this->routesByProduct[it->first].resize(it->second.size());
		for(unsigned int i =0;i<it->second.size(); i++){
			this->routesByProduct[it->first][i] = new PickingRoute();
			this->routesByProduct[it->first][i]->first = it->second[i]->first; 
			this->routesByProduct[it->first][i]->second = it->second[i]->second; 
		}
	}

}

/**
 * Member constructor with the more strict informations
 * @param value Objective function value
 * @param time Algorithm runtime
 * @param minDelta The minimal value to consider a solution diferent of another (default value 1e-06)
 * @param maximization Defines if that solution is of a maximization problem (default value true)
 **/
StorageAllocationSolution::StorageAllocationSolution(double value, double time, double minDelta,bool maximization){
	this->solutionValue = value;
	this->runtime = time;
	this->minDelta = minDelta;
	isMaximization = maximization; 
}


void StorageAllocationSolution::setEvaluator(DistanceMatrix<Vertex> *distanceMatrix, map<pair<Cell,int> , Vertex > &vertexByPosition, OptimizationConstraints &constraints){
	if(Evaluator != NULL)
		delete Evaluator;
	Evaluator = new StorageSolutionEvaluator(distanceMatrix,vertexByPosition,constraints);
}

/**
 * Destructor
 **/
StorageAllocationSolution::~StorageAllocationSolution(){
	this->notAllocatedProducts.clear();
	this->productsAllocation.clear(); 


	for(map<Product, vector<PickingRoute *> >::iterator it = this->routesByProduct.begin(); it != this->routesByProduct.end();it++ ){
		for(int i=0;i< it->second.size(); i++){
		//	cout<<"del 1."<<i<<endl; 
			if(it->second[i] != NULL  /*Maybe insert a test here in the future if the cache of routes is implemented*/){
		//		cout<<"Parte A "<<(it->second[i] == NULL)<<" "<<it->second[i]->first.size()<<"\n";
				it->second[i]->first.clear(); 
				//cout<<"Parte B "<<it->second[i]<<"\n";
				delete it->second[i]; 
				//cout<<"Parte C\n";
			}
			it->second.clear();
			
		}
	}
	cout<<"End for"<<endl; 
	this->routesByProduct.clear();
//	cout<<"Clear"<<endl;
/*
	for(auto & [key,value] : this->routesByProduct){
		for(unsigned int i=0; i<value.size();i++){
			if(true ){
				//value[i].clear(); 
				delete value[i];
			}
		}
	}
*/
}

/**
 * 
 **/
void StorageAllocationSolution::setMinDelta(double minDelta){
    this->minDelta = minDelta;
}

/**
 * 
 **/
void StorageAllocationSolution::setRuntime(double time){
    this->runtime = time;
}

/**
 * 
 **/
void StorageAllocationSolution::setSolutionValue(double value){
	cout<<"SET VALUE : "<<value<<endl;
    this->solutionValue = value; 
}

/**
 * 
 **/
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

/**
 * Print the solution in the folder results\\solution 
 **/
void StorageAllocationSolution::printSolution() const{
	ofstream file("results/solutions.txt");
	printToFile(file); 
}

void StorageAllocationSolution::Evaluate(bool evaluateWithTSP){
	set<PickingRoute *> routes; 
	double distance = 0.0; 
	double penalty = 0.0; 
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


/**
 * Print the solution to a given file defined by the ofstream object
 * @param out Ofstream object that carries the data about where the print should be done 
 **/
void StorageAllocationSolution::printToFile(ofstream & out) const{
	out<<productsAllocation.size()<<endl;
	
	for(auto & [product, position] : productsAllocation)
		out<<product.getName()<<" "<<position.first.getCode()<<" "<<position.second<<endl;
	cout<<flush;
	out.close(); 
}

/**
 * Return all the products allocations. Products not allocated are not returned 
 **/
map<Product, pair<Cell,int> > & StorageAllocationSolution::getProductAllocations(){
	return this->productsAllocation;
}

/**
 * Set a specific product allocation 
 * @param cell Cell where the product will be allocated 
 * @param level Level inside the cell where the product will be allocated
 * @param product Product to be allocated 
 **/
void StorageAllocationSolution::setAllocation(const Cell &cell, int level, const Product &product){
	this->productsAllocation[product] =  make_pair(cell,level); 
}

/**
 * Remove the allocation of a product 
 */
void StorageAllocationSolution::removeAllocation(Product &product){	
	this->productsAllocation.erase(product);	
}

/**
 * Change the position of two products in the solution 
 * @param firstProduct First product to be changed
 * @param secondProduct Second product to be changed
 * @param useTSPEvaluator Defines if the method should use TSP Evaluator to define 
 */
void StorageAllocationSolution::proceedSwap(const Product &firstProduct, const Product &secondProduct, bool useTSPEvaluator){
		
	pair<Cell,int> first = productsAllocation[firstProduct];
	pair<Cell,int> second	= productsAllocation[secondProduct];
	
	productsAllocation[firstProduct] = second; 
	productsAllocation[secondProduct] = first;
	
	vector<PickingRoute *> firstRoutes = routesByProduct[firstProduct];
	vector<PickingRoute *> secondRoutes = routesByProduct[secondProduct];
	
	//if a same route has both products in the swap the evaluation don't need to be done
	for(unsigned int i=0; i<firstRoutes.size(); i++){
		if(find(secondRoutes.begin(),secondRoutes.end(), firstRoutes[i]) != secondRoutes.end())
			continue; 
		else if(useTSPEvaluator)
			firstRoutes[i]->second = Evaluator->DoRouteEvaluation(firstRoutes[i]->first);
		else
			firstRoutes[i]->second = Evaluator->DoRouteEstimation(firstRoutes[i]->first);
	}
	
	//if a same route has both products in the swap the evaluation don't need to be done	
	for(unsigned int i=0; i<secondRoutes.size(); i++){
		if(find(firstRoutes.begin(),firstRoutes.end(), secondRoutes[i]) != firstRoutes.end())
			continue; 
		else if(useTSPEvaluator)
			secondRoutes[i]->second = Evaluator->DoRouteEvaluation(secondRoutes[i]->first);
		else
			secondRoutes[i]->second = Evaluator->DoRouteEstimation(secondRoutes[i]->first);
	}
}


/**
 * Set the allocations on warehouse 
 **/
void StorageAllocationSolution::setAllocation(map<Product, pair<Cell,int> > &allocations,const vector<Order> &orders){
	
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



/**
 * Updates the solution based on changing the routes needed to pick all the products in the warehouse,
 * in this way it is not necessary recalculate all the routes in a given 
 * @param oldRoutes Original routes, as they were before the solution change
 * @param newRoutes New routes, as they are after the solution changes 
 * @param useTSP Indicates if the solution needs to be reevaluated based on a TSP solving algorithm or a indirect method
 **/
void StorageAllocationSolution::updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool useTSP){
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

/**
 *	Overload of the operator = 
 */
StorageAllocationSolution & StorageAllocationSolution::operator=(const StorageAllocationSolution &other){
	
	this->solutionValue = other.solutionValue;
	this->runtime = other.runtime;
	this->minDelta = other.minDelta;
	isMaximization = other.isMaximization; 
	
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



