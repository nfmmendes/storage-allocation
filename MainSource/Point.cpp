
#include<iostream>
#include<string>
#include<utility>
#include<cmath>
#include<algorithm>
#include "Point.h"

#define TOLERANCE 0.000001


Point::Point(){
    coordX = coordY = coordZ = 0;
}

Point::Point(const string &label, double coordX, double coordY, double coordZ){
    
    this->label = label;
    this->coordX = coordX;
    this->coordY = coordY;
    this->coordZ = coordZ;
}

Point::Point(const Point &point){
    
    this->label = point.getLabel();
    this->coordX = point.getCoordX();
    this->coordY = point.getCoordY();
    this->coordZ = point.getCoordZ();
}
   
double Point::getCoordX() const { return coordX;}
double Point::getCoordY() const { return coordY; }
double Point::getCoordZ() const { return coordZ; }
string Point::getLabel()  const { return label; }

bool Point::isMinorX(const Point &a,const Point &b){
    return a.getCoordX() < b.getCoordX();
}

bool Point::isMinorY(const Point &a,const Point &b){
    return a.getCoordY() < b.getCoordY();
}

bool Point::isMinorZ(const Point &a,const Point &b){
    return a.getCoordZ() < b.getCoordZ();
}

bool Point::operator<(const Point &other)const{
	if(fabs(this->coordX - other.coordX) > TOLERANCE)
		return this->coordX < other.coordX; 
	if(fabs(this->coordY - other.coordY) > TOLERANCE)
		return this->coordY < other.coordY; 
	if(fabs(this->coordZ - other.coordZ) > TOLERANCE)
		return this->coordZ < other.coordZ; 
	
	return false; 
}

bool Point::operator>(const Point &other)const{
	return !(*this < other && *this == other);
}

bool Point::operator==(const Point &other) const{
	return fabs(this->coordX - other.coordX) <= TOLERANCE &&  
		   fabs(this->coordY - other.coordY)<= TOLERANCE && 
		   fabs(this->coordZ - other.coordZ) <= TOLERANCE;
}

Point & Point::operator=(const Point &other){
	this->label = other.getLabel();
    this->coordX = other.getCoordX();
    this->coordY = other.getCoordY();
    this->coordZ = other.getCoordZ();
	
	return *this; 
}

vector<Point>  Point::removeDuplicates(vector<Point> & points){
	
	sort(points.begin(), points.end()); 
	
	vector<int> pointsToRemove;
	for(int i=1; i<(int) points.size(); i++){
		if(fabs(points[i-1].coordX-points[i].coordX) < TOLERANCE && fabs(points[i-1].coordY-points[i].coordY) < TOLERANCE &&
		   fabs(points[i-1].coordZ-points[i].coordZ) < TOLERANCE)
		   pointsToRemove.push_back(i);
	}
		
	vector<Point> returned; 
	int cont = 0; 
	int tot = 0;
	for(tot=0; tot< (int) points.size() && cont < (int) pointsToRemove.size(); tot++){
		if(pointsToRemove[cont] == tot)
			cont++;
		else 
			returned.push_back(points[tot]);
	}
	
	for(;tot <(int) points.size();tot++)
		returned.push_back(points[tot]);

	if(pointsToRemove.size() == 0)
		return points; 
	
	return returned; 
		
}

double Point::getDistance(const Point &other){
    return sqrt(pow(this->coordX-other.coordX,2)+pow(this->coordY-other.coordY,2)+ pow(this->coordZ,2));
}
