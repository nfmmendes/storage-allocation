#pragma once

#include<vector>
#include "AbstractSolution.h"

class NeighborhoodStructure{

    protected:
        AbstractSolution * startSolution;
        
    public:
        NeighborhoodStructure(){ this->startSolution = NULL; }
        virtual ~NeighborhoodStructure(){}
        NeighborhoodStructure(AbstractSolution *solution) { this->startSolution = solution; }
        void setStartSolution(AbstractSolution *solution) {  
            if(this->startSolution != nullptr){
               // delete this->startSolution; 
            }
            this->startSolution = solution; 
        }
        virtual AbstractSolution * getStartSolution() const = 0; 
        virtual std::vector<AbstractSolution *> createNeighbors() =0;    

};
