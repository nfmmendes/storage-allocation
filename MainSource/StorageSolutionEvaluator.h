#ifndef STORAGE_SOLUTION_EVALUATOR_H
#define STORAGE_SOLUTION_EVALUATOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
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
using namespace std;
using namespace QuickTSP;

typedef struct pair< vector<Vertex>, double> PickingRoute; 
typedef struct map< Product, pair<Cell,int> > MapAllocation;  
typedef struct pair<Cell, int> Position; 

/// This class is exclusivelly to evaluate the solutions provided by the a heuristic method
/// All kind of evaluation are done in this class and it should be as independent as possible
/// of the heuristic that call it 
class StorageSolutionEvaluator{

	private:
		map<Vertex, map<int, vector<PickingRoute > >  > routesByVertexAndSize; ///< A pool of already calculated routes, divided by 
																			   ///< the presence of a vertex and then by size.  
		map<pair<Cell,int> , Vertex> vertexByCellPosition; 
		DistanceMatrix<Vertex> *distances; 
		OptimizationConstraints optimizationConstraints;	

		//Auxiliary structures
		set<string> weaklyIsolatedFamilies;  
		set<string> stronglyIsolatedFamilies;
		map<Vertex, Vertex> closestStartPoint;
		map<Vertex, Vertex> closestEndPoint;
		map<string, ProductAllocationProhibitions> prohibitionsByProduct; 
		map<long, Shelf> shelfById; 
		map<string, set<long> > shelfIdsSetByBlockName;

		double getBetterRouteWithTwoPoints(vector<Vertex>& vertexes); 
		void InitializeIsolatedFamilies();
		void InitializeClosestDeliveryPoint();

	public:
		StorageSolutionEvaluator(const StorageSolutionEvaluator &sto);
		StorageSolutionEvaluator(DistanceMatrix<Vertex> * distanceMatrix, map<Position, Vertex> &vertexByPosition,  vector<Block> &blocks, const OptimizationConstraints &constraint); 
		double sumDistances(vector<Vertex> &sequence); 
		double DoRouteEvaluation(vector<Vertex> & route);
		double DoRouteEstimation(vector<Vertex> & route);
		double DoFullEvaluationWithTSP(vector<PickingRoute> &vertexesVisits);
		double searchSequenceOnCache(vector<Vertex> &vertexes);
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);
		map<Product, int> getRequestsByProduct(vector<Order> &orders);
		PickingRoute getVertexes(vector<Position> &positions);
		Vertex getVertex(Position &position);
		double evaluatePenaltyDelta(MapAllocation & allocations,const Product &first,const Product &second);
		double evaluatePenaltyDeltaByProhibition(const Product &first, const Cell &firstCell, const Product &second, const Cell &secondCell);
};

#endif