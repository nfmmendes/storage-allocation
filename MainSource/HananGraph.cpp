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
#include "HananGraph.h"
using namespace std;
using namespace QuickTSP;


HananGraph::HananGraph(){}
HananGraph::HananGraph(const vector<Point >points, Graph & graph){
    for(unsigned int i=0; i<points.size();i++)
        this->points.push_back(Point(points[i]));
    
    this->graph = graph;
    
}

vector<Vertex> HananGraph::getBuildVertexes(){
    return buildVertexes;
}

HananGraph & HananGraph::operator=(const HananGraph &other){
    
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
    this->vertexCoordinate = other.vertexCoordinate;
    
    return *this;
}

//By now columns and lines will be represented by the same class
//vector<Vertex> HananGraph::getVertexexByLine(Line &line){   return this->lines;}
//vector<Vertex> HananGraph::getVertexesByColumn(Line &column){ return this->columns; }
//vector<Arc> HananGraph::getArcstByLine(Line &line){ retu}
//vector<Arc> HananGraph::getArcsByColumn(Line &column);

pair<int, int> HananGraph::getVertexCoordinate(Vertex &v){
    return vertexCoordinate[v];
}

