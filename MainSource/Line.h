#pragma once

#include<iostream>
#include<string>
#include "Point.h"
using std::string;


namespace QuickTSP{

    /**
     * @brief Class <c> Line </c> Represent a basic rect segment, with a starting point and a 
     * slope in a tridimensional space. 
     */
    class Line{
        private: 
            Point startPoint;
            Point slope;
            string label; 
            
        public:       
            /**
             * @brief Copy constructor. 
             * @param other The object to be copied. 
             */
            Line(const Line &other);

            /**
             * @brief Constructor.
             * @param label The line label.  
             * @param pointA The starting point.
             * @param pointB The ending point. 
             */ 
            Line(std::string label, Point &pointA, Point &pointB);
                
            /**
             * @brief Get the line slope. 
             * @return The line slope. 
             */
            Point getSlope() const;

            /**
             * @brief Get the line starting point. 
             * @return The line starting point. 
             */
            Point getStartPoint() const;

            /**
             * @brief Get the line label. 
             * @return The line label. 
             */
            string getLabel() const;
    };
}
