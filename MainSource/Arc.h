#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
#include "Vertex.h"
using namespace std;



namespace QuickTSP{


    //Class to represent a vertex in a graph
    class Arc{
        
        private:
            string label;
            double value; 
            Vertex beginVertex;
            Vertex endVertex; 
        
        public:
            Arc();
            Arc(const Arc &arc){
                this->label = arc.getLabel();
                this->value = arc.getValue(); 
                this->beginVertex = arc.getBeginVertex();
                this->endVertex = arc.getEndVertex();
            }
            
            Arc(string label, double value, Vertex &begin, Vertex &end){
                this->label = label;
                this->value = value; 
                this->beginVertex = begin;
                this->endVertex= end;
            }
        
            void setLabel(string label){
                this->label = label;
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
            
            
            string getLabel() const { return label; }
            double getValue() const  { return value; }
            Vertex getBeginVertex() const { return beginVertex; }
            Vertex getEndVertex() const  {return endVertex; }
            
            
            
    };
}
