#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;



namespace QuickTSP{


    //Class to represent a vertex in a graph
    class Arc{
        
        private:
            string label;
            double value; 
            Vertex &beginVertex;
            Vertex &endVertex; 
        
        public:
            Arc();
            Arc(Arc &arc){
                this->label = arc.getLabel();
                this->value = arc.getValue(); 
                this->beginVertex = arc.getBeginVertex();
                this->endVertex = arc.getEndVertex();
            }
            
            Arc(string label, double value, Vertex &begin, Vertex &end){
                this->label = label;
                this->value = value; 
                this->beginVertex = begin;
                this->endVertex= endVertex;
            }
        
            void setLabel(string label){
                this->label = value;
            }
            
            
            void setValue(double value){
                this->value = value; 
            }
            
            void setBeginVertex(Vertex& vertex){
                this->beginVertex = vertex;
                
            }
            
            void setEndVertex(Vertex& vertex){
                this->endVertex = vertex; 
            }
            
            
            string getLabel() { return label; }
            double getValue() { return value; }
            Vertex getBeginVertex() { return beginVertex; }
            Vertex endVertex() {return endVertex; }
            
            
            
    };
}