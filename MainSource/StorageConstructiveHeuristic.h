#ifndef STORAGE_CONSTRUCTIVE_HEURISTIC
#define STORAGE_CONSTRUCTIVE_HEURISTIC

#include<iostream>
#include<cmath>
#include<iomanip>
#include "Product.h"
#include "Warehouse.h"
#include "DistanceMatrix.h"
#include "Order"
#include "OptimizationConstraints.h"
using namespace std;
using namespace QuickTSP; 


class StorageConstructiveHeuristic : public Heuristic  {

	private:
		OptimizationConstraints constraints;
		vector<Product> products; 
        DistanceMatrix<Vertex> *distanceMatrix; 
        Warehouse *warehouse; 
		vector<Order> orders; 
		bool StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> distMatrix,vector<Order> &orders, OptimizationConstraints &cons);
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
    public: 
        AbstractSolution * Execute();
}

#endif 