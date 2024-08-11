#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<set>
#include "Arc.h"
#include "Vertex.h" 
using std::vector;
using std::map;
using std::set;
using std::string;

namespace QuickTSP{

        /**
         * @brief The class Graph is used to represent a graph using a compact data structure. 
         */
        class Graph{
            private:
                vector<Vertex> vertexes;					        ///< List of graph vertexes 
                map<Vertex, vector<Arc> > arcsByVertex;		///< Arcs that are incident on each vertex	
                string name;								        ///< Graph name 
            public:
                /**
                 * @brief Constructor.
                 */
                Graph(){}
            
                /**
                 * @brief Copy constructor. 
                 * @param graph The graph to be copied. 
                 */
                Graph(const Graph &graph);
            
                /**
                 * @brief Constructor. 
                 * @param vertexes Graph vertexes.
                 * @param arc Graph arcs.
                 * @param name Graph name. 
                 */
                Graph(const vector<Vertex> &vertexes, map<Vertex, vector<Arc> > &arc, string name);
            
                /**
                 * @brief Assignment operator override. 
                 * @param other The object to be copied. 
                 * @return A reference to the modified object. 
                 */
                Graph &operator=(const Graph &other);
            
                /**
                 * @brief Get the graph arcs.
                 * @return A map containing the arcs indexed by vertex. 
                 */
                const map<Vertex, vector<Arc> >& getArcs() const;

                /**
				 * @brief Get the graph vertexes grouped by type. 
				 * @return A map containing the arcs indexed by type. 
                 */
				const map<string, set<Vertex>>& getVertexesByType();

                /**
                 * @brief Get the graph vertexes. 
                 * @return The list of graph vertexes. 
                 */
                const vector<Vertex>& getVertexes() const;

                /**
                 * @brief Get the graph name. 
                 * @return The graph name. 
                 */
                const string& getName() const;
            
                /**
                 * @brief Get the graph arcs.  
                 * @param arcs A map containing the arcs indexed by vertex. 
                 */
                void setArcs(map<Vertex , vector<Arc> > arcs);

                /**
                 * @brief Set the graph vertexes. 
                 * @param other The list of vertexes. 
                 */
                void setVertexes(vector<Vertex> other);

                /**
                 * @brief Add a vertex to the graph. 
                 * @param other The vertex to be added. 
                 */
                void addVertex(Vertex &other);

                /**
                 * @brief Add an arc to the graph. 
                 * @param arc The arc to be added. 
                 */
                void addArc(Arc &arc);

                /**
                 * @brief Get the list of adjacent vertex of a vertex.
                 * @param v The vertex searchead. 
                 * @return A list containing all the adjacent vertexes.
                 */
                vector<Vertex> getAdjacentVertexes(Vertex & v);

                /**
                 * @brief Convert a set of arcs in a graph. 
                 * @param arcs The set of arcs. 
                 * @param name The graph name. 
                 * @return Return a graph formed by the arcs in the set. 
                 */
                static Graph convertArcsToGraph(set<Arc> &arcs, string name="");

                /**
				 * @brief Print graph info. 
                 */
				void print() const; 
        };
}
