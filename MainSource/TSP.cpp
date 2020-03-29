#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "TSP.h"
#include "DistanceMatrix.h"
using namespace std;



TSP::TSP(){
	
	
}

TSP::TSP(DistanceMatrix<Vertex> distanceMatrix){
	this->distanceMatrix = distanceMatrix; 
	this->distanceMatrixSet = true;
	
}

DistanceMatrix<Vertex> TSP::getDistanceMatrix(){
	return distanceMatrix; 
	
}


void TSP::setDistanceMatrix(DistanceMatrix<Vertex> matrix){
	this->distanceMatrix = matrix; 
	this->distanceMatrixSet = true; 
}


pair<double , vector<Vertex> > TSP::bruteForceTSP(const vector<Vertex> points){
	
	vector<Vertex> currentOrder = points; 
	vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
	
	do {
		double sum = 0.0;
		for(unsigned int i=1;i<currentOrder.size(); i++)
			sum += distanceMatrix.getDistance(currentOrder[i-1], currentOrder[i]); 
		
		if(sum < bestCost){
			bestCost = sum; 
			solution= currentOrder; 
		}
	} while ( std::next_permutation(currentOrder.begin(),currentOrder.end()) );
	
	return make_pair(bestCost, solution); 
}

/**
 *	Evaluate the best route based on the closest neighbor algorithm
 *  @param points Vector of vertexes that need to be visited. The first point is the the departure and the last the destination
 *				  The first and last point does not need to be the same
 */
pair<double , vector<Vertex> > TSP::closestNeighborTSP(const vector<Vertex> points){
	
	
	if(points.size() <=3){
		double cost = points.size() >2? distanceMatrix.getDistance(points[0], points[1]) + distanceMatrix.getDistance(points[1], points[2]) :0;
		return make_pair(cost, points);
	}
	
	vector<Vertex> solution;
	set<Vertex> remainingPoints; 
	Vertex previousPoint; 
	double sumCost = 0; 
	
	for(unsigned int i=1; i< remainingPoints.size()-1; i++)
		remainingPoints.insert(points[i]); 
	
	solution.push_back(points[0]);
	previousPoint =  solution[0]; 
	
	while(!remainingPoints.empty()){
		double lowerDistance = 1e100; 
		double distance = 0;
		Vertex bestPoint; 

		for(auto value : remainingPoints){
			distance = distanceMatrix.getDistance(previousPoint, value);
			
			if(distance < lowerDistance){
				lowerDistance = distance;
				bestPoint = value;
			}
		}
		
		sumCost+= lowerDistance; 
		solution.push_back(bestPoint); 
		previousPoint = bestPoint; 
		remainingPoints.erase(remainingPoints.find(bestPoint)); 
	}
	
	sumCost += distanceMatrix.getDistance(previousPoint, points[points.size()-1]);
	
	return make_pair(sumCost, solution); 
}

/**
 *
 */
pair<double , vector<Vertex> > TSP::quickLocalSearchTSP(const vector<Vertex> points){
	
	vector<Vertex> currentOrder = points; 
	vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
	
	return make_pair(bestCost, solution); 
	
}