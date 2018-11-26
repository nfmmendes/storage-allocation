#include<iostream>
#incude<string>
using namespace std;


namespace QuickTSP{

    class Vertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            Vertex();
            Vertex(Vertex &other){
                this->label = other.label;
                this->type = other.type;
                this->value = other.value; 
            }
            Vertex(string label, string Type, string value = 0);
       
            void setLabel(string value){ this->label = value; }
            void setType(string value) { this->label = value; }
            void setValue(string value) { this->label = value; } 
        
        
        
    };
    
}
    