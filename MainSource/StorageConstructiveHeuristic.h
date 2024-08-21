#ifndef STORAGE_CONSTRUCTIVE_HEURISTIC
#define STORAGE_CONSTRUCTIVE_HEURISTIC

#include<iostream>
#include<set>
#include<vector>
#include<queue>
#include<unordered_map>
#include "Product.h"
#include "Heuristic.h"
#include "Vertex.h"
#include "Warehouse.h"
#include "DistanceMatrix.h"
#include "Order.h"
#include "OptimizationConstraints.h" 
#include "StorageSolutionEvaluator.h"
#include "StorageAllocationSolution.h"
#include "ProductAllocationProhibition.h"
using namespace QuickTSP; 
using std::vector;
using std::set;
using std::map;
using std::tuple;
using std::string;

using ProductAndFrequenceByFamily = tuple <map<string, queue<Product> >, map<string, int> >;

class StorageConstructiveHeuristic : public Heuristic  {

	private:
		OptimizationConstraints constraints;
		map<Position, Vertex > vertexByCell; 
		vector<Product> products; 
        const DistanceMatrix<Vertex> *distanceMatrix; 
        Warehouse *warehouse; 
		vector<Order> orders; 
		
		//Auxiliary data structures
		set<string> isolatedFamilies; 
		set<string> restrictedProducts; 
		map<string, vector<Product> > productsByFamily; 
		map<string, IsolatedFamily > familyIsolationsByFamilyCode; 
		map<string, ProductAllocationProhibitions > productAllocationsByProductName; 
		map<Vertex, Position > cellByVertex;
		map<string, vector<Vertex> > vertexByType; 
		set<string> storageVertexTypes; 
		map<string, Block> blocksByName; 
		map<long int, Shelf> shelvesById; 
		unordered_map<Vertex, Vertex> closestStartPoint;
		unordered_map<Vertex, Vertex> closestEndPoint; 
		vector<pair<Product, int> > productsSortedByFrequence;
		map<Product, int> frequenceByProduct;
		
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
		map<string, vector<Vertex> > getVertexesByType();
		vector<pair<Product,int> > getProductOrderByFrequence();
		vector<Vertex> getStoragePoints(); 
		bool isIsolatedFamily(const Product &product);
		vector<Vertex> getStorageVertexesOrderedByDistance();
		bool hasConstraints(const Product &product);
		void InitializeAuxiliaryDataStructures();
		bool isForbiddenStore(const Product &product, const Vertex &vertex);
		vector<Vertex> getStorageVertexes(map<string,vector<Vertex> > &vertexByType);
		void InitializeClosestDeliveryPoint();
		set<Product> getNotUsedProducts(const map<Vertex,Product> allocations); 
		set<Cell> getNotUsedCells(const map<Vertex,Product> &allocations); 
		set<Shelf> getNotUsedShelves(const set<Cell> &usedCells);
		set<Block> getNotUsedBlocks(const set<Shelf> &usedShelves); 
		void allocateStronglyIsolatedFamilies(map<Vertex, Product> & allocations);
		double evaluatePenaltiesByNonIsolation(map <Product, Position > & allocations);
		double getBestRouteWithTwoPoints(const vector<Product> &items, MapAllocation &productAllocation );
		ProductAndFrequenceByFamily getProductAndFrequenceByFamily(const set<Product> &notUsedProducts); 
		vector<pair<int, string > > orderFamilyByFrequence(const map<string, int> &frequenceByFamily);
		tuple<int, map<Vertex,Product> > testFamilyAllocation(queue<Product>& products, const vector<Vertex> &vertexes);
		bool AllocateBestFamily(map<Vertex, Product> & allocations, vector<Vertex>& vertexes, 
				  vector<string> familyCodes,  map<string, queue<Product> >  &orderedProductsByFamily);
		tuple<set<Cell> , set<Shelf> , set<Block> > getNonUsedStructures(const map<Vertex,Product> &allocations);
		double evaluatePenaltiesByAllocationProhibition(MapAllocation & allocation); 
		void fillFrequenceByProduct();
		void setBestSolution(map<Vertex, Product> &cellByVertex);
		double evaluatePenaltyOnLevel(const vector<string>& familyAllocated, const string& isolation);

    public: 
        StorageAllocationSolution * Execute();
		StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh, const DistanceMatrix<Vertex> *distMatrix,
									 map<Position, Vertex>& vertexByCell,
									vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 