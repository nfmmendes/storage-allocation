#pragma once

#include<iostream>
#include<functional>
#include<string>
#include "AbstractVertex.h"


namespace QuickTSP{

    /// This graphs represents a vertex in a graph. As the vertex can have many
    /// roles the object contains 3 fields that can be used in a free way
    class Vertex : public AbstractVertex{
        
        private:
            std::string label;
            std::string type;
            double value;
        
        public:
            Vertex();
            Vertex(const Vertex &other);
        
            Vertex(std::string label, std::string Type, double value = 0);
        
            void setLabel(std::string value);
            void setType(std::string value);
            void setValue(double value);
        
            std::string getLabel() const ;
            std::string getType() const;
            double getValue() const;
        
            bool operator==(const Vertex & other) const;
        
            bool operator!=(const Vertex & other);
			Vertex &operator=(const Vertex &other); 
        
            ///This overload allows the use of an object of this class as a key to a map
            bool operator<(const Vertex &other)const;
			friend std::ostream &operator<<(std::ostream & pr, const Vertex &b){ pr<<b.type<<" label: "<<b.label; return pr;}
            std::size_t hash_value(const Vertex & p);
    };

    // custom hash can be a standalone function object:
    struct VertexHash
    {
        std::size_t operator()(const Vertex& s) const noexcept
        {
            std::size_t h1 = std::hash<std::string>{}(s.getLabel());
            std::size_t h2 = std::hash<std::string>{}(s.getType());
            std::size_t h3 = std::hash<double>{}(s.getValue());
            return h1 ^ (h2 << 1) ^ (h3 >> 2); 
        }
    };
    
    // custom specialization of std::hash can be injected in namespace std
    
}

    namespace std
    {
        template<> struct hash<QuickTSP::Vertex>
        {
            std::size_t operator()(const QuickTSP::Vertex& s) const noexcept
            {
                std::size_t h1 = std::hash<std::string>{}(s.getLabel());
                std::size_t h2 = std::hash<std::string>{}(s.getType());
                std::size_t h3 = std::hash<double>{}(s.getValue());
                return h1 ^ (h2 << 1) ^ (h3 >> 2); 
            }
        };
    }