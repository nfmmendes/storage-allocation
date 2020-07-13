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
using namespace std;
using namespace QuickTSP;

typedef struct pair< vector<Vertex>, double> PickingRoute; 

/// This class is exclusivelly to evaluate the solutions provided by the a heuristic method
/// All kind of evaluation are done in this class and it should be as independent as possible
/// of the heuristic that call it 
class StorageSolutionEvaluator{

	private:
		map<Vertex, map<int, vector<PickingRoute > >  > routesByVertexAndSize; ///< A pool of already calculated routes, divided by 
																			   ///< the presence of a vertex and then by size.  
		map<pair<Cell,int> , Vertex> vertexByCellPosition; 
		DistanceMatrix<Vertex> *distances; 
		map<Vertex, Vertex> closestStartPoint;
		map<Vertex, Vertex> closestEndPoint;
		OptimizationConstraints optimizationConstraints;

		double getBetterRouteWithTwoPoints(vector<Vertex>& vertexes);
		void InitializeClosestDeliveryPoint();

	public:
		StorageSolutionEvaluator(const StorageSolutionEvaluator &sto);
		StorageSolutionEvaluator(DistanceMatrix<Vertex> * distanceMatrix,const map<pair<Cell,int> , Vertex > &vertexByPosition,const OptimizationConstraints &constraint); 
		double sumDistances(vector<Vertex> &sequence); 
		double DoRouteEvaluation(vector<Vertex> & route);
		double DoRouteEstimation(vector<Vertex> & route);
		double DoFullEvaluationWithTSP(vector<PickingRoute> &vertexesVisits);
		double searchSequenceOnCache(vector<Vertex> &vertexes);
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);
		map<Product, int> getRequestsByProduct(vector<Order> &orders);
		PickingRoute getVertexes(vector<pair<Cell, int> > &positions);
		Vertex getVertex(pair<Cell, int> &position);
		
};

#endif