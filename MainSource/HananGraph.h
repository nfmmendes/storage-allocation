#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Graph.h"
using namespace std; 


namespace QuickTSP {

    class HananGraph : Graph{
        
        private:
            vector<Line &> lines
            vector<Line &> columns; 
            vector<Point &> points; 
            vector<Vertex &> buildVertexes;
            map<Vertex &, pair<int,int> > vertexCoordinate; 
            
        public:
            HananGraph();
            HananGraph(vector<Point &>points, Graph & graph);
            
            vector<Vertex &> getBuildVertexes(){
                return buildVertex;
            }
            
            vector<Vertex &> getVertexCoordinate(Vertex &v){
                return 0; 
            }
            
        
    }
}