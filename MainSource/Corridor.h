#pragma once

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include "Point.h"
using std::string;
using std::pair;
using std::vector;

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
        Corridor();
        Corridor(const Corridor & other);
        Corridor(long int Id, string blockName, string dir, string sense, pair<double,double> begin, double length);
        
        string getDirection() const;
        string getSense()const; 
        long int getId() const;
        string getBlockId();
        pair<double, double> getBeginCoords() const;
		
        double getLength()const;

		pair<double, double> getEndCoords() const;
        void orderCorridorPoints(vector<Point> & points)const;
        Corridor & operator=(const Corridor &other);
		bool operator==(const Corridor &other)const;
		bool operator!=(const Corridor &other)const;
		bool operator<(const Corridor &other)const;
		void printCorridorInformation();
};
