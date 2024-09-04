#include "Corridor.h"

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
using namespace std;


Corridor::Corridor(){}

Corridor::Corridor(const Corridor & other){
			
    this->Id = other.Id;
    this->blockName = other.blockName;
    this->direction = other.direction;
    this->sense = other.sense;
    this->begin = other.begin; 
    this->length = other.length;
}


Corridor::Corridor(long int Id, string blockName, string dir, string sense, pair<double,double> begin, double length){
    this->Id = Id;
    this->blockName = blockName;
    this->direction = dir;
    this->sense = sense;
    this->begin = begin;
    this->length = length;
}

std::string Corridor::getDirection() const{ return direction; }
std::string Corridor::getSense()const  { return sense; } 
long int Corridor::getId() const { return Id; }
std::string Corridor::getBlockId() {return blockName; }
std::pair<double, double> Corridor::getBeginCoords() const { return begin; }


double Corridor::getLength()const { return length; }

/**
 *
 */
std::pair<double, double> Corridor::getEndCoords() const { 

    if(direction == HORIZONTAL){
        if( sense == LEFT_TO_RIGHT || sense == BOTH)
            return std::make_pair(begin.first + length, begin.second);
        else 
            return std::make_pair(begin.first - length, (double)begin.second); 				
    }else {
        if(sense == UP_DOWN)
            return std::make_pair(begin.first, begin.second - length); 
        else 
            return std::make_pair(begin.first, begin.second + length); 
    }
}


/**
 *
 */
void Corridor::orderCorridorPoints(std::vector<Point> & points)const{
    
    if(this->getDirection() ==  VERTICAL){
        std::sort(points.begin(), points.end(), Point::isMinorY);
        if(this->getSense() == UP_DOWN)
            std::reverse(points.begin(), points.end());
        
    }else if(this->getDirection() == HORIZONTAL){
        std::sort(points.begin(), points.end(), Point::isMinorX);
        if(this->getSense() == RIGHT_TO_LEFT)
            std::reverse(points.begin(), points.end());
    }
}

/**
 *
 */
Corridor & Corridor::operator=(const Corridor &other){
    this->Id = other.Id;
    this->blockName = other.blockName;
    this->direction = other.direction;
    this->sense = other.sense;
    this->begin = other.begin;
    this->length = other.length;
    
    return *this;
}

/**
 *
 */
bool Corridor::operator==(const Corridor &other)const{
    return this->Id == other.Id && this->blockName == other.blockName && direction == other.direction && this->sense == other.sense &&
            this->begin == other.begin && this->length == other.length; 
}

/**
 *
 */
bool Corridor::operator!=(const Corridor &other)const{
    return !(*this == other); 
}


/**
 *
 */
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


void Corridor::printCorridorInformation(){
    cout<<"___________________________________\n";
    cout<<"Corridor :\t"<<this->Id<<endl;
    cout<<"Block name :\t"<<this->blockName<<"\tDirection: \t"<<this->direction<<"\tSense: \t"<<this->sense<<endl;
    cout<<"Begin point: \t(x="<<this->begin.first<<" , y="<<this->begin.second<<")\t Length="<<this->length<<endl; 
    cout<<"___________________________________\n\n";
}