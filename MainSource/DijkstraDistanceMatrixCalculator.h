#pragma once

#include<iostream>
#include<utility>
#include<queue>
#include<functional>
#include<algorithm>
#include<list>
#include<map>
#include "DistanceMatrix.h"
#include "AbstractVertex.h"
#include "DistanceMatrixCalculator.h"
#include "Arc.h"
#include "Vertex.h"
# define INF 0x3f3f3f3f 
using namespace std;
using namespace QuickTSP; 

/**
 * @brief Template class <c> DistanceMatrixCalculator </c> contains the algorithms and data structures
 *        needed to calculate and store a distance matrix from a subset of vertices of a graph and all
 *        the other vertexes of this graph.
 * @tparam Graph The class used to represent the graph.
 * @tparam Vertex The class used to represent a graph vertex. 
*/ 
template <class Graph, class Vertex>
class DijkstraDistanceMatrixCalculator : public DistanceMatrixCalculator<Graph,  Vertex > {

    public:  
        /**
         * @brief Constructor.
         */
        DijkstraDistanceMatrixCalculator(){}

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
         */
        DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator &other);

        /**
         * @brief Calculate the distance matrix. 
         * @param graph The weighted graph.
         * @param sourceVertexes The list of source vertexes
         * @return A matrix indicating the distance from each source vertex to all other source vertexes. 
         */
        DistanceMatrix<Vertex> &calculateMatrixDistance(Graph &graph, vector<Vertex> sourceVertexes); 

		DistanceMatrix<Vertex> distanceMatrix; 

};


typedef pair<int, double> iPair; 

template <class Graph, class Vertex>
DijkstraDistanceMatrixCalculator<Graph, Vertex>::DijkstraDistanceMatrixCalculator(DijkstraDistanceMatrixCalculator<Graph,Vertex> &other){
    this = &other;
};


template <class Graph, class Vertex >
DistanceMatrix<Vertex> &DijkstraDistanceMatrixCalculator< Graph,Vertex>::calculateMatrixDistance(Graph &graph, vector<Vertex> sourceVertexes){

    //  Based on the code presented on 
    //  https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/ 
    //  It is a very efficient implementation that works in O(n log n) for each source point (if there is more than one). 
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
		
		for(unsigned int j=0;j<sourceVertexes.size();j++){
			distancePairs[make_pair(sourceVertexes[i], sourceVertexes[j])] = dist[indexVertex[sourceVertexes[j] ]]; 
		}	
    }
		
	return distanceMatrix.buildMatrix(distancePairs); 
}
