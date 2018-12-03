#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
using namespace std;

    
namespace QuickTSP{
        class TSP{
            private: 
                HananGraph graph;
                vector<PathUnity> solution;
            public:
                TSP() {
                    
                }
            
                TSP(TSP &other){
                    this->graph = other.graph;
                    
                    for(unsigned int i=0; i< other.solution.size();i++)
                        this->solution.push_back(other.solution[i]);
                }
            
                TSP(HananGraph &graph){
                    this->graph = graph;
                }
                
                void setHananGraph(HananGraph &graph){ this->graph = graph;}
                HananGraph getHananGraph()           { return this->graph; }
                vector<PathUnity> getSolution()    {return this->solution; } 
                
                void Run(){
                    
                }
        };
}
