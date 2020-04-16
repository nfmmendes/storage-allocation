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




/**
 *     Class to represent corridors. This class is used to describe only retilinear corridors
 *     and not transversal ones 
 */
class Corridor{
    
    private:
        long int Id;
        string blockName;			  ///< Name of block where the corridor is 
        string direction;       	  ///< Direction of The values can be: HORIZONTAL or VERTICAL
        string sense;             	  ///< The values can be: UP_DOWN, BOTTOM_UP, LEFT_TO_RIGHT, RIGHT_TO_LEFT, BOTH
        pair<double, double> begin;	  ///< Coordinates of the corridor begin
        double length;				  ///< Length of corridor 
    
    public:
        Corridor(){}
        Corridor(const Corridor & other){
			
			this->Id = other.Id;
			this->blockName = other.blockName;
			this->direction = other.direction;
			this->sense = other.sense;
			this->begin = other.begin; 
			this->length = other.length;
		}
		
		///
		///
		///
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
    
		/**
		 *
		 */
		pair<double, double> getEndCoords() const { 
		
			if(direction == HORIZONTAL){
				if( sense == LEFT_TO_RIGHT || sense == BOTH)
					return make_pair<double,double>((double)begin.first + length, (double)begin.second);
				else 
					return make_pair<double,double>((double)begin.first - length, (double)begin.second); 				
			}else {
				if(sense == UP_DOWN)
					return make_pair<double,double>((double)begin.first, (double) begin.second - length); 
				else 
					return make_pair<double,double>((double)begin.first,(double) begin.second + length); 
			}
		}
		
	
		/**
		 *
		 */
        void orderCorridorPoints(vector<Point> & points)const{
            
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
    
		/**
		 *
		 */
        Corridor & operator=(const Corridor &other){
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
		bool operator==(const Corridor &other)const{
			return this->Id == other.Id && this->blockName == other.blockName && direction == other.direction && this->sense != other.sense &&
				   this->begin == other.begin && this->length == other.length; 
		}
		
		/**
		 *
		 */
		bool operator!=(const Corridor &other)const{
			return !(*this == other); 
		}
    
	
		/**
		 *
		 */
		bool operator<(const Corridor &other)const{
			
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
		
		
		void printCorridorInformation(){
			cout<<"___________________________________\n";
			cout<<"Corridor :\t"<<this->Id<<endl;
			cout<<"Block name :\t"<<this->blockName<<"\tDirection: \t"<<this->direction<<"\tSense: \t"<<this->sense<<endl;
			cout<<"Begin point: \t(x="<<this->begin.first<<" , y="<<this->begin.second<<")\t Length="<<this->length<<endl; 
			cout<<"___________________________________\n\n";
		}
};


#endif







