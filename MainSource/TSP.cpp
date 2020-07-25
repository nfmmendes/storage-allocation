#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "TSP.h"
#include "DistanceMatrix.h"
using namespace std;


/**
 * Default constructor
 **/
TSP::TSP(){
	
	
}

/**
 * Copy constructor
 **/
TSP::TSP(DistanceMatrix<Vertex> &distanceMatrix){
	this->distanceMatrix = distanceMatrix; 
	this->distanceMatrixSet = true;
	
}

/**
 *
 **/
DistanceMatrix<Vertex> TSP::getDistanceMatrix(){
	return distanceMatrix; 
	
}

/**
 *
 **/
void TSP::setDistanceMatrix(DistanceMatrix<Vertex> matrix){
	this->distanceMatrix = matrix; 
	this->distanceMatrixSet = true; 
}

/**
 *	Evaluate the best route testing all the possible options
 *  @param points Vector of vertexes that need to be visited. The first point is the the departure and the last the destination
 *				  The first and last point does not need to be the same
 *  @param bestStart Map the closest delivery point for each storage point in the sense delivery point --> storage point
 *  @param bestEnd Map the closest delivery point for each storage point in the sense storage point --> delivery point 
 **/
pair<double,vector<Vertex> > TSP::bruteForceTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart, map<Vertex,Vertex> &bestEnd){
	
	vector<Vertex> currentOrder = points; 
	vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
	int orderSize = currentOrder.size(); 

	do {
		double sum = 0.0;
		for(unsigned int i=1;i<orderSize; i++){
			sum += distanceMatrix.getDistance(currentOrder[i-1], currentOrder[i]); 
			if(sum > bestCost)
				break;
		}
		
		sum += distanceMatrix.getDistance(bestStart[currentOrder[0] ] , currentOrder[0] );
		sum += distanceMatrix.getDistance(currentOrder[orderSize-1] , bestEnd[ currentOrder[orderSize-1] ] );
		
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
 *  @param bestStart Map the closest delivery point for each storage point in the sense delivery point --> storage point
 *  @param bestEnd Map the closest delivery point for each storage point in the sense storage point --> delivery point 
 */
pair<double , vector<Vertex> > TSP::closestNeighborTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart,map<Vertex,Vertex> &bestEnd){
	
	
	vector<Vertex> solution;
	set<Vertex> remainingPoints; 
	Vertex previousPoint; 
	double sumCost = 0; 
	
	double minStartCost = 1e100; 
	int bestVertexToInit = 0; 
	double distance; 
	
	for(unsigned int i=0; i< points.size(); i++){
		distance = distanceMatrix.getDistance(bestStart[points[i] ],  points[i]);
		//find the closest point to a delivery point 
		if(distance < minStartCost){
			minStartCost = distance; 
			bestVertexToInit = i; 
		}
			
		remainingPoints.insert(points[i]); 
	}
	
	
	sumCost = minStartCost; 
	solution.push_back(points[bestVertexToInit]); 
	remainingPoints.erase(points[bestVertexToInit]); 
	
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
	
	sumCost += distanceMatrix.getDistance(previousPoint, bestEnd[previousPoint]);
	
	return make_pair(sumCost, solution); 
}

/**
 *  Return a route with a good cost (without warranty of optimality) for a average size sequence of points 
 **/
pair<double , vector<Vertex> > TSP::quickLocalSearchTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart, map<Vertex,Vertex> &bestEnd){
	 
	//vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
		
	pair<double, vector<Vertex> > currentOrder = closestNeighborTSP(points, bestStart, bestEnd);
	bestCost = currentOrder.first; 
	int orderSize = currentOrder.second.size(); 

	for(unsigned int i=1; i+1< orderSize; i++){
		double costReduction = 0; 
		int changingPoint =0;

		for(unsigned int j=1; j+2<orderSize; j++){
			double oldCost = distanceMatrix.getDistance(currentOrder.second[j-1], currentOrder.second[j]) +
							 distanceMatrix.getDistance(currentOrder.second[j], currentOrder.second[j+1]) +
							 distanceMatrix.getDistance(currentOrder.second[j+1], currentOrder.second[j+2]);
			double newCost = distanceMatrix.getDistance(currentOrder.second[j-1], currentOrder.second[j+1]) +
							 distanceMatrix.getDistance(currentOrder.second[j+1], currentOrder.second[j]) +
							 distanceMatrix.getDistance(currentOrder.second[j], currentOrder.second[j+2]);
			
			if(newCost - oldCost < costReduction){
				costReduction = newCost - oldCost;
				changingPoint = j; 
				break; 
			}
		}

		if(costReduction < 0){
			currentOrder.first -= costReduction;
			auto elem = currentOrder.second[changingPoint+1];
			currentOrder.second[changingPoint+1] = currentOrder.second[changingPoint];
			currentOrder.second[changingPoint] = elem; 
			i--; 
		}  
	}
	
	return currentOrder; 
	
}