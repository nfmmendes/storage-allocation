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
        const AbstractSolution * startSolution {nullptr};

        int randomSeed { 0 };             
        
    public:
        /** 
         * @brief Constructor.
         */
        NeighborhoodStructure(){ }
        
        /**
         * @brief Constructor.
         * @param solution Initial solution.
         * @param seed The algorithm random seed. Default value is zero
         */
        NeighborhoodStructure(AbstractSolution *solution, int seed = 0) { 
            this->startSolution = solution; 
            randomSeed = seed;
        }

        /**
         * @brief Set the initial solution. 
         * @param solution The initial solution.
         */
        void setStartSolution(AbstractSolution *solution) {  
            startSolution = solution; 
        }

        void setRandomSeed(int seed){ 
            randomSeed = seed; srand(this->randomSeed); 
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
        virtual const AbstractSolution * getStartSolution() const = 0; 

        /**
         * @brief Create a list of neighbors from the initial solution. 
         * @return A list of solutions. 
         */
        virtual vector<AbstractSolution *> createNeighbors() =0;    
};
