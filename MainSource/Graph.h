#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Arc.h"
#include "Vertex.h"
using namespace std; 

namespace QuickTSP{
    
        class Graph{
            private:
                vector<Vertex> vertexes;
                vector<Arc> arcs;
                string name;
            public:
                Graph();
            
                Graph(const Graph &graph) {
                    for(unsigned int i=0; i< graph.vertexes.size(); i++)
                        this->vertexes.push_back(Vertex(graph.vertexes[i]));
                    
                    for(unsigned int i=0; i < graph.arcs.size(); i++)
                        this->arcs.push_back(Arc(graph.arcs[i]));
                    
                    this->name = graph.name;
                }
            
               Graph(vector<Vertex > vertexes, vector<Arc> arcs, string name);
            
               Graph &operator=(Graph &other);
        };
    
}
