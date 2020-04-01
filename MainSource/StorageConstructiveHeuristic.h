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
#include "ProductAllocationProhibition.h"
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
		
		//Auxiliary data structures
		set<string> isolatedFamilies; 
		set<string> restrictedProducts; 
		map<string, vector<Product> > productsByFamily; 
		map<string, vector<IsolatedFamily> > familyIsolationsByFamilyCode; 
		map<string, ProductAllocationProhibitions > productAllocationsByProductName; 
		map<Vertex, pair<Cell, int> > cellByVertex;
		map<string, vector<Vertex> > vertexByType; 
		set<string> storageVertexTypes; 
		map<string, Block> blocksByName; 
		map<long int, Shelf> shelvesById; 
		map<Vertex, Vertex> closestStartPoint;
		map<Vertex, Vertex> closestEndPoint; 
		
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
		map<string, vector<Vertex> > getVertexesByType();
		vector<pair<Product,int> > getProductOrderByFrequence(); 
		vector<Vertex> getStorageVertexesOrderedByDistance();
		bool hasConstraints(Product &product);
		void InitializeAuxiliaryDataStructures();
		bool isForbiddenStore(Product &product, Vertex &vertex);
		vector<Vertex> getStorageVertexes(map<string,vector<Vertex> > &vertexByType);
    public: 
        StorageAllocationSolution * Execute();
		StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> distMatrix,map<pair<Cell, int>, Vertex> vertexByCell,
										  vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 