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
        Corridor();
        Corridor(const Corridor & other);
        Corridor(long int Id, string blockName, string dir, string sense, pair<double,double> begin, double length);
    
        void setDirection(std::string value);
        void setSense(std::string value);
        void setId( long int value );
        void setIdBlock (std::string value);
        void setBeginCoords(std::pair<double,double> value);
        void setLength(double value);
        
        std::string getDirection() const;
        std::string getSense()const; 
        long int getId() const;
        std::string getBlockId();
        std::pair<double, double> getBeginCoords() const;
		
        double getLength()const;

		std::pair<double, double> getEndCoords() const;
        void orderCorridorPoints(std::vector<Point> & points)const;
        Corridor & operator=(const Corridor &other);
		bool operator==(const Corridor &other)const;
		bool operator!=(const Corridor &other)const;
		bool operator<(const Corridor &other)const;
		void printCorridorInformation();
};
