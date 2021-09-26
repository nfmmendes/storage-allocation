#pragma once

#include<iostream>
#include<string>
#include "Point.h"
using namespace std;


namespace QuickTSP{

    ///This class represent a basic line, with a starting point and a slope
    ///in a tridimensional space
    class Line{
        private: 
            Point startPoint;
            Point slope;
            std::string label; 
            
        public:
            Line();
        
            ///Copy constructor
            Line(const Line &other);
                
                ///Constructor member by member
            Line(std::string label, Point &pointA, Point &pointB);
                
            Point getSlope() const;
            Point getStartPoint() const;
            std::string getLabel() const;
            
            void setSlope(Point &value);
            void setStartPoint(Point &value);
            void setLabel(std::string value);
    };
}
