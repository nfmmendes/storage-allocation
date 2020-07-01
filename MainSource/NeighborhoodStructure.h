#ifndef NEIGHBORHOOD_STRUCTURE_H
#define NEIGHBORHOOD_STRUCTURE_H

#include<iostream>
#include<vector>
#include<string>
#include "AbstractSolution.h"
using namespace std;

class NeighborhoodStructure{

    protected:
        AbstractSolution * startSolution;
        
    public:
        NeighborhoodStructure(){}
        virtual ~NeighborhoodStructure(){}
        NeighborhoodStructure(AbstractSolution *solution) { this->startSolution = solution; }
        void setStartSolution(AbstractSolution *solution) { this->startSolution = solution; }
        virtual AbstractSolution * getStartSolution() const = 0; 
        virtual vector<AbstractSolution *> createNeighbors() =0;    

};

#endif