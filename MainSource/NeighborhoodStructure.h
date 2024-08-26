#pragma once

#include<vector>
#include "AbstractSolution.h"
#include "OptimizationConstraints.h"

/**
 * @brief Class <c> NeighborhoodStructure </c> is an abstract class used to represent
 * a method to find solutions close to the another solution given in a heuristic method.
 */
class NeighborhoodStructure{

    protected:
        AbstractSolution * startSolution {nullptr};
        
    public:
        /** 
         * @brief Constructor.
         */
        NeighborhoodStructure(){ }

        /**
         * @brief Destructor.
         */
        virtual ~NeighborhoodStructure(){}

        /**
         * @brief Constructor.
         * @param solution Initial solution.
         */
        NeighborhoodStructure(AbstractSolution *solution) { this->startSolution = solution; }

        /**
         * @brief Set the initial solution. 
         * @param solution The initial solution.
         */
        void setStartSolution(AbstractSolution *solution) {  
            this->startSolution = solution; 
        }

        /**
         * @brief Set optimization/neighborhood constraints. 
         * @param cons Optimization/neighborhood constraints. 
         */
        virtual void setOptimizationConstraints(OptimizationConstraints * cons) = 0;

        /**
         * @brief Get the initial solution.
         * @return The initial solution.
         */
        virtual AbstractSolution * getStartSolution() const = 0; 

        /**
         * @brief Create a list of neighbors from the initial solution. 
         * @return A list of solutions. 
         */
        virtual vector<AbstractSolution *> createNeighbors() =0;    
};
