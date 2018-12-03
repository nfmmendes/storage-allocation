#ifndef VERTEX_H
#define VERTEX_H

#include<iostream>
#include<string>
using namespace std;


namespace QuickTSP{

    /// This graphs represents a vertex in a graph. As the vertex can have many
    /// roles the object contains 3 fields that can be used in a free way
    class Vertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            Vertex(){}
            Vertex(const Vertex &other){
                this->label = other.label;
                this->type = other.type;
                this->value = other.value; 
            }
        
            Vertex(string label, string Type, double value = 0){
                this->label = label;
                this->type = Type;
                this->value = value;
            }
       
            void setLabel(string value){ this->label = value; }
            void setType(string value) { this->type = value; }
            void setValue(double value) { this->value = value; }
        
            string getLabel(){ return this->label; }
            string getType(){ return this->type; }
            double getValue() { return this->value; }
        
            bool operator==(const Vertex & other){
                return label == other.label && type == other.type && value == other.value;
            }
            
            bool operator!=(const Vertex & other){
                return label != other.label || type != other.type || value != other.value;
            }
        
            ///This overload allows the use of an object of this class as a key to a map
            bool operator<(const Vertex &other)const{
                return label+type+to_string(value) < other.label+other.type+to_string(other.value);
                
            }
        
    };
    
}

#endif    
