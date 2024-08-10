#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include "Point.h"
#include "Line.h"
using namespace std;
using namespace QuickTSP;

Line::Line(){}

Line::Line(const Line &other){
    this->startPoint = Point(other.getStartPoint());
    this->slope = Point(other.getSlope());
}

Line::Line(string label, Point &pointA, Point &pointB){
    string pointLabel = label+string("_slope");
    this->slope = Point(pointLabel,pointA.getCoordX() - pointB.getCoordX(),pointA.getCoordY() - pointB.getCoordY(),pointA.getCoordZ() - pointB.getCoordZ());
    this->startPoint = Point(pointA);
}

Point Line::getSlope() const { return slope; }
Point Line::getStartPoint() const {return startPoint; }
string Line::getLabel() const { return  label; }

void Line::setSlope(Point &value) { this->slope = value; }
void Line::setStartPoint(Point &value) { this->startPoint = value; }
void Line::setLabel(string value) { this->label = value;}