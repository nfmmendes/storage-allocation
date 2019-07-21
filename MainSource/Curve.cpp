#include "Curve.h"



Curve::Curve(){}

Curve::Curve(const Curve & other){
    this->Id = other.Id;
    this->startingPoint = other.startingPoint;
    this->endingPoint = other.endingPoint;
    this->startingCorridorId = other.startingCorridorId;
    this->endingCorridorId = other.endingCorridorId;
    
}

Curve::Curve(long int id, long int startingCorridor, long int endingCorridor, Point startingPoint, Point endingPoint){
    this->Id = id;
    this->startingCorridorId = startingCorridor;
    this->endingCorridorId = endingCorridor;
    this->startingPoint = startingPoint;
    this->endingPoint = endingPoint;
}

void Curve::setStartingCorridorId(long int &startId){
    if(startId >= 0) this->startingCorridorId = startId;
}

void Curve::setEndingCorridorId(long int &endId){
    if(endId >= 0) this->endingCorridorId = endId;
}

void Curve::setStartingPoint(Point &point){ this->startingPoint = point; }
void Curve::setEndingPoint(Point &point){ this->endingPoint = point; }
void Curve::setId(long int id){ this->Id = id;}

long int Curve::getStartCorridor() const { return startingCorridorId; }
long int Curve::getEndCorridor() const { return endingCorridorId; }
Point Curve::getStartingPoint() const { return startingPoint;}
Point Curve::getEndingPoint() const { return endingPoint; }
long int Curve::getId()const{ return Id; }

Curve & Curve::operator=(const Curve &other){
    this->Id = other.Id;
    this->startingCorridorId = other.startingCorridorId;
    this->endingCorridorId = other.endingCorridorId;
    this->startingPoint = other.startingPoint;
    this->endingPoint = other.endingPoint;
    
    return *this;
}


void Curve::printCurveInformation(){
	
	cout<<"____________________________________\n";
	cout<<"Curve: \t"<<this->Id <<endl;
	cout<<"Starting corridor: \t"<<this->startingCorridorId<<"\t"<<"Ending corridor \n"<<endl; 
	cout<<"Starting point: (x=\t"<<this->startingPoint.getCoordX()<<", y="<<this->startingPoint.getCoordY()<<")";
	cout<<"Ending point: (x=\t"<<this->endingPoint.getCoordX()<<", y="<<this->endingPoint.getCoordY()<<")\n";
	cout<<"____________________________________\n";
}