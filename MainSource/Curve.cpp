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

long int Curve::getStartCorridor(){ return startingCorridorId; }
long int Curve::getEndCorridor(){ return endingCorridorId; }
Point Curve::getStartingPoint(){ return startingPoint;}
Point Curve::getEndingPoint(){ return endingPoint; }
long int Curve::getId(){ return Id; }
