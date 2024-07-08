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

namespace QuickTSP {

    State::State(){}

    State::State(map<Vertex,int> parity, map<Vertex, int> component){
        this->vertexParity = parity;
        this->vertexComponent = component;
    }

    //Increases in one the degree of a vertexes in a path
    //Optimal routes have vertexes with even degree (equals to 0 or 2)
    void State::adjustParity(Vertex &v, bool insertedInArc){
        if(insertedInArc) vertexParity[v]++;
        else              vertexParity[v]--;
    }

    void State::adjustComponent(Transition &t){
        Vertex begin = t.getBeginVertex();
        Vertex end = t.getEndVertex();
        
        //If the two vertexes are in the state, or they are in the same component (and the new transition create a cicle)
        //or they are in separate components. In the last case, all the vertexes in the component with higher id will be
        //"moved" to the component with a lower id
        if(vertexComponent.count(begin) && vertexComponent.count(end)){
            int componentBegin = vertexComponent[begin];
            int componentEnd = vertexComponent[end];
            
            int minimo = min(componentBegin, componentEnd);
            int maximo = max(componentBegin, componentEnd);
            
            for(map<Vertex,int>::iterator it = vertexComponent.begin(); it != vertexComponent.end(); it++)
                if(it->second == maximo)
                    it->second = minimo;
        }
        
    }

    void State::addTransition(Transition &t){
        //Verify the components of state
        this->adjustParity(t.getBeginVertex());
        this->adjustParity(t.getEndVertex());
        
    }
}