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
            Line(const Line &other){
                this->startPoint = Point(other.getStartPoint());
                this->slope = Point(other.getSlope());
            }
            
            ///Constructor member by member
            Line(string label, Point &pointA, Point &pointB){
                string pointLabel = label+string("_slope");
                this->slope = Point(pointLabel,pointA.getCoordX() - pointB.getCoordX(),pointA.getCoordY() - pointB.getCoordY(),pointA.getCoordZ() - pointB.getCoordZ());
                this->startPoint = Point(pointA);  
            }
            
            Point getSlope() const { return slope; }
            Point getStartPoint() const {return startPoint; }
            string getLabel() const { return  label; }
        
            void setSlope(Point &value) { this->slope = value; }
            void setStartPoint(Point &value) { this->startPoint = value; }
            void setLabel(string value) { this->label = value;}
    };
}
