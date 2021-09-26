#pragma once

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include "Point.h"
using namespace std;



const std::string HORIZONTAL = "HORIZONTAL";
const std::string VERTICAL = "VERTICAL";

const std::string UP_DOWN = "UP_DOWN";
const std::string BOTTOM_UP = "BOTTOM_UP";
const std::string LEFT_TO_RIGHT = "LEFT_TO_RIGHT";
const std::string RIGHT_TO_LEFT = "RIGHT_TO_LEFT";
const std::string BOTH = "BOTH";

/**
 *     Class to represent corridors. This class is used to describe only retilinear corridors
 *     and not transversal ones 
 */
class Corridor{
    
    private:
        long int Id;
        std::string blockName;			  ///< Name of block where the corridor is 
        std::string direction;       	  ///< Direction of The values can be: HORIZONTAL or VERTICAL
        std::string sense;             	  ///< The values can be: UP_DOWN, BOTTOM_UP, LEFT_TO_RIGHT, RIGHT_TO_LEFT, BOTH
        std::pair<double, double> begin;	  ///< Coordinates of the corridor begin
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
    
    
        void setDirection(std::string value){  direction = value;}
        void setSense(std::string value) { sense = value; }
        void setId( long int value ) { if(value > 0) Id = value; else throw("Error. Invalid negative Id"); }
        void setIdBlock (std::string value) {blockName = value;}
        void setBeginCoords(std::pair<double,double> value){ begin = value; }
        void setLength(double value){ length = value; }
        
        std::string getDirection() const{ return direction; }
        std::string getSense()const  { return sense; } 
        long int getId() const { return Id; }
        std::string getBlockId() {return blockName; }
        std::pair<double, double> getBeginCoords() const { return begin; }
		
        double getLength()const { return length; }
    
		/**
		 *
		 */
		std::pair<double, double> getEndCoords() const { 
		
			if(direction == HORIZONTAL){
				if( sense == LEFT_TO_RIGHT || sense == BOTH)
					return std::make_pair<double,double>((double)begin.first + length, (double)begin.second);
				else 
					return std::make_pair<double,double>((double)begin.first - length, (double)begin.second); 				
			}else {
				if(sense == UP_DOWN)
					return std::make_pair<double,double>((double)begin.first, (double) begin.second - length); 
				else 
					return std::make_pair<double,double>((double)begin.first,(double) begin.second + length); 
			}
		}
		
	
		/**
		 *
		 */
        void orderCorridorPoints(std::vector<Point> & points)const{
            
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
