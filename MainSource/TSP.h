#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Order.h"
using namespace std;

    
namespace QuickTSP{
        class TSP{
            private: 
                HananGraph graph;
                vector<Order> orders;
                vector<PathUnity> solution;
            public:
                TSP();
            
                TSP(TSP &other);
            
                TSP(HananGraph &graph,vector<Order> &orders);
                
                void setHananGraph(HananGraph &graph);
                void setOrders(vector<Order>& orders);
                HananGraph getHananGraph();
                vector<Order> & getOrders();
                vector<PathUnity> getSolution();
                
                void Run();
        };
}
