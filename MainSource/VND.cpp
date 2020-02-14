//
//  VND.cpp
//  
//  Created by Nilson Mendes on 07/01/2019.
//

#include "VND.h"
#include "IsolatedFamily.h"
#include "AbstractVertex.h"
#include "Graph.h"
#include "Product.h"
#include "Order.h"
#include "Vertex.h"
#include <vector>
using namespace std; 

/**
 *	Default constructor 
 */
VND::VND(){
    
}


/***
 *	Member constructor 
 *  @param warehouse
 *	@param orders
 *  @param prohibitions
 *	@param isolated
 *	@param param
 */
VND::VND(Warehouse &wh, Graph &graph, DistanceMatrix<Vertex> distanceMatrix,vector<Order> &orders, OptimizationConstraints &cons){
    this->warehouse = wh; 
	this->orders = orders;
	this->constraints = cons;
	this->distanceMatrix = distanceMatrix;
	this->Graph = graph; 
	
}

/**
 *	Copy constructor 
 */
VND::VND(const VND & other){
    
}

/**
 *	Algorithm main function 
 */ 
void VND::run(){
    
	int switchNeighborhood = 1; 
	
	AbstractSolution currentSolution = generateInitialSolution(); 
	bestSolution = new StorageAlloactionSolution(currentSolution); 
	
	while(!stopCriteria()){
		
		switch(switchNeighborhood){
			case 1:
				firstLocalSearch(currentSolution);
				break; 
			case 2:
				secondLocalSearch(currentSolution);
				break; 
			case 3:
				thirdLocalSearch(currentSolution); 
				break; 
			case 4:
				pertubation(currentSolution); 
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

AbstractSolution & VND::getSolution(){
    
}

double VND::getSolutionValue(){
    
}

void VND::pertubation(AbstractSolution &solution){
    
}

/**
 *	Swap two products in a same shelf 
 */
void VND::firstLocalSearch(AbstractSolution &solution){
    
}

/**
 * Swap two produtc in the same block but different shelves 
 */
void VND::secondLocalSearch(AbstractSolution &solution){
    
}

/**
 *	Swap the position of two groups of correlated products
 */
void VND::thirdLocalSearch(AbstractSolution &solution){
    
}

bool VND::stopCriteria(){
    
}

bool VND::pertubationCriteria(){
    
}
