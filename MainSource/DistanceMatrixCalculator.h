#ifndef DISTANCE_MATRIX_CALCULATOR_H
#define DISTANCE_MATRIX_CALCULATOR_H

#include<iostream>
#include<vector> 
#include<map>
#include<string>
#include<cstdlib>
#include<utility> 
#include "AbstractVertex.h"
#include "DistanceMatrix.h"
using namespace std; 


template <class Graph, class Vertex>
class DistanceMatrixCalculator{

        
    public:
        DistanceMatrixCalculator(){}
        DistanceMatrixCalculator(DistanceMatrixCalculator<Graph, Vertex > &other);
        virtual DistanceMatrix<Vertex> & calculateMatrixDistance(Graph &graph, vector<Vertex> sourceVertexes)=0;
     

}; 


#endif


