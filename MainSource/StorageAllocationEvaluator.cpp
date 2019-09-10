#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include<set>
#include<vector>
#include<map>
#include<algorithm>
#include "Vector.h"
#include "Arc.h"
#include "StorageSolutionEvaluator.h"
#include "DistanceMatrix.h"
#include "OptimizationParamters.h"
using namespace std;

/**
 *
 */
StorageSolutionEvaluator(){

}

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluator(StorageSolutionEvaluation &sto){}

/**
 *
 */
StorageSolutionEvaluator::StorageSolutionEvaluation(DistanceMatrix * distanceMatrix){}

/**
 *
 */
StorageSolutionEvaluator & StorageSolutionEvaluator::operator=(const StorageSolutionEvaluator &other){

}

/**
 *
 */
double StorageSolutionEvaluator::DoRouteEvaluation(vector<Vertex> & route){
	
	vector<Vertex> bestRoute = route; 
	vector<Vertex> currentRoute = route; 
	double lowestValue = 1e10; 
	
	if(route.size() <= OptimizationParamters::ALL_PERMUTATIONS_TSP_THRESHOLD){
		while(next_permutation(currentRoute.begin()+1, current.end()-1)){
			double distance = sumDistances(currentRoute); 
			if(lowestValue < distance){
				bestRoute = currentRoute; 
				lowestValue = distance; 
			}
		}
	}else if(route.size()> OptimizationParamters::ALL_PERMUTATIONS_TSP_THRESHOLD && route.size() <= OptimizationParamters::INSERTION_TSP_THRESHOLD){
		
	}else{
		
	}
		
	return lowestValue; 
}

/**
 *
 */ 
double StorageSolutionEvaluator::DoRouteEstimation(vector<Vertex> & solution){
	
}


double StorageSolutionEvaluator::sumDistances(vector<Vertex> &sequence){
	double sum = 0.0;
	int limit = sequence.size() >0 : sequence.size()-1 : 0; 
	
	for(int i=0;i<limit; i++){
		sum += distances->getDistances(sequence[i], sequence[i+1]); 
	}
	
	return sum; 
}
