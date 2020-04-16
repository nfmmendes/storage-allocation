#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include "Cell.h"
#include "Vertex.h"
#include "Arc.h"
#include "DistanceMatrix.h"
#include "OptimizationParameters.h"
#include "StorageSolutionEvaluator.h"
using namespace std;
using namespace QuickTSP;

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(){

}



/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(const StorageSolutionEvaluator &sto){
	this->routesByVertexAndSize = sto.routesByVertexAndSize;
	this->vertexByCellPosition = sto.vertexByCellPosition;
	this->distances = sto.distances;
}

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(DistanceMatrix<Vertex> * distanceMatrix){
	
	this->distances = distanceMatrix;
}

/**
 *
 */
StorageSolutionEvaluator & StorageSolutionEvaluator::operator=(const StorageSolutionEvaluator &other){
	this->routesByVertexAndSize = other.routesByVertexAndSize;
	this->vertexByCellPosition = other.vertexByCellPosition;
	this->distances = other.distances;
	return *this;
}

/**
 *
 */
double StorageSolutionEvaluator::DoRouteEvaluation(vector<Vertex> & route){
	
	vector<Vertex> bestRoute = route; 
	vector<Vertex> currentRoute = route; 
	double lowestValue = 1e10; 
	
	if(route.size() <= OptimizationParameters::ALL_PERMUTATIONS_TSP_THRESHOLD){
		while(next_permutation(currentRoute.begin()+1, currentRoute.end()-1)){
			double distance = sumDistances(currentRoute); 
			if(lowestValue < distance){
				bestRoute = currentRoute; 
				lowestValue = distance; 
			}
		}
	}else if(route.size()> OptimizationParameters::ALL_PERMUTATIONS_TSP_THRESHOLD && route.size() <= OptimizationParameters::INSERTION_TSP_THRESHOLD){
		
	}else{
		
	}
		
	return lowestValue; 
}

/**
 *
 */ 
double StorageSolutionEvaluator::DoRouteEstimation(vector<Vertex> & solution){
	int solutionValue = solution.size();
	cout<<solutionValue<<endl;
	return 0;
}


double StorageSolutionEvaluator::sumDistances(vector<Vertex> &sequence){
	double sum = 0.0;
	int limit = sequence.size() >0 ? sequence.size()-1 : 0; 
	
	for(int i=0;i<limit; i++){
		sum += distances->getDistance(sequence[i], sequence[i+1]); 
	}
	
	return sum; 
}
