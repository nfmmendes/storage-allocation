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
using std::shared_ptr;
using std::string;
using std::queue;

using ProductAndFrequenceByFamily = tuple <map<string, queue<Product> >, map<string, int> >;

/**
 * @brief Class <c> StorageConstructiveHeuristic </c> creates a solution to the storage allocation problem
 * using a constructive heuristic.  
 */
class StorageConstructiveHeuristic : public Heuristic  {

	private:
		OptimizationConstraints constraints;
		map<Position, shared_ptr<Vertex> > vertexByCell; 
		vector<Product> products; 
        const DistanceMatrix<Vertex> *distanceMatrix; 
        Warehouse *warehouse; 
		vector<Order> orders; 
		
		//Auxiliary data structures
		set<string> isolatedFamilies; 
		set<string> restrictedProducts; 
		map<string, vector<Product> > productsByFamily; 
		map<string, Product*> productPointerByProductName;
		map<string, IsolatedFamily > familyIsolationsByFamilyCode; 
		map<string, ProductAllocationProhibitions > allocationProhibitionByProductName; 
		map<Vertex, Position > cellByVertex;
		map<string, vector<Vertex> > vertexByType; 
		set<string> storageVertexTypes; 
		map<string, Block> blocksByName; 
		map<long int, Shelf> shelvesById; 
		unordered_map<Vertex, shared_ptr<Vertex>> closestStartPoint;
		unordered_map<Vertex, shared_ptr<Vertex>> closestEndPoint; 
		vector<pair<Product, int> > productsSortedByFrequence;
		map<Product, int> frequenceByProduct;
		
		/**
		 * @brief Get if the heuristic stop criteria has been reached. 
		 * @return True if the stop criteria has been reached, false otherwise. 
		 **/
		bool StopCriteriaReached();

		/**
         * @brief Evaluate a solution.
         * @param solution The solution to be evaluated. 
		 **/
        void EvaluateSolution(AbstractSolution * solution); 

		/**
		 * @brief Get the vertexes on warehouse graph representation grouped by type.
		 * @return A map grouping warehouse vertexes by type. 
		 **/
		map<string, vector<Vertex> > getVertexesByType();

		/**
		 * @brief Get the list of products ordered by frequence, from the most frequent to the less frequent. 
		 * @return A list of pair containing the product and its frequence, ordered by frequence. 
		 **/
		vector<pair<Product,int> > getProductOrderByFrequence();

		/**
		 * @brief Get the list of storage points vertexes in the warehouse graph representation. 
		 * @return The storage points vertexes in the warehouse graph representation. 
		 **/
		vector<shared_ptr<Vertex>> getStoragePoints(); 

		/**
		 * @brief Check if a product belongs to one of the family products that must be isolated inside the warehouse.
		 * @param product Product that will be checked.
		 * @return true if the product belongs to an isolated family, false otherwise.
		 **/
		bool isIsolatedFamily(const Product &product);

		/**
		 * @brief Get the vertexes ordered by distance to an expedition point.
		 * @return A list of vertex ordered from the closest to the farthest from an expedition point.
		 **/
		vector<Vertex> getStorageVertexesOrderedByDistance();

		/**
		 * @brief Get if the product has allocations constraints. 
		 * @param product The product to be checked. 
		 * @return True if the product has allocation constraints, false otherwise. 
		 **/
		bool hasConstraints(const Product &product);

		/**
		 * @brief Initialize data structures needed to run the algorithm. 
		 **/
		void InitializeAuxiliaryDataStructures();

		/**
		 * @brief Analyse if a product can be allocated in a vertex based in the allocations prohibitions.
		 * @param product Product that will be evaluated.
		 * @param vertex Vertex were we are trying to put the product.
		 **/
		bool isForbiddenStore(const Product &product, const Vertex &vertex);

		/**
		 * @brief Get the list of storage vertexes in the warehouse graph representation.
		 * @param vertexByType A map grouping all the vertexes by vertex type. 
		 * @return The list of storage vertexes. 
		 **/
		vector<Vertex> getStorageVertexes(map<string,vector<Vertex> > &vertexByType);

		/**
		 * @brief Initialize the closest delivery point of each storage point in the warehouse. 
		 **/
		void InitializeClosestDeliveryPoint();

		/**
		 * @brief Get the list of non allocated products. 
		 * @param allocations The list of all allocations.
		 * @return A list of non ordered products. 
		 **/
		set<Product> getNotUsedProducts(const map<Vertex,Product> allocations); 

		/**
		 * @brief Get not used cells in an allocation.
		 * @param allocations A map containing the allocation of each product. 
		 * @return A set of non used cells. 
		 **/
		set<Cell> getNotUsedCells(const map<Vertex,Product> &allocations); 

		/**
		 * @brief Get the list of not used shelves in the current allocation. 
		 * @param usedCells All the cells used in the product allocation. 
		 * @return The list of the non used shelves in the current allocation. 
		 **/
		set<Shelf> getNotUsedShelves(const set<Cell> &usedCells);

