#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include<fstream>
#include "Vertex.h"
#include "Transition.h"
#include "HananGraph.h"
using namespace std; 



namespace QuickTSP{



    class PathUnity{
        
        private: 
            Vertex beginVertex;
            Vertex endVertex;
            Transition transition;  

        public:
            PathUnity();
            PathUnity(const PathUnity &other);
            PathUnity(Vertex &begin, Vertex &end, Transition &transition){
                this->beginVertex = begin;
                this->endVertex = end;
                this->transition = transition; 
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            void setHananTransition(Transition &value) { this->transition = value; } 
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; } 
            Transition & getTransition() { return this->transition; } 
            
        
    };
}