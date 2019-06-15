#ifndef Corridor_H
#define Corridor_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<cstdlib>
#include "Point.h"
//#include "Sense.h"
//#include "Direction.h"
using namespace std;



const string HORIZONTAL = "HORIZONTAL";
const string VERTICAL = "VERTICAL";

const string UP_DOWN = "UP_DOWN";
const string BOTTOM_UP = "BOTTOM_UP";
const string LEFT_TO_RIGHT = "LEFT_TO_RIGHT";
const string RIGHT_TO_LEFT = "RIGHT_TO_LEFT";
const string BOTH = "BOTH";




///
///     Class to represent corridors. This class is used to describe only retilinear corridors
///     and not transversal ones 
///
class Corridor{
    
    private:
        long int Id;
        string blockName;
        string direction;       //! The values can be: horizontal or vertical
        string sense;               //! The values can be: up_down, bottom_up, left_to_right, right_to_left, both
        pair<double, double> begin;
        double length;
    
    public:
        Corridor(){}
        Corridor(const Corridor & other){}
        Corridor(long int Id, string blockName, string dir, string sense, pair<double,double> begin, double length){
            this->Id = Id;
            this->blockName = blockName;
            this->direction = dir;
            this->sense = sense;
            this->begin = begin;
            this->length = length;
        }
    
    
        void setDirection(string value){  direction = value;}
        void setSense(string value) { sense = value; }
        void setId( long int value ) { if(value > 0) Id = value; else throw("Error. Invalid negative Id"); }
        void setIdBlock (string value) {blockName = value;}
        void setBeginCoords(pair<double,double> value){ begin = value; }
        void setLength(double value){ length = value; }
        
        string getDirection() const{ return direction; }
        string getSense()const  { return sense; } 
        long int getId() const { return Id; }
        string getBlockId() {return blockName; }
        pair<double, double> getBeginCoords() const { return begin; }
        double getLength()const { return length; }
    
        void orderCorridorPoints(vector<Point> & points)const{
            
            if(this->getDirection() ==  VERTICAL){
                sort(points.begin(), points.end(), Point::isMinorY);
                if(this->getSense() == RIGHT_TO_LEFT)
                    reverse(points.begin(), points.end());
                
            }else if(this->getDirection() == HORIZONTAL){
                sort(points.begin(), points.end(), Point::isMinorX);
                if(this->getSense() == UP_DOWN)
                    reverse(points.begin(), points.end());
            }
        }
    
        Corridor & operator=(const Corridor &other){
            this->Id = other.Id;
            this->blockName = other.blockName;
            this->direction = other.direction;
            this->sense = other.sense;
            this->begin = other.begin;
            this->length = other.length;
            
            return *this;
        }
    
};


#endif







