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

TSP(DistanceMatrix<Vertex> distanceMatrix){
	
	
}


DistanceMatrix<Vertex> TSP::getDistanceMatrix() const{
	
	
}


void TSP::setDistanceMatrix(DistanceMatrix<Vertex> matrix){
	
	
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


pair<double , vector<Vertex> > TSP::closestNeighborTSP(const vector<Vertex> points){
	
	vector<Vertex> currentOrder = points; 
	vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
	
	return make_pair(bestCost, solution); 
}

pair<double , vector<Vertex> > TSP::quickLocalSearchTSP(const vector<Vertex> points){
	
	vector<Vertex> currentOrder = points; 
	vector<Vertex> solution = points;
	double bestCost = std::numeric_limits<double>::max(); 
	
	return make_pair(bestCost, solution); 
	
}