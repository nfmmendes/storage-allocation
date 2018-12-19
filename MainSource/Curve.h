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
        long int startingCorridorId;
        long int endingCorridorId;
        Point startingPoint;
        Point endingPoint;
        long int Id;
    
    public:
        Curve();
        Curve(const Curve & other);
        Curve(long int id, long int startingCorridor, long int endingCorridor, Point startingPoint, Point endingPoint);
        void setStartingCorridorId(long int &startId);
        void setEndingCorridorId(long int &endId);
        void setStartingPoint(Point &point);
        void setEndingPoint(Point &point);
        void setId(long int id);
    
        long int getStartCorridor();
        long int getEndCorridor();
        Point getStartingPoint();
        Point getEndingPoint();
        long int getId();
    
};

#endif

