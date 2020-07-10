#ifndef STORAGE_CONSTRUCTIVE_HEURISTIC
#define STORAGE_CONSTRUCTIVE_HEURISTIC

#include<iostream>
#include<cmath>
#include<set>
#include<iomanip>
#include<vector>
#include<queue>
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
		map<string, IsolatedFamily > familyIsolationsByFamilyCode; 
		map<string, ProductAllocationProhibitions > productAllocationsByProductName; 
		map<Vertex, pair<Cell, int> > cellByVertex;
		map<string, vector<Vertex> > vertexByType; 
		set<string> storageVertexTypes; 
		map<string, Block> blocksByName; 
		map<long int, Shelf> shelvesById; 
		map<Vertex, Vertex> closestStartPoint;
		map<Vertex, Vertex> closestEndPoint; 
		vector<pair< Product , int> > productsSortedByFrequence;
		map<Product, int> frequenceByProduct;
		
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
		map<string, vector<Vertex> > getVertexesByType();
		vector<pair<Product,int> > getProductOrderByFrequence();
		vector<Vertex> getStoragePoints(); 
		bool isIsolatedFamily(Product &product);
		vector<Vertex> getStorageVertexesOrderedByDistance();
		bool hasConstraints(Product &product);
		void InitializeAuxiliaryDataStructures();
		bool isForbiddenStore(Product &product, Vertex &vertex);
		vector<Vertex> getStorageVertexes(map<string,vector<Vertex> > &vertexByType);
		void InitializeClosestDeliveryPoint();
		set<Product> getNotUsedProducts(const map<Vertex,Product> allocations); 
		set<Cell> getNotUsedCells(const map<Vertex,Product> &allocations); 
		set<Shelf> getNotUsedShelves(const set<Cell> &usedCells);
		set<Block> getNotUsedBlocks(const set<Shelf> &usedShelves); 
		void allocateStronglyIsolatedFamilies(map<Vertex, Product> & allocations);
		double getBetterRouteWithTwoPoints(vector<pair<Product, double> > &items, map<Product, pair<Cell,int> > &productAllocation );
		tuple <map<string, queue<Product> >, map<string, int> > getProductAndFrequenceByFamily(set<Product> &notUsedProducts); 
		vector<pair<int, string > > orderFamilyByFrequence(const map<string, int> &frequenceByFamily);
		tuple<int, map<Vertex,Product> > testFamilyAllocation(queue<Product> products, vector<Vertex> &vertexes);
		bool AllocateBestFamily(map<Vertex, Product> & allocations, vector<Vertex> vertexes, 
				  vector<string> familyCodes,  map<string, queue<Product> >  &orderedProductsByFamily);
		tuple<set<Cell> , set<Shelf> , set<Block> > getNonUsedStructures(const map<Vertex,Product> &allocations);
		
    public: 
        StorageAllocationSolution * Execute();
		StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> &distMatrix,map<pair<Cell, int>, Vertex> vertexByCell,
										  vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 