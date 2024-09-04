#pragma once

#include<iostream>
#include<string>
#include<vector>


/**
 * Class <c> Point <c> represents a geometrical point in a 3D space
 */
class Point {
    private: 
        std::string label;
        double coordX; 
        double coordY;
        double coordZ; 
        
    public:
        /**
         * @brief Constructor.
         */
        Point();

        /**
         * @brief Constructor.
         * @param label The point label.
         * @param coordX The point x coordinate.
         * @param coordY The point y coordinate.
         * @param coordZ The point z coordinate.
         */
        Point(std::string label, double coordX=0, double coordY=0, double coordZ=0);

        /**
         * @brief Copy constructor.
         * @param point The object to be copied. 
         */
        Point(const Point &point);

        /**
         * @brief Get the point x coordinate.
         * @return The point x coordinate.
         */
        double getCoordX() const;

        /**
         * @brief Get the point y coordinate.
         * @return The point y coordinate.
         */
        double getCoordY() const;

        /**
         * @brief Get the point z coordinate.
         * @return The point z coordinate.
         */
        double getCoordZ() const;

        /**
         * @brief Get the point label.
         * @return The point label.
         */
        std::string getLabel() const;
    
        /**
         * @brief Get if a point has a lower x coordinate value than another.
         * @param a The first point.
         * @param b The second point.
         * @return True if the first point has a lower x coordinate than the second point.
         */
        static bool isMinorX(const Point &a,const Point &b);

        /**
         * @brief Get if a point has a lower y coordinate value than another.
         * @param a The first point.
         * @param b The second point.
         * @return True if the first point has a lower y coordinate than the second point.
         */
        static bool isMinorY(const Point &a,const Point &b);

        /**
         * @brief Get if a point has a lower z coordinate value than another.
         * @param a The first point.
         * @param b The second point.
         * @return True if the first point has a lower z coordinate than the second point.
         */
        static bool isMinorZ(const Point &a,const Point &b);

        /**
         * @brief Remove duplicates in a list of points.
         * @param points The list of points.
         * @return The new list of points without duplicates. 
         */
        static std::vector<Point> removeDuplicates(std::vector<Point> & points);
    
        /**
         * @brief The "less than" operator override.
         * @param other The right hand side 
         * @return True if the left hand side object is lower than the right hand side object. False otherwise.
         */
        bool operator<(const Point &other)const;

        /**
         * @brief The "greater than" operator override.
         * @param other The right hand side 
         * @return True if the left hand side object is greater than the right hand side object. False otherwise.
         */
        bool operator>(const Point &other)const; 

        /**
         * @brief The equality operator override. 
         * @param other The right hand side object.
         * @return True if the objects are considered equals. False otherwise. 
         */
        bool operator==(const Point &other) const; 

        /**
         * @brief The assignment operator override.
         * @param other The right hand side 
         * @return A reference to the modified left hand side object.
         */
        Point &operator=(const Point &other); 
    
        /**
         * @brief Get the distance between two points.
         * @param other The point from which the distance will be measured.
         * @return The distance between this point and the parameter point. 
         */
        double getDistance(const Point &other);

        /**
         * @brief Out stream operator override. 
         * @param op The out stream object. 
         * @param p The point to be print.
         * @return A reference to the out stream object. 
         */
        friend std::ostream&operator<<(std::ostream &op, const Point &p){ 
            op<<"Label :"<<p.label<<" ("<<p.coordX<<","<<p.coordY<<","<<p.coordZ<<")\n"; 
            return op;
        }
};
