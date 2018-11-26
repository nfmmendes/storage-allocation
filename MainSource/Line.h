#include<iostream>
#include<string>
#include<cmath>
#include<cstdlib>
using namespace std;


namespace QuickTSP{

    class Line{
        private: 
            Point &startPoint;
            Point &slope;
            
        public:
            Line();
            
            Line(){
                Line & line;
            }
            
            Line(Point &pointA, Point &pointB){
                this->slope = Point(pointA.coordX - pointB.coordX,pointB.coordY - pointB.coordY,pointC.coordZ - pointC.coordZ);
                this->startPoint = Point(pointA);  
            }
    };
}
