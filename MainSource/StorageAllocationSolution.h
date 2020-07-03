#ifndef STORAGE_ALLOCATION_SOLUTION_H
#define STORAGE_ALLOCATION_SOLUTION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<map>
#include<utility>
#include "Order.h"
#include "AbstractSolution.h"
#include "StorageSolutionEvaluator.h"
#include "OptimizationConstraints.h"
#include "DistanceMatrix.h"
#include "Product.h"
#include "Cell.h"
#include "Vertex.h"
using namespace std;
using namespace QuickTSP;

//Represent a sequence of vertexes to be visited and the cost to visit them all
typedef struct pair< vector<Vertex>, double> PickingRoute; 

class StorageAllocationSolution : public AbstractSolution{

	private: 
		static StorageSolutionEvaluator *Evaluator; 
		static vector<StorageAllocationSolution *> currentSolutions;
		unsigned long long int solutionIndex; 
		map<Product, pair<Cell, int> > productsAllocation; 
		map<Product, vector<PickingRoute *> > routesByProduct; 
		set<Product> notAllocatedProducts; 
        void setSolutionValue(double value) override;
        void setRuntime(double time) override; 
        void setMinDelta(double minDelta) override ;
		void updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);
    public:
		StorageAllocationSolution();
		StorageAllocationSolution(StorageAllocationSolution *other);
		StorageAllocationSolution(StorageAllocationSolution &other);
		StorageAllocationSolution(double value, double time, double minDelta = 1e-06,bool maximization = true);
		~StorageAllocationSolution();
		static void setEvaluator(DistanceMatrix<Vertex> distanceMatrix);
		map<Product, pair<Cell, int> > & getProductAllocations();
		set<Product> & getNonAllocatedProducts()const; 
		void setAllocation(const Cell &cell, int level, const Product &product); 
		void setAllocation(const map<Product, pair<Cell,int> > &allocations); 
		void setNonAllocatedProducts(const set<Product> &nonAllocated);
		void removeAllocation(Product &product);
		void proceedSwap(const Product &firstProduct, const Product &secondProduct,bool evaluateSolutionWithTSP=false);
		void evaluateSolutionWithTSP(vector<Order> &orders,OptimizationConstraints &constraints);
		void evaluateSolutionWithoutTSP(vector<Order> &orders, OptimizationConstraints &constraints);
        void printSolution()const override;
        void printToFile(ofstream & out) const override;
		StorageAllocationSolution & operator=(const StorageAllocationSolution &other); 

};

#endif