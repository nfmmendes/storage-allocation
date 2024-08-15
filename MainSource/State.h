#pragma once

#include<iostream>
#include<vector>
#include<map>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Transition.h"
using std::map;

namespace QuickTSP{

    class State {

        private:
            map<Vertex,int> vertexParity;
            map<Vertex , int> vertexComponent;
            void adjustParity(Vertex &v,bool insertedInArc = true);
            void adjustComponent(Transition &transition);
        
        public: 
            //Data
            State();
            State(map<Vertex,int> parity, map<Vertex, int> component);
            void addTransition(Transition &t);
    };

}
