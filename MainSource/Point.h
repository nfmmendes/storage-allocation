#ifndef POINT_H
#define POINT_H

#include<iostream>
#include<string>
#include<utility>
using namespace std;


        //Class to represent a geometrical point in a 3D space
    class Point {
        private: 
            string label;
            double coordX; 
            double coordY;
            double coordZ; 
            
        public:
            Point();
            Point(string label, double coordX, double coordY, double coordZ);
            Point(const Point &point);
            void setCoordX(double value);
            void setCoordY(double value);
            
        
            void setCoordZ(double value);
            void setPoint(Point &point);
            
            double getCoordX() const;
            double getCoordY() const;
            double getCoordZ() const;
            string getLabel() const;
};


#endif
