#ifndef TSP_H
#define TSP_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <map>
#include "DistanceMatrix.h"
#include "Vertex.h"
using namespace std;
using namespace QuickTSP; 


class TSP {

	private:
		DistanceMatrix<Vertex> distanceMatrix; 
		bool distanceMatrixSet = false; 

	public:
		TSP();
		TSP(DistanceMatrix<Vertex> &distanceMatrix);
		DistanceMatrix<Vertex> getDistanceMatrix(); 
		void setDistanceMatrix(DistanceMatrix<Vertex> matrix);
		TSP(const TSP &other);
		pair<double , vector<Vertex> > bruteForceTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart, map<Vertex,Vertex> &bestEnd);
		pair<double , vector<Vertex> > closestNeighborTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart, map<Vertex,Vertex> &bestEnd);
		pair<double , vector<Vertex> > quickLocalSearchTSP(const vector<Vertex> &points, map<Vertex,Vertex> &bestStart, map<Vertex,Vertex> &bestEnd); 
		
	


}; 



#endif