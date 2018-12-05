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
                TSP() {
                    
                }
            
                TSP(TSP &other){
                    this->graph = other.graph;
                    
                    for(unsigned int i=0; i< other.solution.size();i++)
                        this->solution.push_back(other.solution[i]);
                }
            
                TSP(HananGraph &graph,vector<Order> &orders){
                    this->graph = graph;
                    this->orders = orders;
                }
                
                void setHananGraph(HananGraph &graph){ this->graph = graph;}
                void setOrders(vector<Order>& orders){ this->orders = orders;}
                HananGraph getHananGraph() { return this->graph; }
                vector<Order> & getOrders() { return this->orders;}
                vector<PathUnity> getSolution()    {return this->solution; }
                
                void Run(){
                    
                }
        };
}
