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
		map<Product, Position > productsAllocation; 
		map<Product, vector<PickingRoute *> > routesByProduct; 
		set<Product> notAllocatedProducts; 
		double totalPenalty; 
        void setSolutionValue(double value) override;
        void setRuntime(double time) override; 
        void setMinDelta(double minDelta) override ;
		void updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);
		double getVariationAndUpdateAfterSwap(PickingRoute *original,Vertex &oldVertex, Vertex &newVertex, bool useTSPEvaluator);
    public:
		static int countSolutions; 
		StorageAllocationSolution();
		StorageAllocationSolution(StorageAllocationSolution *other);
		StorageAllocationSolution(StorageAllocationSolution &other);
		StorageAllocationSolution(double value, double time, double minDelta = 1e-06,bool maximization = true);
		~StorageAllocationSolution();
		static void setEvaluator(DistanceMatrix<Vertex> *, map<Position , Vertex > &, vector<Block> & ,OptimizationConstraints &);
		map<Product, pair<Cell, int> > & getProductAllocations();
		set<Product> & getNonAllocatedProducts()const; 		 
		double getTotalPenalty(); 
		void setAllocation(const Cell &cell, int level, const Product &product);  
		void setTotalPenalty(const double value); 
		void setAllocation(MapAllocation &allocations,const vector<Order> &orders);
		void setRoutesByProduct(map<Product, vector<PickingRoute * > > &other);
		void setNonAllocatedProducts(const set<Product> &nonAllocated);
		void removeAllocation(Product &product);
		void proceedSwap(const Product &firstProduct, const Product &secondProduct,bool evaluateSolutionWithTSP=false);
		void Evaluate(bool evaluateWithTSP = true);
        void printSolution()const override;
        void printToFile(ofstream & out) const override;
		StorageAllocationSolution & operator=(const StorageAllocationSolution &other); 

};

#endif