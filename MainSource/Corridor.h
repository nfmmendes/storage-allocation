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
 * @brief Class <c> Corridor </c> represents a warehouse corridor. This class is used to describe only 
 *        to rectilinear corridors that are parallel to the block walls. 
 */
class Corridor{
    
    private:
        unsigned long int Id { 0 };
        string blockName { };			            ///< Name of block where the corridor is 
        string direction { VERTICAL };       	    ///< Direction of The values can be: HORIZONTAL or VERTICAL
        string sense { UP_DOWN };             	    ///< The values can be: UP_DOWN, BOTTOM_UP, LEFT_TO_RIGHT, RIGHT_TO_LEFT, BOTH
        pair<double, double> begin { 0.0, 0.0 };	///< Coordinates of the corridor begin
        double length { 0.0 };				        ///< Length of corridor 
    
    public:
        /**
         * @brief Constructor.
         */
        Corridor();

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
         */
        Corridor(const Corridor & other);

        /**
         * @brief Constructor.
         * @param Id The corridor id. 
         * @param blockName The corridor block name. 
         * @param dir The corridor direction: "HORIZONTAL" or "VERTICAL"
         * @param sense The corridors sense: "UP_DOWN", "BOTTOM_UP", "LEFT_TO_RIGHT", "RIGHT_TO_LEFT", "BOTH"
         * @param begin The corridor begin coordinates. 
         * @param length The corridor length.
         */
        Corridor(unsigned long int Id, const string& blockName, const string& dir, const string& sense,
                 const pair<double,double>& begin, double length);
        
        /**
         * @brief Get the corridor direction. 
         * @return The corridor direction.
         */
        const string& getDirection() const;

        /**
         * @brief Get the corridor sense. 
         * @return The corridor sense. 
         */
        const string& getSense()const; 

        /**
         * @brief Get the corridor id.
         * @return The corridor id. 
         */
        unsigned long int getId() const;

        /**
         * @brief Get the corridor begin coordinates. 
         * @return The corridor begin coordinates. 
         */
        const pair<double, double>& getBeginCoords() const;
		
        /**
         * @brief Get the corridor length.
         * @return The corridor length
         */
        double getLength() const;

        /**
		 * @brief Get the corridor end coordinates. 
		 * @return The corridor end coordinates. 
		 */
        const pair<double, double>& getEndCoords() const;

        /**
         * @brief Sort the corridor internal points.
         * @param points The corridor internal points. 
         */
        void orderCorridorPoints(vector<Point> & points) const;

        /**
         * @brief Assignment operator override. 
         * @param other The right hand side object.
         * @return A reference to the modified left hand side object. 
         */
        Corridor& operator=(const Corridor &other);

        /**
		 * @brief Equality operator override. 
		 * @param other The right hand side object.
		 * @return True if the objects are considered equals. False otherwise.
		 */
        bool operator==(const Corridor &other)const;
		
        /**
         * @brief Inequality operator override. 
		 * @param other The right hand side object.
		 * @return True if the objects are considered inequals. False otherwise.
		 */
        bool operator!=(const Corridor &other)const;

        /**
		 * @brief Less than operator override. 
		 * @param other The right hand side object.
		 * @return True if the left hand side object is considered lower than the right
         *         hand side object. False otherwise. 
		 */
        bool operator<(const Corridor &other)const;

        /**
		 * @brief Print corridor information.
         */
		void printCorridorInformation() const;
};
