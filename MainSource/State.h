#pragma once

#include<iostream>
#include<vector>
#include<map>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Transition.h"

namespace QuickTSP{

    class State {

        private:
            std::map<Vertex,int> vertexParity;
            std::map<Vertex , int> vertexComponent;
            void adjustParity(Vertex &v,bool insertedInArc = true);
            void adjustComponent(Transition &transition);
        
        public: 
            //Data
            State();
            State(std::map<Vertex,int> parity, std::map<Vertex, int> component);
            void addTransition(Transition &t);
    };

}
