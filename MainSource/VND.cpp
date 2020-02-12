//
//  VND.cpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#include "VND.h"
#include "IsolatedFamily.h"

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
VND::VND(Warehouse &wh, vector<Order> &orders, vector<ProductAllocationProhibitions> &prohibitions, vector<IsolatedFamily> &isolated, vector<Parameter> &param){
    this->warehouse = wh; 
	this->orders = orders;
	
}

/**
 *	Copy constructor 
 */
VND::VND(const VND & other){
    
}

void VND::run(){
    
}

Solution & VND::getSolution(){
    
}

double VND::getSolutionValue(){
    
}

void VND::pertubation(Solution &solution){
    
}

void VND::firstLocalSearch(Solution &solution){
    
}

void VND::secondLocalSearch(Solution &solution){
    
}

void VND::thirdLocalSearch(Solution &solution){
    
}

bool VND::stopCriteria(){
    
}

bool VND::pertubationCriteria(){
    
}
