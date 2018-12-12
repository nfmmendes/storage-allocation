#ifndef ARC_H
#define ARC_H

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
            Arc(const Arc &arc);
                
            Arc(string label, double value, Vertex &begin, Vertex &end);
            
            void setLabel(string label);
                
                
            void setValue(double value);
                
            void setBeginVertex(Vertex& vertex);
            
                
            void setEndVertex(Vertex& vertex);
        
        
            string getLabel() const;
            double getValue() const;
            Vertex getBeginVertex() const;
            Vertex getEndVertex() const;
        
            Arc& operator=(const Arc & other);
            bool operator==(const Arc &other)const;
            
    };
}

#endif
