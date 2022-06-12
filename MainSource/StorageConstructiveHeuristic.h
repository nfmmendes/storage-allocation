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

using ProductAndFrequenceByFamily = std::tuple <std::map<std::string, std::queue<Product> >, std::map<string, int> >;

class StorageConstructiveHeuristic : public Heuristic  {

	private:
		OptimizationConstraints constraints;
		std::map<Position, Vertex > vertexByCell; 
		std::vector<Product> products; 
        const DistanceMatrix<Vertex> *distanceMatrix; 
        Warehouse *warehouse; 
		std::vector<Order> orders; 
		
		//Auxiliary data structures
		std::set<std::string> isolatedFamilies; 
		std::set<std::string> restrictedProducts; 
		std::map<std::string, std::vector<Product> > productsByFamily; 
		std::map<std::string, IsolatedFamily > familyIsolationsByFamilyCode; 
		std::map<std::string, ProductAllocationProhibitions > productAllocationsByProductName; 
		std::map<Vertex, Position > cellByVertex;
		std::map<std::string, vector<Vertex> > vertexByType; 
		std::set<std::string> storageVertexTypes; 
		std::map<std::string, Block> blocksByName; 
		std::map<long int, Shelf> shelvesById; 
		std::unordered_map<Vertex, Vertex> closestStartPoint;
		std::unordered_map<Vertex, Vertex> closestEndPoint; 
		std::vector<std::pair<Product, int> > productsSortedByFrequence;
		std::map<Product, int> frequenceByProduct;
		
		bool StopCriteriaReached();
        void EvaluateSolution(AbstractSolution * solution); 
		std::map<string, std::vector<Vertex> > getVertexesByType();
		std::vector<std::pair<Product,int> > getProductOrderByFrequence();
		std::vector<Vertex> getStoragePoints(); 
		bool isIsolatedFamily(Product &product);
		std::vector<Vertex> getStorageVertexesOrderedByDistance();
		bool hasConstraints(Product &product);
		void InitializeAuxiliaryDataStructures();
		bool isForbiddenStore(Product &product, Vertex &vertex);
		std::vector<Vertex> getStorageVertexes(std::map<string,vector<Vertex> > &vertexByType);
		void InitializeClosestDeliveryPoint();
		std::set<Product> getNotUsedProducts(const std::map<Vertex,Product> allocations); 
		std::set<Cell> getNotUsedCells(const std::map<Vertex,Product> &allocations); 
		std::set<Shelf> getNotUsedShelves(const std::set<Cell> &usedCells);
		std::set<Block> getNotUsedBlocks(const std::set<Shelf> &usedShelves); 
		void allocateStronglyIsolatedFamilies(std::map<Vertex, Product> & allocations);
		double evaluatePenaltiesByNonIsolation(std::map <Product, Position > & allocations);
		double getBetterRouteWithTwoPoints(std::vector<Product> &items, MapAllocation &productAllocation );
		ProductAndFrequenceByFamily getProductAndFrequenceByFamily(std::set<Product> &notUsedProducts); 
		std::vector<std::pair<int, std::string > > orderFamilyByFrequence(const std::map<std::string, int> &frequenceByFamily);
		tuple<int, map<Vertex,Product> > testFamilyAllocation(queue<Product> products, vector<Vertex> &vertexes);
		bool AllocateBestFamily(std::map<Vertex, Product> & allocations, std::vector<Vertex> vertexes, 
				  std::vector<string> familyCodes,  std::map<std::string, std::queue<Product> >  &orderedProductsByFamily);
		std::tuple<set<Cell> , std::set<Shelf> , std::set<Block> > getNonUsedStructures(const std::map<Vertex,Product> &allocations);
		double evaluatePenaltiesByAllocationProhibition(MapAllocation & allocation); 
		void fillFrequenceByProduct();
		void setBestSolution(std::map<Vertex, Product> &cellByVertex);
		double evaluatePenaltyOnLevel(std::vector<string> familyAllocated, std::string isolation);

    public: 
        StorageAllocationSolution * Execute();
		StorageConstructiveHeuristic(std::vector<Product> & prods, Warehouse &wh, const DistanceMatrix<Vertex> *distMatrix,
									 std::map<Position, Vertex> vertexByCell,
									std::vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 