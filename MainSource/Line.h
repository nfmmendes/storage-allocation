#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include "Point.h"
using namespace std;


namespace QuickTSP{

    ///This class represent a basic line, with a starting point and a slope
    ///in a tridimensional space
    class Line{
        private: 
            Point startPoint;
            Point slope;
            string label; 
            
        public:
            Line();
        
            ///Copy constructor
            Line(const Line &other);
                
                ///Constructor member by member
            Line(string label, Point &pointA, Point &pointB);
                
            Point getSlope() const;
            Point getStartPoint() const;
            string getLabel() const;
            
            void setSlope(Point &value);
            void setStartPoint(Point &value);
            void setLabel(string value);
    };
}
