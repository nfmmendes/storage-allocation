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
typedef pair< vector<Vertex>, double> PickingRoute; 

class StorageAllocationSolution : AbstractSolution{

	private: 
		static StorageSolutionEvaluator *evaluator; 
		static vector<StorageAllocationSolution *> currentSolutions;
		unsigned long long int solutionIndex; 
    protected: 
		map<pair<Cell, int> , Product> productAllocation; 
		map<Product, vector<PickingRoute *> > routesByProduct; 
		set<Product> notAllocatedProducts; 
        virtual void setSolutionValue(double value);
        virtual void setRuntime(double time); 
        virtual void setMinDelta(double minDelta);
		void updateSolutionValue(vector<PickingRoute> &oldRoutes, vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);
    public:
		map< pair<Cell, int>, Product> & getProductAllocation() const;
		void setAllocation(const Cell &cell, int level, const Product &product); 
		void removeAllocation(const Cell &cell, int level);
		void proceedSwap(map<Cell,int> &first, map<Cell,int> &second, bool evaluateWithTSP, bool evaluateSolutionWithTSP=false);
		void evaluateSolutionWithTSP();
		void evaluateSolutionWithoutTSP();
        virtual void printSolution() const;
        virtual void printToFile(const ofstream & out) const;

};

#endif