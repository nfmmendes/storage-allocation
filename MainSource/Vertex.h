#pragma once

#include<iostream>
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
        
            bool operator==(const Vertex & other)const;
        
            bool operator!=(const Vertex & other);
			Vertex &operator=(const Vertex &other); 
        
            ///This overload allows the use of an object of this class as a key to a map
            bool operator<(const Vertex &other)const;
			friend std::ostream &operator<<(std::ostream & pr, const Vertex &b){ pr<<b.type<<" label: "<<b.label; return pr;}
		
    };
    
}
