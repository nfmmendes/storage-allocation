#pragma once

#include<iostream>
#include<functional>
#include<string>
#include "AbstractVertex.h"
using std::string;
using std::ostream;
using std::size_t;
using std::hash;

namespace QuickTSP{

    /**
     * @brief Class <c> Vertex </c> represents a vertex in a graph. 
     */
    class Vertex : public AbstractVertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            /**
             * @brief Constructor.
             */
            Vertex();

            /**
             * @brief Copy constructor. 
             * @param other The object to be copied. 
             */
            Vertex(const Vertex &other);

            /**
             * @brief Constructor. 
             * @param label The vertex label.
             * @param Type The vertex type.
             * @param value The vertex value. 
             */
            Vertex(string label, string Type, double value = 0);
        
            /**
             * @brief Set the vertex label. 
             * @param value The new vertex label. 
             */
            void setLabel(string value);

            /**
             * @brief Set the vertex type. 
             * @param value The vertex type.
             */
            void setType(string value);

            /**
             * @brief Set the vertex value. 
             * @param value The vertex value. 
             */
            void setValue(double value);
        
            /**
             * @brief Get the vertex label. 
             * @return The vertex label. 
            */
            string getLabel() const;

            /**
             * @brief Get the vertex type. 
             * @return The vertex type. 
            */
            string getType() const;
            
            /**
             * @brief Get the vertex value. 
             * @return The vertex value. 
            */
            double getValue() const;
        
            /**
             * @brief Override the equality operator ==.
             * @param other The right side operator.
             * @return True if the objects are equal, false otherwise. 
            */
            bool operator==(const Vertex & other) const;
        
            /**
             * @brief Override the inequality operator != 
             * @param other The right side operator.
             * @return True if the objects are not equals, false otherwise. 
            */
            bool operator!=(const Vertex & other);

            /**
			 * @brief Override the assignment operator. 
			 * @param other The right side operator. 
			 * @return A reference to the modified object. 
            */
			Vertex &operator=(const Vertex &other); 
        
            /**
            * @brief Override the less than operator <
            * @param other The right hand side object. 
            * @return True if the left side operator is lower/less than the right side operator. 
            **/
            bool operator<(const Vertex &other)const;

            /**
			 * @brief Override the out stream operator << 
			 * @param pr The stream object. 
			 * @param b The vertex to be print. 
			 * @return Return a reference to the ostream object received as parameter. 
            */
			friend ostream &operator<<(ostream & pr, const Vertex &b){ pr<<b.type<<" label: "<<b.label; return pr;}

            /**
             * @brief Override the function hash value. 
             * @param p The vertex to have its hash value computed. 
             * @return The hash value. 
            */
            size_t hash_value(const Vertex & p);
    };

    // custom hash can be a standalone function object:
    struct VertexHash
    {
        size_t operator()(const Vertex& s) const noexcept
        {
            size_t h1 = hash<string>{}(s.getLabel());
            size_t h2 = hash<string>{}(s.getType());
            size_t h3 = hash<double>{}(s.getValue());
            return h1 ^ (h2 << 1) ^ (h3 >> 2); 
        }
    };
    
    // custom specialization of hash can be injected in namespace std
    
}

namespace std
{
    template<> struct hash<QuickTSP::Vertex>
    {
        size_t operator()(const QuickTSP::Vertex& s) const noexcept
        {
            size_t h1 = hash<string>{}(s.getLabel());
            size_t h2 = hash<string>{}(s.getType());
            size_t h3 = hash<double>{}(s.getValue());
            return h1 ^ (h2 << 1) ^ (h3 >> 2); 
        }
    };
}