#pragma once

#include<iostream>
#include<vector>
#include<map>
#include<utility>
#include<set>
#include "Arc.h"
#include "Vertex.h" 

namespace QuickTSP{

        /**
         * @brief The class Graph is used to represent a graph using a compact data structure. 
         */
        class Graph{
            private:
                std::vector<Vertex> vertexes;					        ///< List of graph vertexes 
                std::map<Vertex, std::vector<Arc> > arcsByVertex;		///< Arcs that are incident on each vertex	
                std::string name;								        ///< Graph name 
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
                Graph(const std::vector<Vertex> &vertexes, std::map<Vertex, std::vector<Arc> > &arc, std::string name);
            
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
                std::map<Vertex, std::vector<Arc> > getArcs() const;

                /**
				 * @brief Get the graph vertexes grouped by type. 
				 * @return A map containing the arcs indexed by type. 
                 */
				std::map<std::string, std::set<Vertex>> getVertexesByType();

                /**
                 * @brief Get the graph vertexes. 
                 * @return The list of graph vertexes. 
                 */
                std::vector<Vertex> getVertexes() const;

                /**
                 * @brief Get the graph name. 
                 * @return The graph name. 
                 */
                std::string getName() const;
            
                /**
                 * @brief Get the graph arcs.  
                 * @param arcs A map containing the arcs indexed by vertex. 
                 */
                void setArcs(std::map<Vertex , std::vector<Arc> > arcs);

                /**
                 * @brief Set the graph vertexes. 
                 * @param other The list of vertexes. 
                 */
                void setVertexes(std::vector<Vertex> other);

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
                 * @brief Remove a graph vertex. 
                 * @param other The vertex to be removed. 
                 */
                void removeVertex(Vertex &other);

                /**
                 * @brief Remove an arc in the vertex. 
                 * @param vertex The initial arc vertex. 
                 * @param arc The arc to be removed. 
                 */
                void removeArc(Vertex vertex, Arc & arc);

                /**
                 * @brief Remove the vertex with index i. 
                 * @param i The index of the vertex to be removed. 
                 */
                void removerVertex(int i);

                /**
                 * @brief Remove the arc with index i in the list indexed by vertex. 
                 * @param vertex The vertex used as map index. 
                 * @param i The index. 
                 */
                void removeArc(Vertex vertex,int i);

                /**
                 * @brief Get the list of adjacent vertex of a vertex.
                 * @param v The vertex searchead. 
                 * @return A list containing all the adjacent vertexes.
                 */
                std::vector<Vertex> getAdjacentVertexes(Vertex & v);

                /**
                 * @brief Convert a set of arcs in a graph. 
                 * @param arcs The set of arcs. 
                 * @param name The graph name. 
                 * @return Return a graph formed by the arcs in the set. 
                 */
                static Graph convertArcsToGraph(std::set<Arc> &arcs, std::string name="");

                /**
				 * @brief Print graph info. 
                 */
				void print() const; 
        };
}
