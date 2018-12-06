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
#include "Vertex.h"
#include "State.h"
using namespace std;
using namespace QuickTSP;

State::State(){}

State::State(map<Vertex,int> parity, map<Vertex, int> component, HananGraph &graph){
    this->vertexParity = parity;
    this->vertexComponent = component;
    this->graph = graph;
}

void State::addTransition(Transition &t){
    //Verify the components of state
    
}
