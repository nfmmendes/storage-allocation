#ifndef ABSTRACT_SOLUTION_H
#define ABSTRACT_SOLUTION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<map>
using namespace std;

class AbstractSolution{

    protected:
        double solutionValue;
        double runtime;
        double minDelta;
        bool isMaximization;

        
    public:
        AbstractSolution(){}
        AbstractSolution(double value, double time, double minDelta = 1e-06,double maximization = true){
            this->solutionValue = value;
            this->runtime = time;
            this->minDelta = minDelta;
            this->isMaximization = maximization; 
        }

        //Data modifiers 
        virtual void setSolutionValue(double value) =0;
        virtual void setRuntime(double time) =0;
        virtual void setMinDelta(double minDelta)  = 0;
        void setIsMaximization(bool isMax) { this->isMaximization = isMax; }

        //Data accessers 
        double getSolutionValue() const { return this->solutionValue; }
        double getRuntime() const  { return this->runtime; }
        double getMinDelta() const { return this->minDekta; }
        double _isMaximization() const { return this->isMaximization; } 

        virtual void printSolution() const = 0;
        virtual void printToFile(const ofstream & out) const =0;

        bool betterThan(const AbstractSolution &other){ 
            if(isMaximization) return this->solutionValue - other.solutionValue > minDelta; 
            else               return other.solutionValue - this->solutionValue > minDelta; 
        }

        bool operator<=(const AbstractSolution &other) const { return this->solutionValue - other.solutionValue <= minDelta; }
        bool equivalent(const AbstractSolution &other) const { 
            return fabs(this->solutionValue - other.solutionValue) <= minDelta; 
        } 

        
};


#endif