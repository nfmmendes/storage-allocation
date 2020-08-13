#ifndef OPTIMIZATION_CONSTRAINTS_H
#define OPTIMIZATION_CONSTRAINTS_H

#include<iostream>
#include<cstdlib>
#include<vector>
#include<set>
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
		set<string> productsCodeWithProhibition; 
		set<string> weaklyIsolatedFamilies; 
		set<string> stronglyIsolatedFamilies; 

	public: 
		vector<Parameter> getParameters()const;
		vector<ProductAllocationProhibitions> getProductAllocationProhibitions()const;
		vector<IsolatedFamily> getIsolatedFamilies()const;
		set<string> & getProductsCodeWithProhibition();
		set<string> & getWeaklyIsolatedFamilyCodes();
		set<string> & getStronglyIsolatedFamilyCodes();

		void setParameters(vector<Parameter> value);
		void setProductAllocationProhibitions(vector<ProductAllocationProhibitions> value);
		void setIsolatedFamilies(vector<IsolatedFamily> value);
		bool IsAllocationAllowed(Product &product, Position newPosition);
		OptimizationConstraints();
		OptimizationConstraints(const OptimizationConstraints &other);
		OptimizationConstraints & operator=(const OptimizationConstraints &other);
		OptimizationConstraints(vector<Parameter> param,  vector<ProductAllocationProhibitions> prohibitions, vector<IsolatedFamily> isolated);
};

#endif