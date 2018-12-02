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
using namespace std; 


namespace QuickTSP {

    class HananGraph : Graph{
        
        private:
            vector<Line> lines;
            vector<Line> columns; 
            vector<Point> points; 
            vector<Vertex> buildVertexes;
            map<Vertex, pair<int,int> > vertexCoordinate; 
            
        public:
            HananGraph();
            HananGraph(const vector<Point &>points, Graph & graph);
            
            vector<Vertex> getBuildVertexes(){
                return buildVertexes;
            }
            
            /*
            pair<int, int> getVertexCoordinate(Vertex &v){
                return vertexCoordinate[v]; 
            }
            */
        
    };
}

#endif