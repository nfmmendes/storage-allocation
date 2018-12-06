#ifndef STATE_H
#define STATE_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include<map>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Transition.h"
using namespace std; 



namespace QuickTSP{

    class State {

        public: 
            //Data
            map<Vertex,int> vertexParity;
            map<Vertex , int> vertexComponent; 
            HananGraph graph; 
        
            State();
            State(map<Vertex,int> parity, map<Vertex, int> component, HananGraph &graph);
            void addTransition(Transition &t);
            

    };

}

#endif
