#pragma once

#include<iostream>
#include<vector> 
#include "AbstractVertex.h"
#include "DistanceMatrix.h"

template <class Graph, class Vertex>
class DistanceMatrixCalculator{
        
    public:
        DistanceMatrixCalculator(){}
        DistanceMatrixCalculator(DistanceMatrixCalculator<Graph, Vertex > &other);
        virtual DistanceMatrix<Vertex> & calculateMatrixDistance(Graph &graph, std::vector<Vertex> sourceVertexes)=0;
}; 
