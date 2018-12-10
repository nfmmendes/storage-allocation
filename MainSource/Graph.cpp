#include<iostream>
#include "Graph.h"
using namespace std;
using namespace QuickTSP;

/// Copy constructor
Graph::Graph(const Graph &graph){
    this->name = graph.name;
    
    for(int i=0;i<(int)graph.vertexes.size();i++)
        this->vertexes.push_back(Vertex(graph.vertexes[i]));
    for(int i=0;i<(int)graph.arcs.size();i++)
        this->arcs.push_back(Arc(graph.arcs[i]));
}

/// Graph constructor by members
Graph::Graph(vector<Vertex> vertexes, vector<Arc> arcs, string name){
    this->name = name;
    
    for(int i=0;i<(int)vertexes.size();i++)
        this->vertexes.push_back(Vertex(vertexes[i]));
    for(int i=0;i<(int)arcs.size();i++)
        this->arcs.push_back(Arc(arcs[i]));
}


Graph & Graph::operator=(const Graph &other){
   
    
    this->name = other.name;
    
    this->vertexes.clear();
    this->arcs.clear();
    
    for(int i=0;i<(int)other.vertexes.size();i++)
        this->vertexes.push_back(Vertex(other.vertexes[i]));
    for(int i=0;i<(int)other.arcs.size();i++)
        this->arcs.push_back(Arc(other.arcs[i]));
    
    return *this;
}
