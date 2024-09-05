#pragma once

#include <iostream>
#include "Corridor.h"
#include "Point.h"

/**
 * @brief Class <c> Curve </c> holds information and functions to represent a curve from a corridor 
 *         to another in the warehouse. 
 */
class Curve{
    
    private:
        long int startingCorridorId;			///< Id of corridor where the curve starts 
        long int endingCorridorId;				///< Id of corridor where the curve ends 
        Point startingPoint;					///< Coordinates of curve starting point 
        Point endingPoint;						///< Coordinates of curve ending point 
        long int Id;							///< Curve id 
    
    public:
        /**
         * @brief Constructor.
         */
        Curve();

        /**
         * @brief Copy constructor.
         */
        Curve(const Curve & other);

        /**
         * @brief The curve id.
         * @param id Curve id.
         * @param startingCorridor Id of the corridor where the curve starts.
         * @param endingCorridor Id of the corridor where the curve ends.
         * @param startingPoint The curve begin coordinates. 
         * @param endingPoint The curve ending coordinates.
         */
        Curve(long int id, long int startingCorridor, long int endingCorridor, 
             const Point& startingPoint, const Point& endingPoint);
    
        /**
         * @brief Get the id of the curve start corridor.
         * @return The id of the curve start corridor.
         */
        long int getStartCorridor() const;

        /**
         * @brief Get the id of the curve end corridor.
         * @return The id of the curve end corridor.
         */
        long int getEndCorridor() const;

        /**
         * @brief Get the curve start point.
         * @return The curve start point.
         */
        Point getStartingPoint() const;

        /**
         * @brief Get the curve end point.
         * @return The curve end point.
         */
        Point getEndingPoint() const;

        /**
         * @brief Get the curve id.
         * @return The curve id. 
         */
        long int getId() const;

        /**
         * @brief The assignment operator override. 
         * @param other The right hand side object.
         * @return A reference to the modified left side hand object. 
         */
        Curve &operator=(const Curve &other);

        /**
         * @brief The less than operator override. 
         * @param other The right hand side object.
         * @return True if the left side hand object is considered to be lower than
         *         the right hand side object. False otwerwise
         */
		bool operator<(const Curve &other) const;

        /**
         * @brief The equality operator override. 
         * @param other The right hand side object.
         * @return True if the objects are considered equals. False otherwise.
         */
		bool operator==(const Curve &other) const; 

        /**
         * @brief The inequality operator override. 
         * @param other The right hand side object.
         * @return True if the objects are considered inequals. False otherwise.
         */
		bool operator!=(const Curve &other) const; 

        /**
         * @brief Print curve information.
         */
		void printCurveInformation();
};

