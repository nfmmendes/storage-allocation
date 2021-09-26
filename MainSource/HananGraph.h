#ifndef HANAN_GRAPH_H
#define HANAN_GRAPH_H

#include<iostream>
#include<vector>
#include<utility>
#include<map>
#include "Graph.h"
#include "Line.h"
#include "Point.h"
#include "Vertex.h"
#include "Transition.h"


namespace QuickTSP {

    class HananGraph : Graph{
        
        private:
            std::vector<Line> lines;
            std::vector<Line> columns; 
            std::vector<Point> points; 
            std::vector<Vertex> buildVertexes;
            std::map<Vertex, std::pair<int,int> > vertexCoordinate;
            Graph graph;
            
        public:
            HananGraph();
            HananGraph(const std::vector<Point >points, Graph & graph);
            
            std::vector<Vertex> getBuildVertexes();
        
            HananGraph & operator=(const HananGraph &other);
        
            //By now columns and lines will be represented by the same class
            std::vector<Vertex> getVertexexByLine(Line &line);
            std::vector<Vertex> getVertexesByColumn(Line &column);
            std::vector<Arc> getArcstByLine(Line &line);
            std::vector<Arc> getArcsByColumn(Line &column);
        
            std::pair<int, int> getVertexCoordinate(Vertex &v);
            bool isFeasibleTransition(Transition &t);
        
    };
}

#endif
