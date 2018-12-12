#ifndef GRAPH_H
#define GRAPH_H

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
                Graph(){}
            
                Graph(const Graph &graph);
            
                Graph(vector<Vertex > vertexes, vector<Arc> arcs, string name);
            
                Graph &operator=(const Graph &other);
            
                vector<Arc> getArcs();
                vector<Vertex> getVertexes();
                string getName();
            
                void setArcs(vector<Arc> arcs);
                void setVertexes(vector<Vertex> other);
                void addVertex(Vertex &other);
                void addArc(Arc &arc);
                void removeVertex(Vertex &other);
                void removeArc(Arc & arc);
                void removerVertex(int i);
                void removeArc(int i);
        };
    
}

#endif