		/**
		 * @brief The list of non used blocks in the current allocation. 
		 * @param usedShelves All the shelves used in the current product allocation. 
		 * @return Get the list of non used blocks in the current allocation. 
		 **/
		set<Block> getNotUsedBlocks(const set<Shelf> &usedShelves); 

		/**
		 * @brief Perform the allocation of the strongly isolated families. 
		 * @param allocations A map containing the current allocations.
		 **/
		void allocateStronglyIsolatedFamilies(map<Vertex, Product> & allocations);

		/**
		 * @brief Evaluate the total penalty for non respecting isolation constraints. 
		 * @param allocations The product allocations. 
		 * @return The total penalty for non respecting isolation constraints. 
		 **/
		double evaluatePenaltiesByNonIsolation(map <Product, Position > & allocations);

		/**
		 * @brief Get the minimum distance of a route composed of one expedition point on begin, two storage points 
		 * and one expedition point in the end. 
		 * @param items The list of products considered. 
		 * @param productAllocation The product allocation. 
		 * @return The minimum distance of a route composed of one expedition point on begin, two storage points and one
		 * expedition point in the end. 
		 **/
		double getBestRouteWithTwoPoints(const vector<Product> &items, MapAllocation &productAllocation );

		/**
		 * @brief Return the frequence of the not used products and the frequence of their families. 
		 * @param notUsedProducts Set of products that where not allocated yet in the warehouse 
		 * @return Two maps in a tuple, the first is a map with the products ordered by frequence, 
		 * 		   from the most frequent to the last frequent. The second map has the frequence of each family.
		 *	       Both maps have as keys the family name
		 **/
		ProductAndFrequenceByFamily getProductAndFrequenceByFamily(const set<Product> &notUsedProducts); 

		/**
		 * @brief Order families by the frequence of requests of their products.
		 * @param frequenceByFamily The frequence of each family. 
		 * @return A list of pairs containing the family frequence and the product family name.
		 **/
		vector<pair<int, string > > orderFamilyByFrequence(const map<string, int> &frequenceByFamily);

		/**
		 * @brief Test how good can be a family insertion on the remaining warehouse spaces. 
		 * @param products The list of products to be allocated in the family. 
		 * @param vertexes The vertexes available to allocate the products. 
		 * @return A tuple containing the frequence of each product allocated and the possible allocation. 
		 **/
		tuple<int, map<Vertex,Product> > testFamilyAllocation(queue<Product>& products, const vector<shared_ptr<Vertex>> &vertexes);

		/**
		 * @brief Allocate the best family (by frequence) in the remaining warehouse positions. 
		 * @param allocations The current allocations. 
		 * @param vertexes The available vertexes.
		 * @param familyCodes The remaining families. 
		 * @param orderedProductsByFamily A map of ordered products by family. 
		 * @return Return true if a family is allocated. False otherwise. 
		 **/
		bool allocateBestFamily(map<Vertex, Product> & allocations, vector<shared_ptr<Vertex>>& vertexes, 
				  vector<string> familyCodes,  map<string, queue<Product> >  &orderedProductsByFamily);

		/**
		 * @brief Get non used warehouse structures (cells, shelves and blocks) in the given allocation. 
		 * @param allocations The product allocations. 
		 * @return A tuple containing the non used cells, shelves and blocks in the current allocation.  
		 **/
		tuple<set<Cell>, set<Shelf>, set<Block>> getNonUsedStructures(const map<Vertex,Product> &allocations);

		/**
		 * @brief Evaluate the total penalty by allocation prohibition.
		 * @param allocation The warehouse allocations. 
		 * @return Total penalty by allocation prohibition. 
		 **/
		double evaluatePenaltiesByAllocationProhibition(MapAllocation & allocation); 

		/**
		 * @brief Fill map that holds the frequences of each product.
		 **/
		void fillFrequenceByProduct();

		/**
		 * @brief Set the heuristic best solution in the moment.
		 * @param cellByVertex The list of allocations, indexed by warehouse graph vertex. 
		 **/
		void setBestSolution(map<Vertex, Product> &cellByVertex);

		/**
		 * @brief Evaluate the penalty in the given warehouse level. 
		 * @param familyAllocated The family allocated in that level. 
		 * @param isolation The isolation level (block, shelf or cell). 
		 * @return The total penalty. 
		 **/
		double evaluatePenaltyOnLevel(const vector<string>& familyAllocated, const string& isolation);

    public: 

		/**
         * @brief Execute the heuristic.
         * @return A storage allocation problem solution. 
		 **/
        StorageAllocationSolution * Execute();

		/**
		 * @brief Constructor. 
		 * @param prods Products to be allocated. 
		 * @param wh Warehouse in which the products will be allocated. 
		 * @param distMatrix The distance matrix based on warehouse graph representation. 
		 * @param vertexByCell A map from the cells in the warehouse and the vertexes on graph represetntation.
		 * @param orders Product orders
		 * @param cons Optimization constraints. 
		 **/
		StorageConstructiveHeuristic(vector<Product> & prods, Warehouse &wh, const DistanceMatrix<Vertex> *distMatrix,
									 map<Position, shared_ptr<Vertex>>& vertexByCell,
									vector<Order> &orders, OptimizationConstraints &cons);
};

#endif 