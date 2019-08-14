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
        NeighborhoodStructure();
        NeighborhoodStructure(AbstractSolution *solution);
        virtual void setStartSolution(AbstractSolution *) const = 0;
        virtual AbstractSolution * getStartSolution() const = 0; 
        virtual vector<AbstractSolution *> createNeighbors() =0;    

};

#endif