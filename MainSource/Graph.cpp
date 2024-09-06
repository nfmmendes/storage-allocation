#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
#include "Graph.h"
#include "Arc.h"
#include "Vertex.h"
#include "AbstractVertex.h"
using namespace std;
using namespace QuickTSP;

Graph::Graph(const Graph &graph){
    this->name = graph.name;
	
    for(unsigned int i=0;i<graph.vertexes.size();i++)
		this->vertexes.push_back(Vertex(graph.vertexes[i]));
	
	auto otherArcs = graph.getArcs(); 
	
    for(map<Vertex, vector<Arc> >::iterator it = otherArcs.begin();it!=otherArcs.end();it++)
        for(unsigned int i=0; i < it->second.size();i++)			
            this->arcsByVertex[it->first].push_back(it->second[i]);
	
}

Graph::Graph(const vector<Vertex> &vertexes, map<Vertex, vector<Arc> > &arcs, string name){
    this->name = name;
    
    for(int i=0; i< (int)vertexes.size();i++)
        this->vertexes.push_back(vertexes[i]);
    
    for(map<Vertex, vector<Arc> >::iterator it = arcs.begin(); it != arcs.end(); it++){
        for(unsigned int i=0; i < it->second.size(); i++){
            this->arcsByVertex[it->first].push_back(it->second[i]);
        }
    }
}

Graph & Graph::operator=(const Graph &other){
   
    this->name = other.name; 
    this->vertexes.clear();
    this->arcsByVertex.clear();
   
    for(unsigned int i=0;i<other.vertexes.size();i++)
        this->vertexes.push_back(Vertex(other.vertexes[i]));
	
    auto otherArcs = other.getArcs();
    for(map<Vertex, vector<Arc> >::iterator it = otherArcs.begin();it!=otherArcs.end();it++)
        for(unsigned int i=0;i <  it->second.size();i++)
            this->arcsByVertex[it->first].push_back(it->second[i]);
    
    return *this;
}

const map<Vertex, vector<Arc> >& Graph::getArcs() const{
    return arcsByVertex;
}

const map<string, set<Vertex> > Graph::getVertexesByType(){
	map<string, set<Vertex> > returned; 
    for(const auto& vertex : vertexes)
		returned[vertex.getType()].insert(vertex);
	return returned; 
}

const vector<Vertex>& Graph::getVertexes() const {
    return vertexes;
}

const string& Graph::getName()const{
    return name;
}

void Graph::print() const{
	cout<<vertexes.size() <<" vertexes \n";
	for(const auto& vertex : vertexes)
		cout<<vertex<<endl;
	
	for(const auto & [key, values] : arcsByVertex)
		for(const auto& arc : values)
			cout<<arc<<endl; 
}

Graph Graph::convertArcsToGraph(const set<Arc> &arcs,const string& name){

    set<Vertex> allVertexes;
    vector<Vertex> vertexesList;
    map<Vertex, vector<Arc> > arcsMap; 

    for(const auto &arc : arcs){
        allVertexes.insert({ arc.getBeginVertex(), arc.getEndVertex()});
        arcsMap[arc.getBeginVertex()].push_back(arc);
    }

    for(const auto& vertex : allVertexes)
        vertexesList.push_back(vertex);

    Graph returned(vertexesList, arcsMap, name);
    return returned;
} 

