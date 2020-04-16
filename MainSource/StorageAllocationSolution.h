#ifndef STORAGE_ALLOCATION_SOLUTION_H
#define STORAGE_ALLOCATION_SOLUTION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<map>
#include<utility>
#include "AbstractSolution.h"
#include "StorageSolutionEvaluator.h"
#include "Product.h"
#include "Cell.h"
#include "Vertex.h"
using namespace std;
using namespace QuickTSP;

//Represent a sequence of vertexes to be visited and the cost to visit them all
typedef struct pair< vector<Vertex>, double> PickingRoute; 

class StorageAllocationSolution : public AbstractSolution{

	private: 
		static StorageSolutionEvaluator *evaluator; 
		static vector<StorageAllocationSolution *> currentSolutions;
		unsigned long long int solutionIndex; 
		map<Product, pair<Cell, int> > productAllocation; 
		map<Product, vector<PickingRoute *> > routesByProduct; 
		set<Product> notAllocatedProducts; 
        void setSolutionValue(double value);
        void setRuntime(double time); 
        void setMinDelta(double minDelta) ;
		void updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);
    public:
		StorageAllocationSolution();
		StorageAllocationSolution(StorageAllocationSolution *other);
		StorageAllocationSolution(StorageAllocationSolution &other);
		StorageAllocationSolution(double value, double time, double minDelta = 1e-06,bool maximization = true);
		~StorageAllocationSolution();
		map<Product, pair<Cell, int> > & getProductAllocations();
		void setAllocation(const Cell &cell, int level, const Product &product); 
		void removeAllocation(Product &product);
		void proceedSwap(const Product &firstProduct, const Product &secondProduct,bool evaluateSolutionWithTSP=false);
		void evaluateSolutionWithTSP();
		void evaluateSolutionWithoutTSP();
        void printSolution() const ;
        void printToFile(ofstream & out) const override;
		StorageAllocationSolution & operator=(const StorageAllocationSolution &other); 

};

#endif