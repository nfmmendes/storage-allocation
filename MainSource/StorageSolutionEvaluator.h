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
		DistanceMatrix<Vertex> *distances; 
		double DoRouteEvaluation(vector<Vertex> & route);
		double DoRouteEstimation(vector<Vertex> & route);
	public:
		StorageSolutionEvaluator()
		StorageSolutionEvaluator(StorageSolutionEvaluation &sto);
		StorageSolutionEvaluation(DistanceMatrix<Vertex> * distanceMatrix); 
		double sumDistances(vector<Vertex> &sequence); 
		void DoRouteEvaluation(AbstractSolution * solution);
		void DoRouteEstimation(AbstractSolution * solution);
		StorageSolutionEvaluator & operator=(const StorageSolutionEvaluator &other);
		
}

#endif