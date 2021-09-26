#pragma once

#include<iostream>
#include<string>
#include "Vertex.h"

namespace QuickTSP{


    //Class to represent a vertex in a graph
    class Arc{
        
        private:
            std::string label;
            double value; 
            Vertex beginVertex;
            Vertex endVertex;
            bool directed;  
        
        public:
            Arc();
            Arc(const Arc &arc);
                
            Arc(std::string label, double value, Vertex &begin, Vertex &end, bool directed=true);
            
            void setLabel(std::string label);
                
                
            void setValue(double value);
                
            void setBeginVertex(Vertex& vertex);
            
                
            void setEndVertex(Vertex& vertex);
        
        
            std::string getLabel() const;
            double getValue() const;
            Vertex getBeginVertex() const;
            Vertex getEndVertex() const;
        
            Arc& operator=(const Arc & other);
            bool operator==(const Arc &other)const;
            bool operator<(const Arc &other) const;
			
			friend std::ostream& operator<<(std::ostream &pr, const Arc & a){
				pr<<"Arc "<<a.label <<" value: "<<a.value<< std::endl<<a.beginVertex<<" \n"<<a.endVertex <<std::endl;
				return pr;
			}
            
    };
}

