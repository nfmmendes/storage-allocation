#pragma once

#include<iostream>
#include<string>
#include<vector>


//Class to represent a geometrical point in a 3D space
class Point {
    private: 
        std::string label;
        double coordX; 
        double coordY;
        double coordZ; 
        
    public:
        Point();
        Point(std::string label, double coordX=0, double coordY=0, double coordZ=0);
        Point(const Point &point);
                
        double getCoordX() const;
        double getCoordY() const;
        double getCoordZ() const;
        std::string getLabel() const;
    
        static bool isMinorX(const Point &a,const Point &b);
        static bool isMinorY(const Point &a,const Point &b);
        static bool isMinorZ(const Point &a,const Point &b);
        static std::vector<Point> removeDuplicates(std::vector<Point> & points);
    
        bool operator<(const Point &other)const;
        bool operator>(const Point &other)const; 
        bool operator==(const Point &other) const; 
        Point &operator=(const Point &other); 
    
        double getDistance(const Point &other);
        friend std::ostream&operator<<(std::ostream &op, const Point &p){ 
            op<<"Label :"<<p.label<<" ("<<p.coordX<<","<<p.coordY<<","<<p.coordZ<<")\n"; 
            return op;
        }
        
};
