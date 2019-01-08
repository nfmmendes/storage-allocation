#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<map>
#include<utility>
#include "Arc.h"
#include "Vertex.h"
using namespace std; 

namespace QuickTSP{
    
        class Graph{
            private:
                vector<Vertex> vertexes;
                map<Vertex, vector<Arc> > arcsByVertex;
                string name;
            public:
                Graph(){}
            
                Graph(const Graph &graph);
            
                Graph(vector<Vertex> vertexes, map<Vertex, vector<Arc> > arc, string name);
            
                Graph &operator=(const Graph &other);
            
                map<Vertex, vector<Arc> > getArcs() const;
                vector<Vertex> getVertexes() const;
                string getName() const;
            
                void setArcs(map<Vertex , vector<Arc> > arcs);
                void setVertexes(vector<Vertex> other);
                void addVertex(Vertex &other);
                void addArc(Arc &arc);
                void removeVertex(Vertex &other);
                void removeArc(Vertex vertex, Arc & arc);
                void removerVertex(int i);
                void removeArc(Vertex vertex,int i);
        };
    
}

#endif
