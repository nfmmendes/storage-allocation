#ifndef Corridor_H
#define Corridor_H

#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>
#include<cstdlib>
using namespace std;

///Class to define the direction of a corridor in a warehouse
///It has two possible values, indicated by static objects 
class Direction{

    private:
        string code; 
        
    public:
        Direction(){ this->code = Direction::HORIZONTAL.code; }
        Direction(const string &c) { this->code = c; }
        static const string horizontalCode; 
        static const string verticalCode; 
        static Direction HORIZONTAL;
        static Direction VERTICAL;
        string getDirectionCode() { return code;}
    
        static Direction parseDirection(string &directionString){
            if(directionString == Direction::VERTICAL.code)
                return Direction::VERTICAL;
            else if(directionString == Direction::HORIZONTAL.code)
                return Direction::HORIZONTAL;
            else
                return Direction::VERTICAL;
        }
        
};

///Static class members initialization
const string Direction::horizontalCode = "horizontal";
const string Direction::verticalCode = "vertical";
Direction Direction::HORIZONTAL(Direction::horizontalCode);
Direction Direction::VERTICAL(Direction::verticalCode);

///Class to define the sense of a corridor in a warehouse
///It has four possible values, indicated by static objects 
class Sense{

    private:
         string code; 
        
    public:
        Sense(){ this->code = UP_DOWN.code; }
        Sense(const string c){ this->code = c; }
        static const string up_down_code;
        static const string bottom_up_code;
        static const string left_to_right_code;
        static const string right_to_left_code;
        
        static Sense UP_DOWN;
        static Sense BOTTOM_UP;
        static Sense LEFT_TO_RIGHT;
        static Sense RIGHT_TO_LEFT;
        
        Sense &operator=(Sense &other){ this->code = other.code;  return *this;} 
        string getSenseCode() { return code;}
    
        static Sense parseSense(string &senseString){
            if(senseString == Sense::UP_DOWN.code)
                return Sense::UP_DOWN;
            else if(senseString == Sense::BOTTOM_UP.code)
                return Sense::BOTTOM_UP;
            else if(senseString == Sense::LEFT_TO_RIGHT.code)
                return Sense::LEFT_TO_RIGHT;
            else if(senseString == Sense::RIGHT_TO_LEFT.code)
                return Sense::RIGHT_TO_LEFT;
            else
                return Sense::UP_DOWN;
        }
    
};

///Static class members iniatilization
const string Sense::up_down_code = "up_down";
const string Sense::bottom_up_code = "bottom_up_code";
const string Sense::left_to_right_code = "left_to_right";
const string Sense::right_to_left_code = "right_to_left_code"; 
Sense Sense::UP_DOWN(Sense::up_down_code);
Sense Sense::BOTTOM_UP(Sense::bottom_up_code);
Sense Sense::LEFT_TO_RIGHT(Sense::left_to_right_code);
Sense Sense::RIGHT_TO_LEFT(Sense::right_to_left_code); 


///
///     Class to represent corridors. This class is used to describe only retilinear corridors
///     and not transversal ones 
///
class Corridor{
    
    private:
        long int Id;
        string blockName;
        Direction direction;           //! The values can be: horizontal or vertical
        Sense sense;               //! The values can be: up_down, bottom_up, left_to_right, right_to_left
        pair<double, double> begin;
        double length;
    
    public:
        Corridor();
        Corridor(const Corridor & other);
        Corridor(long int Id, string blockName, Direction dir, Sense sense, pair<double,double> begin, double length){
            this->Id = Id;
            this->blockName = blockName;
            this->direction = dir;
            this->sense = sense;
            this->begin = begin;
            this->length = length;
        }
    
    
        void setDirection(Direction value){  direction = value;}
        void setSense(Sense value) { sense = value; }
        void setId( long int value ) { if(value > 0) Id = value; else throw("Error. Invalid negative Id"); }
        void setIdBlock (string value) {blockName = value;}
        void setBeginCoords(pair<double,double> value){ begin = value; }
        void setLength(double value){ length = value; }
        
        Direction getDirection(){ return direction; }
        Sense getSense() { return sense; } 
        long int getId() { return Id; }
        string getBlockId() {return blockName; }
        pair<double, double> getBeginCoords() { return begin; }
        double getLenght() { return length; } 
        
        
};


#endif







