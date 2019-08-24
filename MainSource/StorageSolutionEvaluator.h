#ifndef STORAGE_SOLUTION_EVALUATOR_H
#define STORAGE_SOLUTION_EVALUATOR_H

#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<set>
#include<vector>
#include<map>
#include "Vector.h"
#include "Arc.h"
#include "StorageSolutionSolution.h"
#include "AbstractSolution.h"
#include "DistanceMatrix.h"
using namespace std;


/// This class is exclusivelly to evaluate the solutions provided by the a heuristic method
/// All kind of evaluation are done in this class and it should be as independent as possible
/// of the heuristic that call it 
class StorageSolutionEvaluator(){

	private:
		map<Vertex, map<int, vector<PickingRoute> >  > routesByVertexAndSize; ///< A pool of already calculated routes, divided by 
																			  ///< the presence of a vertex. The key is always the 
																			  ///< first vertex in the sequence.  
		map<pair<Cell,int> , Vertex> vertexByCellPosition; 
		DistanceMatrix *distances; 
		void DoRouteEvaluation(vector<Vertex> & route);
		void DoRouteEstimation(vector<Vertex> & solution);
	public:
		StorageSolutionEvaluator()
		StorageSolutionEvaluator(StorageSolutionEvaluation &sto);
		StorageSolutionEvaluation(DistanceMatrix * distanceMatrix); 
		void DoRouteEvaluation(AbstractSolution * solution);
		void DoRouteEstimation(AbstractSolution * solution);
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);
		
}

#endif