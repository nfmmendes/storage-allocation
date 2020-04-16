//
//  VND.hpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#ifndef VND_hpp
#define VND_hpp

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
using namespace std;
using namespace QuickTSP; 


class VND {
    
    public:
        VND();
        VND(vector<Product> & prods, Warehouse &wh, DistanceMatrix<Vertex> distMatrix, 
			map<pair<Cell, int>, Vertex> &vertexByCell, vector<Order> &orders, OptimizationConstraints &cons);
        VND(const VND & other);
        void run();
        AbstractSolution *getSolution();
        double getSolutionValue();
    
    
    private:
        Warehouse warehouse;								///< Warehouse where the products will be stored 
		DistanceMatrix<Vertex> distanceMatrix;
		map<pair<Cell, int>, Vertex> vertexByCell;
        vector<Order> orders;								///< Orders to be used in the evaluation
        OptimizationConstraints constraints; 				///< Allocation constraints and parameters 
        AbstractSolution * bestSolution;					///< Best solution found
        double bestSolutionValue;							///< Best solution value
		vector<Product> products; 							///< List of products to be allocated; 
        void pertubation(AbstractSolution &solution);		
        void firstLocalSearch(AbstractSolution &solution); 	
        void secondLocalSearch(AbstractSolution &solution);	
        void thirdLocalSearch(AbstractSolution &solution);	
        bool stopCriteria();								
        bool pertubationCriteria();
		AbstractSolution * generateInitialSolution();
		
    
};

#endif /* VND_hpp */
