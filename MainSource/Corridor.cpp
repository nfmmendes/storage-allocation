#include "Corridor.h"

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using std::cout;
using std::endl;
using std::sort;
using std::reverse;
using std::make_pair;


Corridor::Corridor(){}

Corridor::Corridor(const Corridor & other){
			
    this->Id = other.Id;
    this->blockName = other.blockName;
    this->direction = other.direction;
    this->sense = other.sense;
    this->begin = other.begin; 
    this->length = other.length;
}


Corridor::Corridor(long int Id, const string& blockName, const string& dir, const string& sense, 
                   const pair<double,double>& begin, double length){
    this->Id = Id;
    this->blockName = blockName;
    this->direction = dir;
    this->sense = sense;
    this->begin = begin;
    this->length = length;
}

const string& Corridor::getDirection() const{ return direction; }
const string& Corridor::getSense()const  { return sense; } 
long int Corridor::getId() const { return Id; }
const string& Corridor::getBlockId() const { return blockName; }
const pair<double, double>& Corridor::getBeginCoords() const { return begin; }


double Corridor::getLength()const { return length; }

const pair<double, double>& Corridor::getEndCoords() const { 

    if(direction == HORIZONTAL){
        if( sense == LEFT_TO_RIGHT || sense == BOTH)
            return make_pair(begin.first + length, begin.second);
        else 
            return make_pair(begin.first - length, (double)begin.second); 				
    }else {
        if(sense == UP_DOWN)
            return make_pair(begin.first, begin.second - length); 
        else 
            return make_pair(begin.first, begin.second + length); 
    }
}

void Corridor::orderCorridorPoints(vector<Point>& points) const {
    
    if(this->getDirection() ==  VERTICAL){
        sort(points.begin(), points.end(), Point::isMinorY);
        if(this->getSense() == UP_DOWN)
            reverse(points.begin(), points.end());
        
    }else if(this->getDirection() == HORIZONTAL){
        sort(points.begin(), points.end(), Point::isMinorX);
        if(this->getSense() == RIGHT_TO_LEFT)
            reverse(points.begin(), points.end());
    }
}

Corridor & Corridor::operator=(const Corridor &other){
    this->Id = other.Id;
    this->blockName = other.blockName;
    this->direction = other.direction;
    this->sense = other.sense;
    this->begin = other.begin;
    this->length = other.length;
    
    return *this;
}

bool Corridor::operator==(const Corridor &other)const{
    return this->Id == other.Id && this->blockName == other.blockName && direction == other.direction && this->sense == other.sense &&
            this->begin == other.begin && this->length == other.length; 
}

bool Corridor::operator!=(const Corridor &other)const{
    return !(*this == other); 
}

bool Corridor::operator<(const Corridor &other)const{
    
    if(this->begin > other.begin)
        return false;
    else if(this->begin<other.begin)
        return true;
    
    if(this->length > other.length)
        return false; 
    else if(this->length < other.length)
        return true; 
    
    if(this->Id > other.Id)
        return false; 
    else if(this->Id < other.Id)
        return true; 
    
    if(this->blockName > other.blockName)
        return false;
    else if(this->blockName < other.blockName)
        return true;
    
    
    if(this->direction > other.direction)
        return false;
    else if(this->direction < other.direction)
        return true; 
        
    
    if(this->sense > other.sense)
        return false; 
    else if(this->sense < other.sense)
        return true; 
    
    return false; 
        
}


void Corridor::printCorridorInformation() const{
    cout<<"___________________________________\n";
    cout<<"Corridor :\t"<<this->Id<<endl;
    cout<<"Block name :\t"<<this->blockName<<"\tDirection: \t"<<this->direction<<"\tSense: \t"<<this->sense<<endl;
    cout<<"Begin point: \t(x="<<this->begin.first<<" , y="<<this->begin.second<<")\t Length="<<this->length<<endl; 
    cout<<"___________________________________\n\n";
}