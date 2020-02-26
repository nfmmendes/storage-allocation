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
        double solutionValue;		///< Objective function value
        double runtime;				///< Runtime to arrive in this solution  TODO: PUT THIS IN OTHER CLASS
        double minDelta;			///< Min delta to consider this new different of other. It is used to compare and sort the solutions 
        bool isMaximization;		///< Says if the problem is a maximization problem. It is used to order the solutions 

        
    public:
        AbstractSolution(){}
        AbstractSolution(AbstractSolution *other) {
			this->solutionValue = other->solutionValue;
			this->runtime = other->runtime;
			this->minDelta = other->minDelta;
			isMaximization = other->isMaximization; 
		} 
 	    AbstractSolution(double value, double time, double minDelta = 1e-06,bool maximization = true){
            this->solutionValue = value;
            this->runtime = time;
            this->minDelta = minDelta;
            this->isMaximization = maximization; 
        }
		
		
		virtual ~AbstractSolution(){};

        //Data modifiers 
        virtual void setSolutionValue(double value) =0;
        virtual void setRuntime(double time) =0;
        virtual void setMinDelta(double minDelta)  = 0;
        void setIsMaximization(bool isMax) { this->isMaximization = isMax; }

        //Data accessers 
        double getSolutionValue() const { return this->solutionValue; }
        double getRuntime() const  { return this->runtime; }
        double getMinDelta() const { return this->minDelta; }
        double _isMaximization() const { return this->isMaximization; } 

        virtual void printSolution() const = 0;
        virtual void printToFile(ofstream & out) const =0;

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