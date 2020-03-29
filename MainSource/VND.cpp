//
//  VND.cpp
//  
//  Created by Nilson Mendes on 07/01/2019.
//

#include "VND.h"
#include "IsolatedFamily.h"
#include "AbstractVertex.h"
#include "StorageAllocationSolution.h"
#include "Product.h"
#include "Order.h"
#include "Vertex.h"
#include <vector>
using namespace std; 
using namespace QuickTSP; 

/**
 *	Default constructor 
 */
VND::VND(){
    
}


/***
 *	Member constructor 
 *  @param warehouse
 *	@param orders
 *  @param vertexByCell
 *  @param prohibitions
 *	@param isolated
 *	@param param
 */
VND::VND(vector<Product> & prods, Warehouse &wh, DistanceMatrix<Vertex> distMatrix, map<pair<Cell, int>, Vertex> &vertexByCell,
		 vector<Order> &orders, OptimizationConstraints &cons){
    this->products = prods;	
	this->warehouse = wh; 
	this->orders = orders;
	this->constraints = cons;
	this->vertexByCell = vertexByCell; 
	this->distanceMatrix = distMatrix;
}

/**
 *	Copy constructor 
 */
VND::VND(const VND & other){

	for(unsigned int i=0;i<other.products.size();i++)
		this->products.push_back(other.products[i]); 
	
	for(unsigned int i=0; i< other.orders.size(); i++)
		this->orders.push_back(other.orders[i]); 
    
	this->warehouse = * (new Warehouse(other.warehouse)); 
	this->constraints = other.constraints;
}


AbstractSolution * VND::generateInitialSolution(){
	
	return NULL; 
}


/**
 *	Algorithm main function 
 */ 
void VND::run(){
    
	int switchNeighborhood = 1; 
	
	AbstractSolution *currentSolution = generateInitialSolution(); 
	bestSolution = new StorageAllocationSolution( (StorageAllocationSolution *)currentSolution); 
	
	while(!stopCriteria()){
		
		switch(switchNeighborhood){
			case 1:
				firstLocalSearch(*currentSolution);
				break; 
			case 2:
				secondLocalSearch(*currentSolution);
				break; 
			case 3:
				thirdLocalSearch(*currentSolution); 
				break; 
			case 4:
				pertubation(*currentSolution); 
				switchNeighborhood = 1; 
				break; 
			case 5:
				break;
		}
		switchNeighborhood++; 
		
		if(/*put criteria*/false)
			switchNeighborhood = 1;
	}
	
	
}

/**
 *	NOT IMPLEMENTED 
 */
AbstractSolution * VND::getSolution(){
    return NULL; 
}

/**
 *	NOT IMPLEMENTED 
 */
double VND::getSolutionValue(){
    return 0; 
}

/**
 *	NOT IMPLEMENTED 
 */
void VND::pertubation(AbstractSolution &solution){
    double value = solution.getSolutionValue();
	cout<<value<<endl;
}

/**
 *	Swap two products in a same shelf 
 */
void VND::firstLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
	cout<<value<<endl;
}

/**
 * Swap two produtc in the same block but different shelves 
 */
void VND::secondLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
	cout<<value<<endl;
}

/**
 *	Swap the position of two groups of correlated products
 */
void VND::thirdLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
	cout<<value<<endl;
}

/**
 *	NOT IMPLEMENTED 
 */
bool VND::stopCriteria(){
   return false;  
}

/**
 *	NOT IMPLEMENTED 
 */
bool VND::pertubationCriteria(){
    return false;
}
