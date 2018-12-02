#ifndef VERTEX_H
#define VERTEX_H

#include<iostream>
#include<string>
using namespace std;


namespace QuickTSP{

    class Vertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            Vertex();
            Vertex(const Vertex &other){
                this->label = other.label;
                this->type = other.type;
                this->value = other.value; 
            }
            Vertex(string label, string Type, string value = 0);
       
            void setLabel(string value){ this->label = value; }
            void setType(string value) { this->label = value; }
            void setValue(string value) { this->label = value; } 
        
            bool operator==(const Vertex & other){
                return label == other.label && type == other.type && value == other.value;
            }
            
            bool operator!=(const Vertex & other){
                return label != other.label || type != other.type || value != other.value;
            }
        
            bool operator<(const Vertex &other){
                return label+type+to_string(value) < other.label+other.type+to_string(other.value);
                
            }
        
    };
    
}

#endif    