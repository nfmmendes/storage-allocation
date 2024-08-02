#pragma once

#include<string>
#include<vector>
#include "IsolatedFamily.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"
using std::vector;
using std::set;
using std::string;

typedef struct pair<Cell, int> Position; 

/** 
 *	@brief The OptimizationContraints class holds information concerning to the 
 *		   problem constraints and parameters. 
 */
class OptimizationConstraints{

	private: 
		/// Optimization parameters defined by the user.
		vector<Parameter> parameters; 							

		/// Prohibitions of putting some products in some places. 
		vector<ProductAllocationProhibitions> allocationProhitions;  

		/// Families that should be isolated in the warehouse.
		vector<IsolatedFamily> isolatedFamilies; 					 

		/// Set of products with some kind of prohibitions.
		set<string> productsCodeWithProhibition; 					 

		/// Set of product families with a weak isolation constraint.  
		set<string> weaklyIsolatedFamilies; 						 

		/// Set of product families with a strong isolation constraint.
		set<string> stronglyIsolatedFamilies; 						  

	public: 
		
		/**
		 *  @brief Default constructor.
		 */
		OptimizationConstraints();
		
		/**
		 * @brief Copy constructor. 
		 * @param other The element to be copied. 
		 */
		OptimizationConstraints(const OptimizationConstraints &other);

		/**
		 *  @brief Get the list of optimization parameters.
		 * @return A list containing the optimization parameters.
		 */
		vector<Parameter> getParameters()const;

		/**
		 *  @brief Get the list of product allocation prohibitions. 
		 *  @return A list containinig all the product allocation prohibitions. 
		 */
		vector<ProductAllocationProhibitions> getProductAllocationProhibitions()const;

		/**
		 *  @brief Get the list of product families that must be isolated with their isolation levels. 
		 *  @return A list containing all the product families that must be isolated with 
		 *          their levels of isolations.  
		 */
		vector<IsolatedFamily> getIsolatedFamilies()const;

		/**
		 *  @brief Get the list of products with some kind of prohibition.
		 *  @return A list of products with some kind of prohibitions. 
		 */
		set<string> & getProductsCodeWithProhibition();

		/**
		 *  @brief Get the list of product families with a weak isolation constraint. 
		 *  @return The list of product families with a weak isolation constraint. 
		 */
		set<string> & getWeaklyIsolatedFamilyCodes();

		/**
		 *  @brief Get the list of product families with a strong isolation constraint. 
		 *  @return The list of families with a strong isolation constraint. 
		 */
		set<string> & getStronglyIsolatedFamilyCodes();

		/**
		 *  @brief Set the optimization parameters.
		 *  @param value A vector containing the new optimization parameters.
		 */
		void setParameters(vector<Parameter> value);

		/**
		 *  @brief Set the product allocation prohibitions.
		 *  @param value The list of product allocation prohibitions. 
		 */
		void setProductAllocationProhibitions(vector<ProductAllocationProhibitions> value);

		/**
		 *  @brief Set the list of product families with some isolation contraint. 
		 *  @param value The list of product families with some isolation constraint. 
		 */
		void setIsolatedFamilies(vector<IsolatedFamily> value);

		/**
		 *  @brief Get if a product allocation is allowed in a given position. 
		 *  @param product The product to be allocated.
		 *  @param newPosition The position of the new allocation. 
		 *  @param newPosition The position of the new allocation. 
		 *  @return True if the product can be allocated in the new position. False otherwise. 
		 */
		bool IsAllocationAllowed(const Product &product, const Position &newPosition);

		/**
		 *  @brief Override of operator=.
		 *  @param other The right side object.
		 *  @return True if the objects contains the same values. False otherwise. 
		 */
		OptimizationConstraints & operator=(const OptimizationConstraints &other);
		OptimizationConstraints(vector<Parameter> param,  vector<ProductAllocationProhibitions> prohibitions, 
								vector<IsolatedFamily> isolated);
};
