#ifndef STORAGE_CONSTRUCTIVE_HEURISTIC
#define STORAGE_CONSTRUCTIVE_HEURISTIC

#include<iostream>
#include<cmath>
#include<set>
#include<iomanip>
#include<vector>
#include "Product.h"
#include "Heuristic.h"
#include "Vertex.h"
#include "Warehouse.h"
#include "DistanceMatrix.h"
#include "Order.h"
#include "OptimizationConstraints.h"
#include "StorageAllocationSolution.h"
using namespace std;
using namespace QuickTSP; 


class StorageConstructiveHeuristic : public Heuristic  {

	private:
		OptimizationConstraints constraints;
		map<pair<Cell,int> , Vertex > vertexByCell; 
		vector<Product> products; 
        DistanceMatrix<Vertex> *distanceMatrix; 
        Warehouse *warehouse; 
		vector<Order> orders; 
		set<string> restrictedFamilies; 
		set<string> restrictedProducts; 
		map<string, vector<Vertex> > vertexByType; 
		
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
		map<string, vector<Vertex> > getVertexesByType();
		vector<pair<Product,int> > getProductOrderByFrequence(); 
		vector<Vertex> getStorageVertexesOrderedByDistance();
		bool hasConstraints(Product &product);
		void InitializeAuxiliaryDataStructures();
		bool isNotForbiddenStore(Product &product, Vertex &vertex);
    public: 
        StorageAllocationSolution * Execute();
		StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> distMatrix,map<pair<Cell, int>, Vertex> vertexByCell,
										  vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 