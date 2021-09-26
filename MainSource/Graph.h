#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<set>
#include "Arc.h"
#include "Vertex.h" 

namespace QuickTSP{
    
        class Graph{
            private:
                std::vector<Vertex> vertexes;					///< List of graph vertexes 
                std::map<Vertex, std::vector<Arc> > arcsByVertex;		///< Arcs that are incident on each vertex	
                std::string name;								///< Graph name 
            public:
                Graph(){}
            
                Graph(const Graph &graph);
            
                Graph(const std::vector<Vertex> &vertexes, std::map<Vertex, std::vector<Arc> > &arc, std::string name);
            
                Graph &operator=(const Graph &other);
            
                std::map<Vertex, std::vector<Arc> > getArcs() const;
				std::map<std::string, std::set<Vertex>> getVertexesByType();
                std::vector<Vertex> getVertexes() const;
                std::string getName() const;
            
                void setArcs(std::map<Vertex , std::vector<Arc> > arcs);
                void setVertexes(std::vector<Vertex> other);
                void addVertex(Vertex &other);
                void addArc(Arc &arc);
                void removeVertex(Vertex &other);
                void removeArc(Vertex vertex, Arc & arc);
                void removerVertex(int i);
                void removeArc(Vertex vertex,int i);
                std::vector<Vertex> getAdjacentVertexes(Vertex & v);
                static Graph convertArcsToGraph(std::set<Arc> &arcs, std::string name="");
				void print(); 
        };
    
}
