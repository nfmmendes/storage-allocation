
#include<iostream>
#include<string>
#include<utility>
#include "Point.h"
using namespace std;


Point::Point(){
    coordX = coordY = coordZ = 0;
}
    
    //Full constructor
    //Null values are not allowed
Point::Point(string label, double coordX, double coordY, double coordZ){
    
    if(label == "")
        throw("Error");
    
    this->label = label;
    this->coordX = coordX;
    this->coordY = coordY;
    this->coordZ = coordZ;
}
    
    //Copy constructor
    //Null values are not allowed
Point::Point(const Point &point){
    
    this->label = point.getLabel();
    this->coordX = point.getCoordX();
    this->coordY = point.getCoordY();
    this->coordZ = point.getCoordZ();
}
    
//Set the value of X coordinate
void Point::setCoordX(double value){
    this->coordX = value;
}
    
//Set the value of the Y coordinate
void Point::setCoordY(double value){
    this->coordY = value;
}
    
//Set the value of the Z coordinate
void Point::setCoordZ(double value){
    this->coordZ = value;
}
    
void Point::setPoint(Point &point){
    this->label = point.label;
    this->coordX = point.coordX;
    this->coordY = point.coordY;
    this->coordZ = point.coordZ;
}
    
double Point::getCoordX() const { return coordX;}
double Point::getCoordY() const { return coordY; }
double Point::getCoordZ() const { return coordZ; }
string Point::getLabel()  const { return label; }

