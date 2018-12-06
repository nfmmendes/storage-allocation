#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Order.h"
#include "TSP.h"
using namespace std;
using namespace QuickTSP;

TSP::TSP() {
    
}

TSP::TSP(TSP &other){
    this->graph = other.graph;
    
    for(unsigned int i=0; i< other.solution.size();i++)
        this->solution.push_back(other.solution[i]);
}

TSP::TSP(HananGraph &graph,vector<Order> &orders){
    this->graph = graph;
    this->orders = orders;
}

void TSP::setHananGraph(HananGraph &graph){ this->graph = graph;}
void TSP::setOrders(vector<Order>& orders){ this->orders = orders;}
HananGraph TSP::getHananGraph() { return this->graph; }
vector<Order> & TSP::getOrders() { return this->orders;}
vector<PathUnity> TSP::getSolution()    {return this->solution; }

void TSP::Run(){
    
}
