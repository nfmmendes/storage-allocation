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
            vector<Vertex> vertexParity;
            map<Vertex , int> vertexComponent; 
            HananGraph graph; 
        
            State();
            State(vector<int> parity, map<Vertex, int> component, HananGraph &graph){
                //this->vertexParity = parity;
                this->vertexComponent = component;
                this->graph = graph; 
            }
            
            void addTransition(Transition &t){
                //Verify the components of state 
            }
            

    };

}

#endif