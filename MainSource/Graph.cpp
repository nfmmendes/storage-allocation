#include<iostream>
#include "Graph.h"
using namespace std;

/// Copy constructor
Graph::Graph(Graph &graph){
    this->name = graph.name;
    
    for(int i=0;i<graph.vertexes.size();i++)
        this->vertexes.push_back(Vertex(graph.vertexes[i]));
    for(int i=0;i<graph.arcs.size();i++)
        this->arcs.push_back(Arc(graph.arcs[i]));
}

/// Graph constructor by members
Graph::Graph(vector<Vertex &> vertexes, vector<Arc&> arcs, string name){
    this->name = name;
    
    for(int i=0;i<graph.vertexes.size();i++)
        this->vertexes.push_back(Vertex(vertexes[i]));
    for(int i=0;i<graph.arcs.size();i++)
        this->arcs.push_back(Arc(arcs[i]));
}


Graph &operator=(const Graph &other){
    Graph returned;
    
    returned.name = graph.name;
    
    for(int i=0;i<graph.vertexes.size();i++)
        returned->vertexes.push_back(Vertex(graph.vertexes[i]));
    for(int i=0;i<graph.arcs.size();i++)
        returned->arcs.push_back(Arc(graph.arcs[i]));
    
    return returned;
}
