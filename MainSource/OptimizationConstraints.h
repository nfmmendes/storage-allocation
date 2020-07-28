#ifndef OPTIMIZATION_CONSTRAINTS_H
#define OPTIMIZATION_CONSTRAINTS_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include "IsolatedFamily.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"
using namespace std; 

typedef struct pair<Cell, int> Position; 

class OptimizationConstraints{

	private: 
		vector<Parameter> parameters; 								///< Optimization parameters defined by the user 
		vector<ProductAllocationProhibitions> allocationProhitions;  ///< Prohibitions of putting some products in some places
		vector<IsolatedFamily> isolatedFamilies; 					///< Families that should be isolated in the warehouse
		
	public: 
		vector<Parameter> getParameters()const { return parameters; }
		vector<ProductAllocationProhibitions> getProductAllocationProhibitions()const{ return allocationProhitions; }
		vector<IsolatedFamily> getIsolatedFamilies()const{ return isolatedFamilies; } 
		
		void setParameters(vector<Parameter> value){ parameters = value;} 
		void setProductAllocationProhibition(vector<ProductAllocationProhibitions> value){ allocationProhitions = value;}
		void setIsolatedFamilies(vector<IsolatedFamily> value){ isolatedFamilies = value; } 
		bool IsAllocationAllowed(Product &product, Position newPosition);

		/**
		 *	Default constructor
		 */
		OptimizationConstraints(){
			
		}
		
		/**
		 *	Copy constructor
		 */
		OptimizationConstraints(const OptimizationConstraints &other){
			this->parameters = other.getParameters();
			this->allocationProhitions = other.getProductAllocationProhibitions();
			this->isolatedFamilies= other.isolatedFamilies;
		}

		OptimizationConstraints & operator=(const OptimizationConstraints &other){
			this->parameters = other.getParameters();
			this->allocationProhitions = other.getProductAllocationProhibitions();
			this->isolatedFamilies= other.getIsolatedFamilies();
			
			return *this;
		}
		
		/**
		 *	Member constructor
		 *  @param param Optimization parameters 
		 *  @param prohibition Product allocation prohibitions
		 *  @param isolated Isolated families 
		 */
		OptimizationConstraints(vector<Parameter> param,  vector<ProductAllocationProhibitions> prohibitions, vector<IsolatedFamily> isolated){
			
			parameters = param;
			allocationProhitions = prohibitions;
			isolatedFamilies = isolated; 
		}
};

#endif