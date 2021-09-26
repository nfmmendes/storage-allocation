#pragma once

#include<vector>
#include "NeighborhoodStructure.h"
#include "AbstractSolution.h"

class Heuristic {

    protected: 
        AbstractSolution *bestSolution;
        AbstractSolution *currentSolution;
        virtual bool StopCriteriaReached() =0;
        std::vector<NeighborhoodStructure> neighborhoodStructures;
        virtual void EvaluateSolution(AbstractSolution * solution)=0; 
    public: 
        virtual AbstractSolution * Execute() =0;
};
