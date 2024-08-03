#include<iostream>
#include<cstdlib>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#include "IsolatedFamily.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"
#include "OptimizationConstraints.h"

OptimizationConstraints::OptimizationConstraints(){}

OptimizationConstraints::OptimizationConstraints(const OptimizationConstraints &other){
    this->parameters = other.getParameters();
    this->setProductAllocationProhibitions(other.getProductAllocationProhibitions());
    this->setIsolatedFamilies(other.isolatedFamilies);
}

OptimizationConstraints::OptimizationConstraints(vector<Parameter> param,  vector<ProductAllocationProhibitions> prohibitions, vector<IsolatedFamily> isolated){
    
    parameters = param;
    setProductAllocationProhibitions(prohibitions);
    setIsolatedFamilies(isolated); 
}

const vector<Parameter>& OptimizationConstraints::getParameters()const { 
    return parameters; 
}

const vector<ProductAllocationProhibitions>& OptimizationConstraints::getProductAllocationProhibitions()const{ 
    return allocationProhitions; 
}

const vector<IsolatedFamily> & OptimizationConstraints::getIsolatedFamilies()const{ 
    return isolatedFamilies; 
} 

set<string> & OptimizationConstraints::getProductsCodeWithProhibition() { 
    return productsCodeWithProhibition; 
}

set<string> & OptimizationConstraints::getWeaklyIsolatedFamilyCodes() { 
    return weaklyIsolatedFamilies; 
}

set<string> & OptimizationConstraints::getStronglyIsolatedFamilyCodes() { 
    return stronglyIsolatedFamilies; 
}

void OptimizationConstraints::setParameters(vector<Parameter> value){ 
    parameters = value;
} 

void OptimizationConstraints::setProductAllocationProhibitions(vector<ProductAllocationProhibitions> value){ 	
    allocationProhitions = value;
    productsCodeWithProhibition.clear(); 

    for(unsigned int i=0;i<allocationProhitions.size(); i++)
        productsCodeWithProhibition.insert(allocationProhitions[i].getProduct().getName());
}

void OptimizationConstraints::setIsolatedFamilies(vector<IsolatedFamily> value){ 
    isolatedFamilies = value; 
    weaklyIsolatedFamilies.clear();
    stronglyIsolatedFamilies.clear(); 

    for(unsigned int i=0;i<isolatedFamilies.size(); i++)
        if(isolatedFamilies[i].getForce() == WEAK_ISOLATION)
            weaklyIsolatedFamilies.insert(isolatedFamilies[i].getCode());
        else if(isolatedFamilies[i].getForce() == STRONG_ISOLATION)
            stronglyIsolatedFamilies.insert(isolatedFamilies[i].getCode());
} 

bool OptimizationConstraints::IsAllocationAllowed(const Product &product, const Position& newPosition){
    
    auto query = [product](ProductAllocationProhibitions &other) {  return other.getProduct().getName() == product.getName() ;  };
    vector<ProductAllocationProhibitions>::iterator prohibition = find_if(allocationProhitions.begin(), allocationProhitions.end(), query );
    
    if(prohibition == allocationProhitions.end())
        return true; 
    
    auto forbiddenCells = prohibition->getForbiddenCells();
    auto cellQuery = [newPosition](Cell &other){ return newPosition.first.getCode() == other.getCode(); }; 
    if( find_if(forbiddenCells.begin(), forbiddenCells.end(), cellQuery) == forbiddenCells.end())
        return true; 
    
    auto forbiddenShelves = prohibition->getForbiddenShelves(); 
    auto shelfQuery = [newPosition](Shelf &other){ return newPosition.first.getIdShelf() == other.getId(); }; 
    if (find_if(forbiddenShelves.begin(), forbiddenShelves.end(), shelfQuery) == forbiddenShelves.end())
        return true; 

    return false;
}

/**
 * 
 * */
OptimizationConstraints & OptimizationConstraints::operator=(const OptimizationConstraints &other){
    this->parameters = other.getParameters();
    this->setProductAllocationProhibitions(other.getProductAllocationProhibitions());
    this->setIsolatedFamilies(other.getIsolatedFamilies()); 
    
    return *this;
}

