#pragma once

#include<iostream>
#include<string>
#include<set>
#include<vector>
#include<map>
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

typedef struct std::pair< std::vector<Vertex>, double> PickingRoute; 
typedef struct std::map< Product, std::pair<Cell,int> > MapAllocation;  
typedef struct std::pair<Cell, int> Position; 

/// This class is exclusivelly to evaluate the solutions provided by the a heuristic method
/// All kind of evaluation are done in this class and it should be as independent as possible
/// of the heuristic that call it 
class StorageSolutionEvaluator{

	private:
		std::map<Vertex, std::map<int, std::vector<PickingRoute > >  > routesByVertexAndSize; ///< A pool of already calculated routes, divided by 
															 								   ///< the presence of a vertex and then by size.  
		std::map<std::pair<Cell,int> , Vertex> vertexByCellPosition; 
		DistanceMatrix<Vertex> *distances; 
		OptimizationConstraints optimizationConstraints;	

		//Auxiliary structures
		std::set<std::string> weaklyIsolatedFamilies;  
		std::set<std::string> stronglyIsolatedFamilies;
		std::map<std::string, std::pair<std::string, std::string> > isolationDataByFamilyCode; 			// Isolation level and force by family code 
		std::map<Vertex, Vertex> closestStartPoint;
		std::map<Vertex, Vertex> closestEndPoint;
		std::map<std::string, ProductAllocationProhibitions> prohibitionsByProduct; 
		std::map<long, Shelf> shelfById; 
		std::map<std::string, set<long> > shelfIdsSetByBlockName;

		double getBetterRouteWithTwoPoints(std::vector<Vertex>& vertexes); 
		double getOnePointsBestRouteDistance(Vertex &location);
		void InitializeIsolatedFamilies();
		void InitializeClosestDeliveryPoint();
		double evaluatePenaltyDeltaByProhibition(const Product product, const Cell &firstCell, const Cell &secondCell);
		double evaluatePenaltyDeltaByProhibition(const Product &first, const Cell &firstCell, const Product &second, const Cell &secondCell);
		double evaluatePenaltyDeltaByLevel(std::vector<string> &allocatedFamilies, const Product & first, const Product & second, std::string isolationLevel);
		double evaluatePenaltyOnLevel(std::map<std::string, int> & allocationsByFamilyCode, std::string isolationLevel);

	public:
		StorageSolutionEvaluator(const StorageSolutionEvaluator &sto);
		StorageSolutionEvaluator(DistanceMatrix<Vertex> * distanceMatrix, std::map<Position, Vertex> &vertexByPosition,  std::vector<Block> &blocks, const OptimizationConstraints &constraint); 
		double sumDistances(std::vector<Vertex> &sequence); 
		double DoRouteEvaluation(std::vector<Vertex> & route);
		double DoRouteEstimation(std::vector<Vertex> & route);
		double DoFullEvaluationWithTSP(std::vector<PickingRoute> &vertexesVisits);
		double searchSequenceOnCache(std::vector<Vertex> &vertexes);
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);
		std::map<Product, int> getRequestsByProduct(std::vector<Order> &orders);
		PickingRoute getVertexes(std::vector<Position> &positions);
		Vertex getVertex(Position &position);
		double evaluatePenaltyDelta(MapAllocation & allocations,const Product &first,const Product &second);
};
