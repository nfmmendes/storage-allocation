//
//  ILS.hpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#ifndef ILS_h
#define ILS_h

#include "StorageAllocationSolution.h"
#include "StorageAllocationSolution.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "DistanceMatrix.h";
#include "Warehouse.h"
#include "Graph.h"
#include "Vertex.h"
#include "Arc.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
using namespace std; 


class InsideShelfSwap : NeighborhoodStructure{

};

class InsideBlockSwap: NeighborhoodStructure{

};

class MostFrequentSwap : NeighborhoodStructure{

};



class StorageILS : Heuristic{

    private: 
        DistanceMatrix *distanceMatrix; 
        Graph *graph;
        Warehouse *warehouse; 
        vector<NeighborhoodStructure> neighborhoodStructures;
        StorageAllocationSolution * ExecutePertubation(StorageAllocationSolution *);
        virtual void EvaluateSolution(AbstractSolution * solution); 
    public:
        StorageILS();
        StorageILS(StorageILS &other);
        StorageILS(DistanceMatrix *distances, Graph *graph, Warehouse *warehouse);
        virtual AbstractSolution * Execute(); 

};



#endif /* ILS_hpp */
