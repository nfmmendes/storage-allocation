#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "HananGraph.h"
#include "PathUnity.h"
#include "Order.h"
#include "QuickTSP.h"
using namespace std;
using namespace QuickTSP; 

_QuickTSP::_QuickTSP() {
    
}

_QuickTSP::_QuickTSP(const _QuickTSP &other){
    this->graph = other.graph;
    
    for(unsigned int i=0; i< other.solution.size();i++)
        this->solution.push_back(other.solution[i]);
}

_QuickTSP::_QuickTSP(HananGraph &graph,vector<Order> &orders){
    this->graph = graph;
    this->orders = orders;
}

void _QuickTSP::setHananGraph(HananGraph &graph){ this->graph = graph;}
void _QuickTSP::setOrders(vector<Order>& orders){ this->orders = orders;}
HananGraph & _QuickTSP::getHananGraph() { return this->graph; }
vector<Order> & _QuickTSP::getOrders() { return this->orders;}
vector<PathUnity> _QuickTSP::getSolution()    {return this->solution; }

void _QuickTSP::Run(){
    
}
