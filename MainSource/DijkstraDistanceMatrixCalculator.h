#ifndef DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H
#define DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H

#include "DistanceMatrixCalculator.h"
#include<iostream>
#include<vector>
#include<utility>
using namespace std;


template<class DistanceMatrix, class Graph>
class DijkstraDistanceMatrixCalculator : DistanceMatrixCalculator {

    public:  
        DijkstraDistanceMatrixCalculator();
        DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator &other);
        virtual DistanceMatrix calculateMatrixDistance(Graph &graph); 

};

#endif