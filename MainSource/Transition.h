#ifndef TRANSITION_H
#define TRANSITION_H

#include<iostream>
#include<vector>
#include "Vertex.h"
#include "HananGraph.h"
using namespace std; 

namespace QuickTSP{

    class Transition{
        
        private:
            Vertex beginVertex;
            Vertex endVertex;
            HananGraph graph;

        public:  
            Transition();
            Transition(Transition &transition);
            Transition(Vertex &beginVertex, Vertex& endVertex, HananGraph &graph){
                this->beginVertex = beginVertex;
                this->endVertex = endVertex;
                this->graph = graph; 
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            void setHananGraph(HananGraph &value) { this->graph = value; } 
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; } 
            HananGraph & getGraph() { return this->graph; } 
        
            Transition & operator=(const Transition &other){
                this->beginVertex = other.beginVertex;
                this->endVertex = other.endVertex;
                this->graph = other.graph;
                
                return *this;
            }
    };
    
 }
 
 #endif
