#ifndef PATH_UNITY_H
#define PATH_UNITY_H

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
            PathUnity(Vertex &begin, Vertex &end, Transition &transition);
                
            void setBeginVertex(Vertex &value);
            void setEndVertex(Vertex &value);
            void setHananTransition(Transition &value);
                
            Vertex & getBeginVertex();
            Vertex & getEndVertex();
            Transition & getTransition(); 
            
        
    };
}

#endif
