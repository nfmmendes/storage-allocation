#ifndef QUICK_TSP_H
#define QUICK_TSP_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Order.h"
using namespace std;

    
namespace QuickTSP{
        class _QuickTSP{
            private: 
                HananGraph graph;
                vector<Order> orders;
                vector<PathUnity> solution;
            public:
                _QuickTSP();
            
                _QuickTSP(const _QuickTSP &other);
            
                _QuickTSP(HananGraph &graph,vector<Order> &orders);
                
                void setHananGraph(HananGraph &graph);
                void setOrders(vector<Order>& orders);
                HananGraph & getHananGraph();
                vector<Order> & getOrders();
                vector<PathUnity> getSolution();
                
                void Run();
        };
}


#endif