//
//  ILS.cpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#include "StorageILS.h"
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


/**
 * 
 */
StorageAllocationSolution * StorageILS::ExecutePertubation(StorageAllocationSolution *){

}

/**
 * 
 */
void StorageILS::EvaluateSolution(AbstractSolution * solution){

}

/**
 * 
 */
 StorageILS::StorageILS(){

 }

/**
 * 
 */
StorageILS::StorageILS(StorageILS &other){

}

/**
 * 
 */
StorageILS::StorageILS(DistanceMatrix *distances, Graph *graph, Warehouse *warehouse){

}

/**
 * 
 */
StorageILS::virtual AbstractSolution * Execute(){

}