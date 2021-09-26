#pragma once

#include<iostream>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Order.h"
using namespace std;

    
namespace QuickTSP{
        class _QuickTSP{
            private: 
                HananGraph graph;
                std::vector<Order> orders;
                std::vector<PathUnity> solution;
            public:
                _QuickTSP();
            
                _QuickTSP(const _QuickTSP &other);
            
                _QuickTSP(HananGraph &graph, std::vector<Order> &orders);
                
                void setHananGraph(HananGraph &graph);
                void setOrders(std::vector<Order>& orders);
                HananGraph & getHananGraph();
                std::vector<Order> & getOrders();
                std::vector<PathUnity> getSolution();
                
                void Run();
        };
}
