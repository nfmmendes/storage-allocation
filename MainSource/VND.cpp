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
using namespace QuickTSP; 

VND::VND(){
    
}

VND::VND(vector<Product> & prods, Warehouse &wh, DistanceMatrix<Vertex> distMatrix, map<pair<Cell, int>, Vertex> &vertexByCell,
		 vector<Order> &orders, OptimizationConstraints &cons){
    this->products = prods;	
	this->warehouse = wh; 
	this->orders = orders;
	this->constraints = cons;
	this->vertexByCell = vertexByCell; 
	this->distanceMatrix = distMatrix;
}

VND::VND(const VND & other){

	copy(begin(other.products), end(other.products), back_inserter(products));
	copy(begin(other.orders), end(other.orders), back_inserter(orders));
	
	this->warehouse = * (new Warehouse(other.warehouse)); 
	this->constraints = other.constraints;
}

AbstractSolution * VND::generateInitialSolution(){
	return NULL; 
}

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

AbstractSolution * VND::getSolution(){
    return NULL; 
}

double VND::getSolutionValue(){
    return 0; 
}

void VND::pertubation(AbstractSolution &solution){
    double value = solution.getSolutionValue();
}

void VND::firstLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
}

void VND::secondLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
}

void VND::thirdLocalSearch(AbstractSolution &solution){
    double value = solution.getSolutionValue();
}

bool VND::stopCriteria(){
   return false;  
}

bool VND::pertubationCriteria(){
    return false;
}
