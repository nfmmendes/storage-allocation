#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<map>
#include<utility>
#include<set>
#include "Arc.h"
#include "Vertex.h"
using namespace std; 

namespace QuickTSP{
    
        class Graph{
            private:
                vector<Vertex> vertexes;					///< List of graph vertexes 
                map<Vertex, vector<Arc> > arcsByVertex;		///< Arcs that are incident on each vertex	
                string name;								///< Graph name 
            public:
                Graph(){}
            
                Graph(const Graph &graph);
            
                Graph(const vector<Vertex> &vertexes, map<Vertex, vector<Arc> > &arc, string name);
            
                Graph &operator=(const Graph &other);
            
                map<Vertex, vector<Arc> > getArcs() const;
				map<string, set<Vertex>> getVertexesByType();
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
                vector<Vertex> getAdjacentVertexes(Vertex & v);
                static Graph convertArcsToGraph(set<Arc> &arcs,string name="");
				void print(); 
        };
    
}

#endif
