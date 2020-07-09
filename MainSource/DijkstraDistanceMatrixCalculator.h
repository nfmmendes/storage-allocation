#ifndef DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H
#define DIJKSTRA_DISTANCE_MATRIX_CALCULATOR_H


#include<iostream>
#include<vector>
#include<utility>
#include<queue>
#include<functional>
#include<algorithm>
#include<iomanip>
#include<map>
#include<list>
#include<exception>
#include "DistanceMatrix.h"
#include "AbstractVertex.h"
#include "DistanceMatrixCalculator.h"
#include "Arc.h"
#include "Vertex.h"
# define INF 0x3f3f3f3f 
using namespace std;
using namespace QuickTSP; 



template <class Graph, class Vertex>
class DijkstraDistanceMatrixCalculator : public DistanceMatrixCalculator<Graph,  Vertex > {

    public:  
        DijkstraDistanceMatrixCalculator(){}
        DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator &other);
        DistanceMatrix<Vertex> &calculateMatrixDistance(Graph &graph, vector<Vertex> sourceVertexes); 
		DistanceMatrix<Vertex> distanceMatrix; 

};


typedef pair<int, double> iPair; 



/**
 * 
 * 
 */
template <class Graph, class Vertex>
DijkstraDistanceMatrixCalculator<Graph, Vertex>::DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator<Graph,Vertex> &other){
    this = &other;
};

/**
 *  Based on the code presented on https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ 
 *  It is a very efficient implementation that works in O(n log n) for each source point (if there is more than one). 
 */
template <class Graph, class Vertex >
DistanceMatrix<Vertex> &DijkstraDistanceMatrixCalculator< Graph,Vertex>::calculateMatrixDistance(Graph &graph, vector<Vertex> sourceVertexes){

    vector<Vertex> vertexes = graph.getVertexes(); 
	map<Vertex, vector<Arc> > arcs = graph.getArcs();
    map<Vertex, int> indexVertex;
	
    for(unsigned int i= 0; i<vertexes.size(); i++)
		indexVertex[ vertexes[i] ] = i;

	map<pair<Vertex,Vertex> , double> distancePairs; 

    for(unsigned int i= 0; i<sourceVertexes.size(); i++){
        
        // Create a priority queue to store vertices that 
        // are being preprocessed. This is weird syntax in C++. 
        // Refer below link for details of this syntax 
        // https://www.geeksforgeeks.org/implement-min-heap-using-stl/ 
        priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
    
        // Create a vector for distances and initialize all 
        // distances as infinite (INF) 
        vector<int> dist(vertexes.size(), INF); 
    
        // Insert source itself in priority queue and initialize 
        // its distance as 0. 
        int src = indexVertex[(Vertex)sourceVertexes[i]]; 
        pq.push(make_pair(0, src )); 
        dist[src] = 0; 
    
        /* Looping till priority queue becomes empty (or all 
        distances are not finalized) */
        while (!pq.empty()) 
        { 
            // The first vertex in pair is the minimum distance 
            // vertex, extract it from priority queue. 
            // vertex label is stored in second of pair (it 
            // has to be done this way to keep the vertices 
            // sorted distance (distance must be first item 
            // in pair) 
            int u = pq.top().second; 
            pq.pop(); 
    
            // Get the adjacent vertexes of vertex with index u 
			vector<Arc> incidentArcs = arcs[vertexes[u] ];
            list<pair<int, double> > adj;
		
			
            // Get the indexes of the adjacent vertexes
            for(unsigned int j= 0; j<incidentArcs.size(); j++)
                adj.push_back(make_pair( indexVertex[incidentArcs[j].getEndVertex()] , incidentArcs[j].getValue()  ) );


            // 'it' is used to get all adjacent vertices of a vertex 
            for (list< pair<int, double> >::iterator it = adj.begin(); it !=  adj.end(); ++it) { 
                // Get vertex label and weight of current adjacent 
                // of u. 
                int v = (*it).first; 
                int weight = (*it).second; 
				
				//cout<<vertexes[v].getLabel()<<" "<<it->first<<" "<<dist[v]<<" "<<dist[u]<<" "<<weight<<endl;
                //  If there is shorted path to v through u. 
                if (dist[v] > dist[u] + weight) { 
                    // Updating distance of v 
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v)); 
                } 
            } 
        }
		
	//	cout<<setw(20)<<sourceVertexes[i].getLabel()<<"\t"; 
		for(unsigned int j=0;j<sourceVertexes.size();j++){
			distancePairs[make_pair(sourceVertexes[i], sourceVertexes[j])] = dist[indexVertex[sourceVertexes[j] ]]; 
		//	cout<<setw(4)<<dist[indexVertex[sourceVertexes[j] ]]<<" ";
		}
	//	cout<<endl;
		
    }
	
	
	
	return distanceMatrix.buildMatrix(distancePairs); 
}





#endif


