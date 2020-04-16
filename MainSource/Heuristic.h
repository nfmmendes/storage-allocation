#ifndef HEURISTIC_H
#define HEURISTIC_H

#include<iostream>
#include<vector>
#include<string>
#include "NeighborhoodStructure.h"
#include "AbstractSolution.h"
using namespace std;

class Heuristic {

    protected: 
        AbstractSolution *bestSolution;
        AbstractSolution *currentSolution;
        virtual bool StopCriteriaReached() =0;
        vector<NeighborhoodStructure> neighborhoodStructures;
        virtual void EvaluateSolution(AbstractSolution * solution)=0; 
    public: 
        virtual AbstractSolution * Execute() =0;
};


#endif