#ifndef HANAN_GRAPH_H
#define HANAN_GRAPH_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include<map>
#include "Graph.h"
#include "Line.h"
#include "Point.h"
#include "Vertex.h"
#include "Transition.h"
using namespace std; 


namespace QuickTSP {

    class HananGraph : Graph{
        
        private:
            vector<Line> lines;
            vector<Line> columns; 
            vector<Point> points; 
            vector<Vertex> buildVertexes;
            map<Vertex, pair<int,int> > vertexCoordinate;
            Graph graph;
            
        public:
            HananGraph();
            HananGraph(const vector<Point >points, Graph & graph);
            
            vector<Vertex> getBuildVertexes();
        
            HananGraph & operator=(const HananGraph &other);
        
            //By now columns and lines will be represented by the same class
            vector<Vertex> getVertexexByLine(Line &line);
            vector<Vertex> getVertexesByColumn(Line &column);
            vector<Arc> getArcstByLine(Line &line);
            vector<Arc> getArcsByColumn(Line &column);
        
            pair<int, int> getVertexCoordinate(Vertex &v);
            bool isFeasibleTransition(Transition &t);
        
    };
}

#endif
