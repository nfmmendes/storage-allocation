#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 



namespace QuickTSP{



    class PathUnity{
        
        private: 
            Vertex& beginVertex;
            Vertex& endVertex;
            Transition &Transition;  

        public:
            PathUnity();
            PathUnity(PathUnity &other);
            PathUnity(Vertex &begin, Vertex &end, Transition &transition(){
                this->beginVertex = begin;
                this->endVertex = end;
                this->Transition = transition; 
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            void setHananTransition(Transition &value) { this->Transition = value; } 
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; } 
            HananGraph & getGraph() { return this->Transition; } 
            
        
    };
}