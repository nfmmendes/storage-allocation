#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include "Order.h"
#include "AbstractSolution.h"
#include "StorageSolutionEvaluator.h"
#include "OptimizationConstraints.h"
#include "DistanceMatrix.h"
#include "Product.h"
#include "Cell.h"
#include "Vertex.h"
using namespace QuickTSP;
using std::map;
using std::vector;
using std::string;
using std::set;
using std::pair;
using std::ofstream;
using std::shared_ptr;

class OptimizationParameters;

//Represent a sequence of vertexes to be visited and the cost to visit them all
typedef struct pair< vector<Vertex>, double> PickingRoute; 

/**
 * @brief Class <c> StorageAllocationSolution </c> holds and manipulates all information needed
 * to represent the storage allocation problem solution. 
 */
class StorageAllocationSolution : public AbstractSolution{

	private: 
	
		static StorageSolutionEvaluator *Evaluator; 
		static vector<StorageAllocationSolution *> currentSolutions;
		unsigned long long int solutionIndex; 
		map<Product, Position > productsAllocation; 
		map<Product, vector<PickingRoute *> > routesByProduct; 
		set<Product> notAllocatedProducts; 
		double totalPenalty; 
        
		/**
		 * @brief Set the solution value. 
		 * @param value The solution value. 
		 */
		void setSolutionValue(double value) override;

		/**
         * @brief Set the total run time to get the solution. 
         * @param time The total run time. 
		 */
        void setRuntime(double time) override; 

		/**
         * @brief Set the minimum delta to consider two solutions different. 
         * @param minDelta The minimum delta to consider two solutions different. 
		 */
        void setMinDelta(double minDelta) override;

		/**
		 * @brief Update the solution value after a replacement of routes. 
		 * @param oldRoutes Old routes.
		 * @param newRoutes New routes. 
		 * @param evaluateSolutionWithTSP True if the new solution value must be evaluated using 
		 *                                 the TSP algorithm, false otherwise. 
		 */
		void updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);

		/**
		 * @brief Update a picking route and returns the objective function variation after this update
		 * @param original Picking route that will be alterated 
		 * @param oldVertex Vertex that will be removed of the route
		 * @param newVertex Vertex that will be included in the new route
		 * @param useTSPEvaluator Param to define how the route new cost will be calculated 
		 * */
		double getVariationAndUpdateAfterSwap(PickingRoute *original, Vertex &oldVertex, Vertex &newVertex, bool useTSPEvaluator);
    public:
		static int countSolutions; 

		/**
		 * @brief Constructor.
		 */
		StorageAllocationSolution();

		/**
		 * @brief Pointer copy constructor. 
		 * @param other Object to be copied. 
		 */
		StorageAllocationSolution(const StorageAllocationSolution *other);

		/**
		 * @brief Copy constructor. 
		 * @param other Object to be copied. 
		 */
		StorageAllocationSolution(const StorageAllocationSolution &other);

		/**
		 * @brief Constructor.
		 * @param value The solution value. 
		 * @param time The run time to get the solution. 
		 * @param minDelta The min delta to consider this solution different from another. 
		 * @param maximization If it is a solution of an optimization problem. 
		 */
		StorageAllocationSolution(double value, double time, double minDelta = 1e-06,bool maximization = true);

		/**
		 * @brief Destructor. 
		 */
		~StorageAllocationSolution();

		/**
		 * @brief Set the solution evaluator based on input. 
		 * @param distanceMatrix The distance matrix based the warehouse graph representation.  
		 * @param positionToVertex The map from warehouse position to graph vertexes. 
		 * @param blocks  The warehouse blocks. 
		 * @param optimizationConstraints The optimization constraints.
		 */
		static void setEvaluator(const DistanceMatrix<Vertex> *distanceMatrix, map<Position , Vertex > & positionToVertex, 
								 const vector<Block> &blocks, OptimizationConstraints & optimizationConstraints);
		
		/**
		 * @brief The the product allocations. 
		 * @return A map from each product to its allocation. 
		 */
		map<Product, pair<Cell, int> > & getProductAllocations();

		/**
		 * @brief Get the non-allocated products in the solution. 
		 * @return The set of non allocated products. 
		 */
		set<Product> & getNonAllocatedProducts(); 		 

		/**
		 * @brief Get solution total penalty.
		 * @return The solution total penalty. 
		 */
		double getTotalPenalty(); 

		/**
		 * @brief Set a single product allocation. 
		 * @param cell The cell in which the product will be allocated. 
		 * @param level The level of the cell in which the product will be allocated. 
		 * @param product The product.
		 */
		void setAllocation(const Cell &cell, int level, const Product &product);  
		
		/**
		/// @brief Set solution total penalty. 
		/// @param value Solution total penalty. 
		*/
		void setTotalPenalty(const double value); 
		
		/**
		 * @brief Set the product allocations. 
		 * @param allocations The product allocations.
		 * @param orders The set of orders to the products allocated. 
		 */
		void setAllocation(MapAllocation &allocations,const vector<Order> &orders);
		
		/**
		 * @brief Set the picking routes by each product. 
		 * @param other A map from a product to its picking routes. 
		 */
		void setRoutesByProduct(map<Product, vector<PickingRoute * > > &other);
		
		/**
		 * @brief Set the non allocated products in the solution.
		 * @param nonAllocated The set of non allocated products. 
		 */
		void setNonAllocatedProducts(const set<Product> &nonAllocated);

		/**
		 * @brief Remove allocation from solution.
		 * @param product Product about to have its allocation removed. 
		 */
		void removeAllocation(Product &product);

		/**
		 * @brief Change the position of two products in the solution 
		 * @param firstProduct First product to be changed
		 * @param secondProduct Second product to be changed
		 * @param useTSPEvaluator Defines if the method should use TSP Evaluator to define 
		 */
		void proceedSwap(const Product &firstProduct, const Product &secondProduct,bool evaluateSolutionWithTSP=false);

		/**
		 * @brief Evaluate the solution. 
		 * @param evaluateWithTSP True if the solution must be evaluated with TSP algorithm.
		 */
		void Evaluate(bool evaluateWithTSP = true);

		/**
         * @brief Print the solution on screen. 
		 */
        void printSolution()const override;

		/**
         * @brief Print the solution to file. 
         * @param out A reference to file stream object.
		 */
        void printToFile(ofstream & out) const override;

		/**
		 * @brief Override assignment operator =.
		 * @param other The right hand side object. 
		 * @return A reference t o the modified object. 
		 */
		StorageAllocationSolution & operator=(const StorageAllocationSolution &other); 

		/**
		 * @brief Check the solution.
		 * @return True if the solution is valid, false otherwise.
		 */
		bool checkSolution();

		/**
		 * @brief Create a copy of the object passed as paremeter encapsulated in a smart pointer.
		 * @param pointer The object to be copied.
		 */
		static shared_ptr<AbstractSolution> createSharedPtrCopy(shared_ptr<const AbstractSolution> pointer);
};
