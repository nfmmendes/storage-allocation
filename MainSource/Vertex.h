#ifndef VERTEX_H
#define VERTEX_H

#include<iostream>
#include<string>
#include "AbstractVertex.h"
using namespace std;


namespace QuickTSP{

    /// This graphs represents a vertex in a graph. As the vertex can have many
    /// roles the object contains 3 fields that can be used in a free way
    class Vertex : public AbstractVertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            Vertex();
            Vertex(const Vertex &other);
        
            Vertex(string label, string Type, double value = 0);
        
            void setLabel(string value);
            void setType(string value);
            void setValue(double value);
        
            string getLabel() const ;
            string getType();
            double getValue();
        
            bool operator==(const Vertex & other)const;
        
            bool operator!=(const Vertex & other);
			Vertex &operator=(const Vertex &other); 
        
                ///This overload allows the use of an object of this class as a key to a map
            bool operator<(const Vertex &other)const;
			friend ostream &operator<<(ostream & pr, const Vertex &b){ pr<<b.type<<" label: "<<b.label; return pr;}
		
    };
    
}

#endif    
