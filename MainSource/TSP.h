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
		const DistanceMatrix<Vertex>* distanceMatrix; 
		bool distanceMatrixSet = false; 

	public:
		TSP();
		explicit TSP(const DistanceMatrix<Vertex>* distanceMatrix);
		const DistanceMatrix<Vertex>* getDistanceMatrix() const; 
		void setDistanceMatrix(const DistanceMatrix<Vertex>* matrix);
		TSP(const TSP &other);
		std::pair<double , std::vector<Vertex> > bruteForceTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		std::pair<double , std::vector<Vertex> > closestNeighborTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);
		std::pair<double , std::vector<Vertex> > quickLocalSearchTSP(const std::vector<Vertex> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd); 
}; 
