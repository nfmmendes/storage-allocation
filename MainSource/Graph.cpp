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

/// Copy constructor
Graph::Graph(const Graph &graph){
    this->name = graph.name;
	
    for(unsigned int i=0;i<graph.vertexes.size();i++)
		this->vertexes.push_back(Vertex(graph.vertexes[i]));
	
	map<Vertex, vector<Arc> > otherArcs = graph.getArcs(); 
	
    for(map<Vertex, vector<Arc> >::iterator it = otherArcs.begin();it!=otherArcs.end();it++)
        for(unsigned int i=0; i < it->second.size();i++)			
            this->arcsByVertex[it->first].push_back(it->second[i]);
	
}

/// Graph constructor by members
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

/**
 *
 */
map<Vertex, vector<Arc> > Graph::getArcs() const{
    return arcsByVertex;
}

/**
 *
 */
map<string, set<Vertex> > Graph::getVertexesByType(){
	map<string, set<Vertex> > returned; 
	for(unsigned int i=0;i<this->vertexes.size();i++)
		returned[vertexes[i].getType()].insert(vertexes[i]);
	
	return returned; 
}

/**
 *
 */
vector<Vertex> Graph::getVertexes()const {
    return vertexes;
}

/**
 *
 */
string Graph::getName()const{
    return name;
}

/**
 * Set graph arcs 
 * @param arcs New arcs of the graph. Those arcs 
 */
void Graph::setArcs(map<Vertex, vector<Arc> > arcs){
    this->arcsByVertex.clear();
    this->arcsByVertex = arcs;
}

/**
 *	Set the graph vertexes. This procedure replaces all the vertices and remove invalid arcs 
 *	@param other List of the new vertexes 
 */
void Graph::setVertexes(vector<Vertex> other){
    this->vertexes.clear();
    
	map<Vertex, bool> presentVertexes; 
	
	for(map<Vertex, vector<Arc> >::iterator it = this->arcsByVertex.begin(); it!= this->arcsByVertex.end();it++)
		presentVertexes[it->first] = false; 
	
	
    for(unsigned int i=0; i<other.size();i++){
		presentVertexes[other[i]] = true; 
        this->vertexes.push_back(Vertex(other[i]));
	}	
	
	for(map<Vertex, vector<Arc> >::iterator it = this->arcsByVertex.begin(); it!= this->arcsByVertex.end();it++)
		if(presentVertexes[it->first] == false)
			this->arcsByVertex[it->first].clear(); 
}

/**
 * Add one vertex in the graph 
 */
void Graph::addVertex(Vertex &other){
    this->vertexes.push_back(Vertex(other));
}

/**
 * insert one arc in the graph 
 */
void Graph::addArc(Arc &arc){
    
    this->arcsByVertex[arc.getBeginVertex()].push_back(Arc(arc));
}

/**
 *
 */
void Graph::removeVertex(Vertex &other){
    remove(this->vertexes.begin(), this->vertexes.end(), other);
}

/**
 *
 */
void Graph::removeArc(Vertex vertex,Arc & arc){
    remove(this->arcsByVertex[vertex].begin(), this->arcsByVertex[vertex].end(), arc);
}

/**
 *
 */
void Graph::removerVertex(int i){
    if(i >= 0 && i < (int)this->vertexes.size())
        this->vertexes.erase(this->vertexes.begin()+i);
}

/**
 *
 */
void Graph::removeArc(Vertex vertex,int i){
    if(i >= 0 && i < (int)this->arcsByVertex[vertex].size())
        this->arcsByVertex[vertex].erase(this->arcsByVertex[vertex].begin()+i);
}

/**
 * Get all the adjacent vertex of a vertex 
 * @param vertex Vertex to return its adjacences 
 */
vector<Vertex> Graph::getAdjacentVertexes(Vertex & v){
    vector<Vertex> returned; 

    vector<Arc> incidentArcs = this->arcsByVertex[v];

    for(unsigned int i=0; i<incidentArcs.size();i++)
        returned.push_back(incidentArcs[i].getEndVertex());

    return returned; 
}


void Graph::print() const{
	cout<<vertexes.size() <<" vertexes \n";
	for(unsigned int i=0;i<vertexes.size();i++)
		cout<<vertexes[i]<<endl;
	
	for(auto & mapPair : arcsByVertex)
		for(unsigned int i=0;i<mapPair.second.size(); i++)
			cout<<mapPair.second[i]<<endl; 
}

/**
 * 
 * Convert a set of arcs in a graph. The set of arcs
 * 
 */
Graph Graph::convertArcsToGraph(set<Arc> &arcs,string name){

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

