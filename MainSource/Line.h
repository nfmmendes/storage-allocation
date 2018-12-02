#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include "Point.h"
using namespace std;


namespace QuickTSP{

    class Line{
        private: 
            Point startPoint;
            Point slope;
            string label; 
            
        public:
            Line();
            
            Line(const Line &other){
                this->startPoint = Point(other.getStartPoint());
                this->slope = Point(other.getSlope());
            }
            
            
            Line(string label, Point &pointA, Point &pointB){
                string pointLabel = label+string("_slope");
                this->slope = Point(pointLabel,pointA.getCoordX() - pointB.getCoordX(),pointA.getCoordY() - pointB.getCoordY(),pointA.getCoordZ() - pointB.getCoordZ());
                this->startPoint = Point(pointA);  
            }
            
            
            Point getSlope() const { return slope; }
            Point getStartPoint() const {return startPoint; }
    };
}
