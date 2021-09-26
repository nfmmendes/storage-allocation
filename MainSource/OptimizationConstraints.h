#pragma once

#include<string>
#include<vector>
#include "IsolatedFamily.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"

typedef struct pair<Cell, int> Position; 

class OptimizationConstraints{

	private: 
		std::vector<Parameter> parameters; 								///< Optimization parameters defined by the user 
		std::vector<ProductAllocationProhibitions> allocationProhitions;  ///< Prohibitions of putting some products in some places
		std::vector<IsolatedFamily> isolatedFamilies; 					///< Families that should be isolated in the warehouse
		std::set<std::string> productsCodeWithProhibition; 
		std::set<std::string> weaklyIsolatedFamilies; 
		std::set<std::string> stronglyIsolatedFamilies; 

	public: 
		std::vector<Parameter> getParameters()const;
		std::vector<ProductAllocationProhibitions> getProductAllocationProhibitions()const;
		std::vector<IsolatedFamily> getIsolatedFamilies()const;
		std::set<string> & getProductsCodeWithProhibition();
		std::set<std::string> & getWeaklyIsolatedFamilyCodes();
		std::set<std::string> & getStronglyIsolatedFamilyCodes();

		void setParameters(std::vector<Parameter> value);
		void setProductAllocationProhibitions(std::vector<ProductAllocationProhibitions> value);
		void setIsolatedFamilies(std::vector<IsolatedFamily> value);
		bool IsAllocationAllowed(Product &product, Position newPosition);
		OptimizationConstraints();
		OptimizationConstraints(const OptimizationConstraints &other);
		OptimizationConstraints & operator=(const OptimizationConstraints &other);
		OptimizationConstraints(std::vector<Parameter> param,  std::vector<ProductAllocationProhibitions> prohibitions, 
								std::vector<IsolatedFamily> isolated);
};
