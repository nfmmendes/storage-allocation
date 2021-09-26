#pragma once

#include<iostream>
#include "Vertex.h"
#include "Transition.h"
#include "HananGraph.h"

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
