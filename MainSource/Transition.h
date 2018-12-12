#ifndef TRANSITION_H
#define TRANSITION_H

#include<iostream>
#include<vector>
#include "Vertex.h"
using namespace std; 

namespace QuickTSP{

    class Transition{
        
        private:
            Vertex beginVertex;
            Vertex endVertex;

        public:  
            Transition();
            Transition(Transition &transition);
            Transition(Vertex &beginVertex, Vertex& endVertex){
                this->beginVertex = beginVertex;
                this->endVertex = endVertex;
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; }
        
            Transition & operator=(const Transition &other){
                this->beginVertex = other.beginVertex;
                this->endVertex = other.endVertex;
                
                return *this;
            }
    };
    
 }
 
 #endif
