#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include <memory>
#include <unordered_map>
#include "Vertex.h"
using namespace QuickTSP; 
using std::vector;
using std::pair;
using std::shared_ptr;
using std::unordered_map;


template<class T=Vertex> 
class DistanceMatrix; 

typedef unordered_map<Vertex, shared_ptr<Vertex>> VertexVertexMap; 

/**
 * @brief The <c> TSP </c> class that holds data and methods to represent and solve
 * a Travelling Salesman Problem.
 */
class TSP {

	private:
		const DistanceMatrix<Vertex>* distanceMatrix; 
		bool distanceMatrixSet = false; 

	public:
		/**
		 * @brief Constructor.
		 */
		TSP();

		/**
		 * @brief Constructor.
		 * @param distanceMatrix Distance matrix to evaluate the routes. 
		 */
		explicit TSP(const DistanceMatrix<Vertex>* distanceMatrix);
		
		/**
		 * @brief Copy constructor.
		 * @param other The object to be copied. 
		 */
		TSP(const TSP &other);

		/**
		 * @brief Run a brute force TSP algorithm.
		 * @param points The list of points to be visited.
		 * @param bestStart The starting point.
		 * @param bestEnd The ending point.
		 * @return A pair containing the best distance and a the sequence of visits in the optimal solution. 
		 */
		pair<double , vector<shared_ptr<Vertex>> > bruteForceTSP(const vector<shared_ptr<Vertex>> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);

		/**
		 * @brief Run a closest neighborhood algorithm to solve the TSP.
		 * @param points The list of points to be visited.
		 * @param bestStart The starting point.
		 * @param bestEnd The ending point.
		 * @return A pair containing the best distance found and a the sequence of visits in the solution found. 
		 */
		pair<double , vector<shared_ptr<Vertex>> > closestNeighborTSP(const vector<shared_ptr<Vertex>> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd);

		/**
		 * @brief Run a quick local search algorithm to solve the TSP. 
		 * @param points The list of points to be visited.
		 * @param bestStart The starting point.
		 * @param bestEnd The ending point.
		 * @return A pair containing the best distance found and a the sequence of visits in the solution found. 
		 */
		pair<double , vector<shared_ptr<Vertex>> > quickLocalSearchTSP(const vector<shared_ptr<Vertex>> &points, VertexVertexMap &bestStart, VertexVertexMap &bestEnd); 
}; 
