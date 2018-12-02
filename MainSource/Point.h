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
            
            //Full constructor
            //Null values are not allowed
            Point(string label, double coordX, double coordY, double coordZ){
            
                if(label == "")
                    throw("Error"); 
            
                this->label = label;
                this->coordX = coordX;
                this->coordY = coordY; 
                this->coordZ = coordZ; 
            }
            
            //Copy constructor
            //Null values are not allowed  
            Point(const Point &point){
            
                this->label = point.getLabel();
                this->coordX = point.getCoordX();
                this->coordY = point.getCoordY();
                this->coordZ = point.getCoordZ(); 
            }
            
            //Set the value of X coordinate 
            void setCoordX(double value){
                this->coordX = value;
            }
            
            //Set the value of the Y coordinate
            void setCoordY(double value){
                this->coordY = value;
            }
            
            //Set the value of the Z coordinate
            void setCoordZ(double value){
                this->coordZ = value;
            }
            
            void setPoint(Point &point){
                this->label = point.label;
                this->coordX = point.coordX;
                this->coordY = point.coordY;
                this->coordZ = point.coordZ;
            }
            
            double getCoordX() const { return coordX;}
            double getCoordY() const { return coordY; }
            double getCoordZ() const { return coordZ; }
            string getLabel()  const { return label; }
};


#endif