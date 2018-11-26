#include<iostream>
#include "Graph.h"
using namespace std;

Graph::Graph(Graph &graph){
    this->name = graph.name;
    
    for(int i=0;i<graph.vertexes.size();i++)
        this->vertexes.push_back(Vertex(graph.vertexes[i]));
    for(int i=0;i<graph.arcs.size();i++)
        this->arcs.push_back(Arc(graph.arcs[i]));
}

Graph::Graph(vector<Vertex &> vertexes, vector<Arc&> arcs, string name){
    this->name = name;
    
    for(int i=0;i<graph.vertexes.size();i++)
        this->vertexes.push_back(Vertex(vertexes[i]));
    for(int i=0;i<graph.arcs.size();i++)
        this->arcs.push_back(Arc(arcs[i]));
}
