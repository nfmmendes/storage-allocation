#pragma once

#include<iostream>
#include<string>
#include "Vertex.h"
using std::string;
using std::ostream;
using std::endl;

namespace QuickTSP{

    /** 
     * @brief The class <c> Arc </c> holds information about a graph arc. 
     */
    class Arc{
        
        private:
            string label;
            double value; 
            Vertex beginVertex;
            Vertex endVertex;
            bool directed;  
        
        public:
            /**
             * @brief Copy constructor.
             * @param arc Arc to be copied. 
             */
            Arc(const Arc &arc);

            /**
             * @brief Constructor. 
             * @param label Arc label.
             * @param value Arc value.
             * @param begin Arc begin vertex. 
             * @param end Arc end vertex. 
             * @param directed True if the arc is directed, false otherwise (it is an edge).
             */
            Arc(string label, double value, Vertex &begin, Vertex &end, bool directed=true);
        
            /**
             * @brief Get the arc label. 
             * @return The arc label. 
            */
            const string& getLabel() const;

            /**
             * @brief Get the arc value. 
             * @return The arc value. 
            */
            double getValue() const;

            /**
             * @brief Get the arc begin vertex. 
             * @return The arc begin vertex. 
            */
            const Vertex& getBeginVertex() const;

            /**
             * @brief Get the arc end vertex. 
             * @return The arc end vertex.
            */
            const Vertex& getEndVertex() const;

            /**
             * @brief Get if the arc is directed.
             * @return True if the arc is directed, false otherwise.
             */
            bool isDirected() const;
        
            /**
             * @brief Override the assignament operator =. 
             * @param other The object to be copied. 
             * @return A reference to the modified object. 
            */
            Arc& operator=(const Arc & other);

            /**
             * @brief Overload the equality operator ==.
             * @param other The right hand side object. 
             * @return True if the objects are equals. False otherwise. 
            */
            bool operator==(const Arc &other)const;

            /**
             * @brief Overload the operator less than <.
             * @param other The right hand side operator. 
             * @return Bool if the left side object is lower than the right side object. False otherwise. 
            */
            bool operator<(const Arc &other) const;
			
            /**
			 * @brief Overload the ostream operator << to print arc objects.
			 * @param pr The ostream operator. 
			 * @param arc The arc to be print. 
			 * @return A reference to the ostream operator. 
             */
			friend ostream& operator<<(ostream &pr, const Arc & arc){
				pr<<"Arc "<<arc.label <<" value: "<<arc.value<< endl<<arc.beginVertex<<" \n"<<arc.endVertex <<endl;
				return pr;
			}            
    };
}

