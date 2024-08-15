//  VND.hpp
//
//  Created by Nilson Mendes on 07/01/2019.
//

#pragma once

#include <stdio.h>
#include <vector>
#include "Order.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"
#include "AbstractSolution.h"
#include "IsolatedFamily.h"
#include "Graph.h"
#include "Product.h"
#include "OptimizationConstraints.h"
#include "DistanceMatrix.h"
#include "StorageAllocationSolution.h"
#include "Vertex.h"
using namespace QuickTSP; 

/**
 * @brief Class <c> VND </c> implements a Variable Neighborhood Descent heuristic
 * to the Storage Allocation Problem. 
 */
class VND {
    
    public:
        /**
         * @brief Constructor. 
         */
        VND();

        /**
         * @brief Constructor. 
         * @param prods Products to be allocated.
         * @param wh Warehouse layout. 
         * @param distMatrix Warehouse distance matrix. 
         * @param vertexByCell Map between a position (cell, level) and a graph vertex. 
         * @param orders Product orders.
         * @param cons Optimization constraints. 
         */
        VND(std::vector<Product> & prods, Warehouse &wh, DistanceMatrix<Vertex> distMatrix, 
			std::map<std::pair<Cell, int>, Vertex> &vertexByCell, std::vector<Order> &orders, OptimizationConstraints &cons);

        /**
         * @brief Copy constructor. 
         * @param other Object to be copied. 
         */
        VND(const VND & other);

        /**
         * @brief Run the heuristic. 
         */
        void run();

        /**
         * @brief Get the solution obtained by the heuristic. 
         * @return A solution to the problem. 
         */ 
        AbstractSolution *getSolution();

        /**
         * @brief Get the solution value. 
         * @return The solution value. 
         */
        double getSolutionValue();
    
    private:
        Warehouse warehouse;								    ///< Warehouse where the products will be stored 
		DistanceMatrix<Vertex> distanceMatrix;                  ///< Warehouse distance matrix.
		std::map<std::pair<Cell, int>, Vertex> vertexByCell;    ///< Map to convert a position (cell, level) in a vertex.
        std::vector<Order> orders;								///< Orders to be used in the evaluation
        OptimizationConstraints constraints; 				    ///< Allocation constraints and parameters 
        AbstractSolution * bestSolution;					    ///< Best solution found
        double bestSolutionValue;							    ///< Best solution value
		std::vector<Product> products; 							///< List of products to be allocated; 

        /**
         * @brief Pertubate a solution. 
         * @param solution The solution to be pertubated. 
         */
        void pertubation(AbstractSolution &solution);		

        /**
         * @brief Run the first local search on a solution.
         * @param solution The solution that will have its neighborhood explored. 
         */
        void firstLocalSearch(AbstractSolution &solution); 	

        /**
         * @brief Run the second local search on a solution.
         * @param solution The solution that will have its neighborhood explored. 
         */
        void secondLocalSearch(AbstractSolution &solution);	

        /**
         * @brief Run the third local search on a solution.
         * @param solution The solution that will have its neighborhood explored. 
         */
        void thirdLocalSearch(AbstractSolution &solution);	

        /**
         * @brief Get if the heuristic stop criteria has been reached. 
         * @return True if the heuristic stop criteria has been reached, false otherwise. 
         */
        bool stopCriteria();								
        
        /**
         * @brief Get if the heuristic pertubation criteria has been reached. 
         * @return True if the heuristic pertubation criteria has been reached, false otherwise. 
         */
        bool pertubationCriteria();

        /**
		 * @brief Generate the heuristic initial solution.
		 * @return An initial solution to the problem. 
         */
		AbstractSolution * generateInitialSolution();
};
