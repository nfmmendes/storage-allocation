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
			
    Id = other.Id;
    blockName = other.blockName;
    direction = other.direction;
    sense = other.sense;
    begin = other.begin; 
    length = other.length;
}


Corridor::Corridor(unsigned long int Id, const string& blockName, const string& dir, const string& sense, 
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
unsigned long int Corridor::getId() const { return Id; }
const pair<double, double>& Corridor::getBeginCoords() const { return begin; }


double Corridor::getLength()const { return length; }

const pair<double, double> Corridor::getEndCoords() const { 

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
    
    if(getDirection() ==  VERTICAL){
        sort(points.begin(), points.end(), Point::isMinorY);
        if(getSense() == UP_DOWN)
            reverse(points.begin(), points.end());
        
    }else if(getDirection() == HORIZONTAL){
        sort(points.begin(), points.end(), Point::isMinorX);
        if(getSense() == RIGHT_TO_LEFT)
            reverse(points.begin(), points.end());
    }
}

Corridor & Corridor::operator=(const Corridor &other){
    Id = other.Id;
    blockName = other.blockName;
    direction = other.direction;
    sense = other.sense;
    begin = other.begin;
    length = other.length;
    
    return *this;
}

bool Corridor::operator==(const Corridor &other)const{
    return Id == other.Id && blockName == other.blockName && direction == other.direction && sense == other.sense &&
            begin == other.begin && length == other.length; 
}

bool Corridor::operator!=(const Corridor &other)const{
    return !(*this == other); 
}

bool Corridor::operator<(const Corridor &other)const{
    
    if(begin > other.begin)
        return false;
    if(begin< other.begin)
        return true;
    
    if(length > other.length)
        return false; 
    if(length < other.length)
        return true; 
    
    if(blockName > other.blockName)
        return false;
    if(blockName < other.blockName)
        return true;
    
    if(direction > other.direction)
        return false;
    if(direction < other.direction)
        return true; 
        
    if(sense > other.sense)
        return false; 
    if(sense < other.sense)
        return true; 
    
    return false; 
        
}


void Corridor::printCorridorInformation() const{
    cout<<"___________________________________\n";
    cout<<"Corridor :\t"<<Id<<endl;
    cout<<"Block name :\t"<<blockName<<"\tDirection: \t"<<direction<<"\tSense: \t"<<sense<<endl;
    cout<<"Begin point: \t(x="<<begin.first<<" , y="<<begin.second<<")\t Length="<<length<<endl; 
    cout<<"___________________________________\n\n";
}