#pragma once

#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<map>
#include<unordered_map>
#include<utility>
#include "Vertex.h"
#include "Arc.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
#include "Cell.h"
#include "Product.h"
#include "Order.h"
#include "OptimizationConstraints.h"
#include "Block.h"
using namespace QuickTSP;
using std::map;
using std::vector;
using std::pair;
using std::unordered_map;

class OptimizationParameters;

typedef struct pair< vector<Vertex>, double> PickingRoute; 
typedef class map< Product, pair<Cell,int> > MapAllocation;  
typedef struct pair<Cell, int> Position; 

/** 
 * @brief This class is exclusivelly to evaluate the solutions provided by the a heuristic method
 * All kind of evaluation are done in this class and it should be as independent as possible
 * of the heuristic that call it. 
 */
class StorageSolutionEvaluator{

	private:
		map<const Vertex, map<int, vector<PickingRoute > >  > routesByVertexAndSize; ///< A pool of already calculated routes, divided by 
															 								   ///< the presence of a vertex and then by size.  
		map<pair<Cell,int> , Vertex> vertexByCellPosition; 
		const DistanceMatrix<Vertex> *distances; 
		OptimizationConstraints optimizationConstraints;	

		//Auxiliary structures
		set<string> weaklyIsolatedFamilies;  
		set<string> stronglyIsolatedFamilies;
		map<string, pair<string, string> > isolationDataByFamilyCode; 			// Isolation level and force by family code 
		unordered_map<Vertex, Vertex> closestStartPoint;
		unordered_map<Vertex, Vertex> closestEndPoint;
		map<string, ProductAllocationProhibitions> prohibitionsByProduct; 
		map<long, Shelf> shelfById; 
		map<string, set<long> > shelfIdsSetByBlockName;

		/**
		 * @brief Get the best of a route containing two product locations and initial/final expedition points.
		 * @param vertexes The list of vertexes (pair). 
		 * @return The minimal distance. 
		 */
		double getBetterRouteWithTwoPoints(const vector<Vertex>& vertexes); 

		/** 
		 * @brief Get the minimum distance in a route containing only an initial expedition point, a product 
		 * location and a final product location.
		 * @param location The product location. 
		 * @return The minimum distance in the route closest expedition point -> location -> expedition point. 
		 */
		double getOnePointsBestRouteDistance(const Vertex &location);
		
		/**
		 * @brief Initialize the data structures needed to handle the isolated families.
		 */
		void InitializeIsolatedFamilies();

		/**
		 * @brief Initialize the data structures needed to handle the warehouse delivery points.
		 */
		void InitializeClosestDeliveryPoint();

		/**
		 * @brief Evaluate the prohibition penalty delta (after - before) product be moved to
 		 * another cell.
		 * @param product The product to be analyzed 
		 * @param firstCell The old/first cell. 
		 * @param secondCell The new/second cell.  
		 * @return The total prohibition penalty delta caused by prohibitions. 
		 */
		double evaluatePenaltyDeltaByProhibition(const Product product, const Cell &firstCell, const Cell &secondCell);
		
		/**
		 * @brief Evaluate the penalty delta caused by a swap between two products. In
	     * this function is supposed a valid swap, so strongly isolated families or strong
		 * allocation prohibitions will cause a exception.
		 * @param first The first product.
		 * @param firstCell The first product cell. 
		 * @param second The second product. 
		 * @param secondCell The second product cell. 
		 * @return The delta on the value of prohibition penalty. 
		 */
		double evaluatePenaltyDeltaByProhibition(const Product &first, const Cell &firstCell, const Product &second, const Cell &secondCell);
		
		/**
		 * @brief Evaluate the penalties by isolation level.
		 * @param allocatedFamilies The allocated families on the level. 
		 * @param first The current product. 
		 * @param second The new product. 
		 * @param isolationLevel The isolation level. 
		 * @return The delta on the value of isolation penalty.
		 */
		double evaluatePenaltyDeltaByLevel(const vector<string> &allocatedFamilies, const Product & first, const Product & second, string isolationLevel);
		
		/**
		 * @brief Evaluate the penalties over the allocation of a product family with isolation contraints in a given isolation level.
		 * @param allocationsByFamilyCode The product family code. 
		 * @param isolationLevel The isolation level. 
		 * @return The total penalty over the allocation of product family considering the given isolation level. 
		 */
		double evaluatePenaltyOnLevel(map<string, int> & allocationsByFamilyCode, string isolationLevel);

	public:
		/**
		 * @brief Copy constructor. 
		 * @param sto Object to be copied. 
		 */
		StorageSolutionEvaluator(const StorageSolutionEvaluator &sto);

		/**
		 * @brief Constructor.
		 * @param distanceMatrix The graph distance matrix. 
		 * @param vertexByPosition Graph vertex by warehouse position. 
		 * @param blocks Warehouse blocks. 
		 * @param constraints Allocation constraints. 
		 */
		StorageSolutionEvaluator(const DistanceMatrix<Vertex> * distanceMatrix, map<Position, Vertex> &vertexByPosition, const vector<Block> &blocks, const OptimizationConstraints &constraints); 

		/**
		 * @brief Get the total distance between a sequence of vertexes. 
		 * @param sequence The sequence of vertexes. 
		 * @return The total distance between a sequence of vertexes. 
		 */
		double sumDistances(const vector<Vertex> &sequence); 

		/**
		 * @brief Execute a route evaluation. 
		 * @param route The list of vertexes to be visited in the route. 
		 * @return The best route length found. 
		 */
		double DoRouteEvaluation(const vector<Vertex> & route);

		/**
		 * @brief Estimate the route distance.
		 * @param route The route to be estimated. 
		 * @return The distance route estimation. 
		 */
		double DoRouteEstimation(const vector<Vertex> & route);

		/**
		 * @brief Evaluate the route distance solving a TSP.
		 * @param vertexesVisits The vertexes that need to be visited. 
		 * @return The route distance. 
		 */
		double DoFullEvaluationWithTSP(vector<PickingRoute> &vertexesVisits);

		/**
		 * @brief Search a cached route distance passing by a list of vertexes.
		 * @param vertexes The sequence of vertexes to be searched.
		 * @return The distance, if the vertex sequence is found or -1 otherwise. 
		 */
		double searchSequenceOnCache(vector<Vertex> &vertexes);

		/**
		 * @brief Assignment operator override. 
		 * @param other The object to be copied. 
		 * @return A reference to the modified object. 
		 */
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);

		/**
		 * @brief Get how many times each product is required in a list of orders. 
		 * @param orders The list of orders. 
		 * @return A map containing the number of requests indexed by product. 
		 */
		const map<Product, int> getRequestsByProduct(const vector<Order> &orders);

		/**
		 * @brief Get the graph vertexes corresponding to warehouse positions.
		 * @param positions The warehouse positions. 
		 * @return The list of vertexes, in the same order of the positions. 
		 */
		PickingRoute getVertexes(const vector<Position> &positions);

		/**
		 * @brief Get the graph vertex corresponding to a warehouse position. 
		 * @param position The warehouse position.
		 * @return The graph vertex. 
		 */
		const Vertex& getVertex(const Position &position);

		/**
		 * @brief Evaluate the penalty variation on swapping the position of two products. 
		 * @param allocations The allocation of all products. 
		 * @param first The first product in the swap. 
		 * @param second The second product in the swap. 
		 * @return The total delta. 
		 */
		double evaluatePenaltyDelta(MapAllocation & allocations,const Product &first,const Product &second);
};
