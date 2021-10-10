#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <unordered_map>
#include "DistanceMatrix.h"
#include "Vertex.h"
using namespace QuickTSP; 

typedef std::unordered_map<Vertex,Vertex> VertexVertexMap; 

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
		std::pair<double , std::vector<Vertex> > bruteForceTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		std::pair<double , std::vector<Vertex> > closestNeighborTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		std::pair<double , std::vector<Vertex> > quickLocalSearchTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd); 
}; 
