#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
using namespace std;

    
namespace QuickTSP{
        class QuickTSP{
            private: 
                HananGraph graph;
                vector<PathUnity> solution;
            public:
                QuickTSP();
                QuickTSP(QuickTSP &other);
                QuickTSP(HananGraph &graph); 
                
                void setHananGraph(HananGraph &graph){ this->graph = graph;}
                HananGraph getHananGraph()           { return this->graph; }
                vector<PathUnity> getSolution()    {return this->solution; } 
                
                void Run(){
                    
                }
        };
}