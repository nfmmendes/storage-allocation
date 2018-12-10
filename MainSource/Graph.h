#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Arc.h"
#include "Vertex.h"
using namespace std; 

namespace QuickTSP{
    
        class Graph{
            private:
                vector<Vertex> vertexes;
                vector<Arc> arcs;
                string name;
            public:
                Graph(){}
            
            Graph(const Graph &graph);
            
               Graph(vector<Vertex > vertexes, vector<Arc> arcs, string name);
            
            Graph &operator=(const Graph &other);
        };
    
}
