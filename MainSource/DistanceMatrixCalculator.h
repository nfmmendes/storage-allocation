#ifndef DISTANCE_MATRIX_CALCULATOR_H
#define DISTANCE_MATRIX_CALCULATOR_H

#include<iostream>
#include<vector> 
#include<map>
#include<string>
#include<cstdlib>
#include<utility> 
#include "AbstractVertex.h"
using namespace std; 


template <class Graph, class DistanceMatrix>
class DistanceMatrixCalculator{

        
    public:
        DistanceMatrixCalculator();
        DistanceMatrixCalculator(DistanceMatrixCalculator<Graph, DistanceMatrix> &other);
        virtual DistanceMatrix & calculateMatrixDistance(Graph &graph, vector<AbstractVertex> sourceVertexes)=0;
     

}; 


#endif


