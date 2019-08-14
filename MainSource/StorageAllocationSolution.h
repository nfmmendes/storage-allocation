#ifndef STORAGE_ALLOCATION_SOLUTION_H
#define STORAGE_ALLOCATION_SOLUTION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<map>
#include "AbstractSolution.h"
using namespace std;

class StorageAllocationSolution : AbstractSolution{

    protected: 
        virtual void setSolutionValue(double value);
        virtual void setRuntime(double time); 
        virtual void setMinDelta(double minDelta);
    public:

        virtual void printSolution() const;
        virtual void printToFile(const ofstream & out) const;

};

#endif