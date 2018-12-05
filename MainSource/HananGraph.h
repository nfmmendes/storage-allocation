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
            HananGraph(){}
            HananGraph(const vector<Point &>points, Graph & graph);
            
            vector<Vertex> getBuildVertexes(){
                return buildVertexes;
            }
        
            HananGraph & operator=(HananGraph &other){
                
                this->lines.clear();
                for(unsigned int i=0; i< other.lines.size(); i++)
                    this->lines.push_back(Line(other.lines[i]));
                
                this->columns.clear();
                for(unsigned int i=0; i<other.columns.size(); i++)
                    this->columns.push_back(Line(other.columns[i]));
                
                this->points.clear();
                for(unsigned int i=0; i<other.points.size();i++)
                    this->points.push_back(Point(other.points[i]));
                
                this->buildVertexes.clear();
                for(unsigned int i=0; i<other.buildVertexes.size();i++)
                    this->buildVertexes.push_back(Vertex(other.buildVertexes[i]));
                
                this->vertexCoordinate.clear();
                for(map<Vertex, pair<int,int> >::iterator it = other.vertexCoordinate.begin(); it != other.vertexCoordinate.end(); it++)
                    this->vertexCoordinate[it->first] = make_pair(it->second.first, it->second.second);
                
                return *this;
            }
        
            //By now columns and lines will be represented by the same class
            vector<Vertex> getVertexexByLine(Line &line);
            vector<Vertex> getVertexesByColumn(Line &column);
            vector<Arc> getArcstByLine(Line &line);
            vector<Arc> getArcsByColumn(Line &column);
        
            pair<int, int> getVertexCoordinate(Vertex &v){
                return vertexCoordinate[v]; 
            }
        
        
    };
}

#endif
