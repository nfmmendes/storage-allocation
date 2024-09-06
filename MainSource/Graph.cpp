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
	
	map<Vertex, vector<Arc> > otherArcs = graph.getArcs(); 
	
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
	
    map<Vertex, vector<Arc> > otherArcs = other.getArcs();
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
	for(unsigned int i=0;i<this->vertexes.size();i++)
		returned[vertexes[i].getType()].insert(vertexes[i]);
	
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
	for(unsigned int i=0;i<vertexes.size();i++)
		cout<<vertexes[i]<<endl;
	
	for(auto & mapPair : arcsByVertex)
		for(unsigned int i=0;i<mapPair.second.size(); i++)
			cout<<mapPair.second[i]<<endl; 
}

Graph Graph::convertArcsToGraph(const set<Arc> &arcs,const string& name){

    set<Vertex> allVertexes;
    vector<Vertex> listOfVertexes;
    map<Vertex, vector<Arc> > listOfArcs; 

    for(set<Arc>::iterator it = arcs.begin(); it != arcs.end(); it++){
        allVertexes.insert(it->getBeginVertex());
        allVertexes.insert(it->getEndVertex());
        
        listOfArcs[it->getBeginVertex()].push_back(*it);
    }

    for(set<Vertex>::iterator it=allVertexes.begin(); it!= allVertexes.end(); it++)
        listOfVertexes.push_back(*it);

    Graph returned(listOfVertexes, listOfArcs, name);
    return returned;
} 

