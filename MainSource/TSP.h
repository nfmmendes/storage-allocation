#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Vertex.h"
using namespace QuickTSP; 
using std::vector;
using std::pair;
using std::unordered_map;


template<class T=Vertex> 
class DistanceMatrix; 

typedef unordered_map<Vertex,Vertex> VertexVertexMap; 

class TSP {

	private:
		const DistanceMatrix<Vertex>* distanceMatrix; 
		bool distanceMatrixSet = false; 

	public:
		TSP();
		explicit TSP(const DistanceMatrix<Vertex>* distanceMatrix);
		const DistanceMatrix<Vertex>* getDistanceMatrix() const; 
		void setDistanceMatrix(const DistanceMatrix<Vertex>* matrix);
		TSP(const TSP &other);
		pair<double , vector<Vertex> > bruteForceTSP(const vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		pair<double , vector<Vertex> > closestNeighborTSP(const vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		pair<double , vector<Vertex> > quickLocalSearchTSP(const vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd); 
}; 
