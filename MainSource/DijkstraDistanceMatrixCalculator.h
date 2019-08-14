#ifndef DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H
#define DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H

#include "DistanceMatrixCalculator.h"
#include<iostream>
#include<vector>
#include<utility>
#include "Vertex.h"
using namespace std;
using namespace QuickTSP;



template<class Graph, class DistanceMatrix>
class DijkstraDistanceMatrixCalculator : DistanceMatrixCalculator<Graph,  DistanceMatrix> {

    public:  
        DijkstraDistanceMatrixCalculator(){}
        DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator &other);
        virtual DistanceMatrix calculateMatrixDistance(Graph &graph, vector<Vertex> &sourceVertexes); 

};

#endif