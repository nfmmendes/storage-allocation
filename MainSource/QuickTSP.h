#include<iostream>
#include<cmath>
#include<ctime>
using namespace std;

    
namespace QuickTSP{
        class QuickTSP{
            private: 
                HananGraph graph;
                vector<PathUnity&> solution
            public:
                QuickTSP();
                QuickTSP(QuickTSP &other);
                QuickTSP(HananGraph &graph); 
                
                void setHananGraph(HananGraph &graph){ this->graph = graph;}
                HananGraph getHananGraph()           { return this->graph; }
                Vector<PathUnity &> getSolution()    {return this->solution; } 
                
                void Run(){
                    
                }
        };
}