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

#endif
