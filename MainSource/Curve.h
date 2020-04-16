//
//  Curve.hpp
//  
//
//  Created by Nilson Mendes on 12/12/2018.
//

#ifndef CURVE_h
#define CURVE_h

#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include "Corridor.h"
#include "Point.h"


class Curve{
    
    private:
        long int startingCorridorId;			///< Id of corridor where the curve starts 
        long int endingCorridorId;				///< Id of corridor where the curve ends 
        Point startingPoint;					///< Coordinates of curve starting point 
        Point endingPoint;						///< Coordinates of curve ending point 
        long int Id;							///< Curve id 
    
    public:
        Curve();
        Curve(const Curve & other);
        Curve(long int id, long int startingCorridor, long int endingCorridor, Point startingPoint, Point endingPoint);
        void setStartingCorridorId(long int &startId);
        void setEndingCorridorId(long int &endId);
        void setStartingPoint(Point &point);
        void setEndingPoint(Point &point);
        void setId(long int id);
    
        long int getStartCorridor() const;
        long int getEndCorridor() const;
        Point getStartingPoint() const ;
        Point getEndingPoint() const ;
        long int getId() const;
        Curve &operator=(const Curve &other);
		bool operator<(const Curve &other);
		bool operator==(const Curve &other); 
		bool operator!=(const Curve &other); 
		
		void printCurveInformation();
};

#endif

