
#include<iostream>
#include<string>
#include<utility>
#include<cmath>
#include<algorithm>
#include "Point.h"
using namespace std;

#define TOLERANCE 0.000001


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
   
/**
 *
 */   
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


/**
 *
 */
bool Point::isMinorX(const Point &a,const Point &b){
    return a.getCoordX() < b.getCoordX();
}

/**
 *
 */
bool Point::isMinorY(const Point &a,const Point &b){
    return a.getCoordY() < b.getCoordY();
}

/**
 *
 */
bool Point::isMinorZ(const Point &a,const Point &b){
    return a.getCoordZ() < b.getCoordZ();
}

/**
 *
 */
bool Point::operator<(const Point &other)const{
    double distA = this->coordX*this->coordX + this->coordY*this->coordY + this->coordZ*this->coordZ;
    double distB = other.coordX*other.coordX + other.coordY*other.coordY + other.coordZ*other.coordZ;
    
    if(fabs(distA - distB) >= TOLERANCE)
        return distA < distB;
    else if(fabs(this->coordX - other.coordX) >= TOLERANCE)
        return this->coordX < other.coordX;
    else if(fabs(this->coordY - other.coordY) >= TOLERANCE)
        return this->coordY < other.coordY;
    else if(fabs(this->coordZ - other.coordZ) >= TOLERANCE)
        return this->coordZ < other.coordZ;
    else
        return this->label < other.label;
}

/**
 *
 */
bool Point::operator>(const Point &other)const{
	return !(*this < other && *this == other);
}

/**
 *
 */
bool Point::operator==(const Point &other) const{
	return this->label == other.label && fabs(this->coordX - other.coordX) <= 1e-10 &&  fabs(this->coordY - other.coordY)<=1e-10 && 
										 fabs(this->coordZ - other.coordZ) <= 1e-10;
}

/**
 *
 */
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
	for(int i=0; i< (int) points.size() && cont < (int) pointsToRemove.size(); i++){
		if(pointsToRemove[cont] == i)
			cont++;
		else 
			returned.push_back(points[i]);
	}
	
	if(pointsToRemove.size() == 0)
		return points; 
	
	return returned; 
		
}

/**
 *
 */
double Point::getDistance(const Point &other){
    return sqrt(pow(this->coordX-other.coordX,2)+pow(this->coordY-other.coordY,2)+ pow(this->coordZ,2));
}
