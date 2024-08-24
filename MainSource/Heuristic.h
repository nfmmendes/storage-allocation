#pragma once

#include<vector>
#include "NeighborhoodStructure.h"
#include "AbstractSolution.h"
using std::vector;

/**
 * @brief Class <c> Heuristic </c> is an abstract class that holds 
 * the basic information and functions to represent a heuristic algorithm. 
 */
class Heuristic {

    protected: 
        AbstractSolution *bestSolution;     ///< Best solution found by the heuristic. 
        AbstractSolution *currentSolution;  ///< Heuristic current solution. 
        vector<NeighborhoodStructure> neighborhoodStructures; ///< List of the heuristic neighborhood structures
        
        /**
         * @brief Check if the heuristic stop criteria has been reached. 
         * @return True if the stop critearia has been reached. False otherwise. 
         */
        virtual bool StopCriteriaReached() = 0;
        
        /**
         * @brief Evaluate the solution considering the heuristic criteria. 
         * @param solution The solution to be evaluated. 
         */
        virtual void EvaluateSolution(AbstractSolution * solution)=0; 
    public:
        /**
         * @brief Execute the heuristic. 
         * @return Return the solution found by the heuristic. 
         */ 
        virtual AbstractSolution * Execute() =0;
};
