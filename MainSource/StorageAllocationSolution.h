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

class OptimizationParameters;

//Represent a sequence of vertexes to be visited and the cost to visit them all
typedef struct pair< vector<Vertex>, double> PickingRoute; 

class StorageAllocationSolution : public AbstractSolution{

	private: 
	
		static StorageSolutionEvaluator *Evaluator; 
		static std::vector<StorageAllocationSolution *> currentSolutions;
		unsigned long long int solutionIndex; 
		std::map<Product, Position > productsAllocation; 
		std::map<Product, std::vector<PickingRoute *> > routesByProduct; 
		std::set<Product> notAllocatedProducts; 
		double totalPenalty; 
        void setSolutionValue(double value) override;
        void setRuntime(double time) override; 
        void setMinDelta(double minDelta) override ;
		void updateSolutionValue(std::vector<PickingRoute> &oldRoutes, std::vector<PickingRoute> &newRoutes, bool evaluateSolutionWithTSP=false);
		double getVariationAndUpdateAfterSwap(PickingRoute *original, Vertex &oldVertex, Vertex &newVertex, bool useTSPEvaluator);
    public:
		static int countSolutions; 
		StorageAllocationSolution();
		StorageAllocationSolution(StorageAllocationSolution *other);
		StorageAllocationSolution(StorageAllocationSolution &other);
		StorageAllocationSolution(double value, double time, double minDelta = 1e-06,bool maximization = true);
		~StorageAllocationSolution();
		static void setEvaluator(const DistanceMatrix<Vertex> *, map<Position , Vertex > &, std::vector<Block> & ,OptimizationConstraints &);
		map<Product, pair<Cell, int> > & getProductAllocations();
		std::set<Product> & getNonAllocatedProducts(); 		 
		double getTotalPenalty(); 
		void setAllocation(const Cell &cell, int level, const Product &product);  
		void setTotalPenalty(const double value); 
		void setAllocation(MapAllocation &allocations,const std::vector<Order> &orders);
		void setRoutesByProduct(std::map<Product, std::vector<PickingRoute * > > &other);
		void setNonAllocatedProducts(const std::set<Product> &nonAllocated);
		void removeAllocation(Product &product);
		void proceedSwap(const Product &firstProduct, const Product &secondProduct,bool evaluateSolutionWithTSP=false);
		void Evaluate(bool evaluateWithTSP = true);
        void printSolution()const override;
        void printToFile(std::ofstream & out) const override;
		StorageAllocationSolution & operator=(const StorageAllocationSolution &other); 
		bool checkSolution();

};
