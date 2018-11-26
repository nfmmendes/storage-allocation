#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 

namespace QuickTSP{
    
        class Graph{
        private:
            vector<Vertex&> vertexes; 
            vector<Arc&> arcs; 
            string name; 
        public:
            Graph();
            
            Graph(Graph &graph);
            
           Graph(vector<Vertex &> vertexes, vector<Arc&> arcs, string name);
            
        };
    
}