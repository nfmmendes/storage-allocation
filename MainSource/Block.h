#pragma once

#include<iostream>
#include<map>
#include<vector>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
#include "Curve.h"
using std::vector;
using std::pair;
using std::map;

/**
 * @brief The Block class handles information about a warehouse block. 
 */
class Block{

    private: 
        vector<Shelf> shelves;						///< Stores all shelves
		map<long int, Shelf> shelvesById;			///< Stores a map connecting a shelf id to the object
        vector<BlockExit> exits;					///< Store all the exists
        vector<Corridor> corridors;				    ///< Store all the corridors 
        vector<Curve> curves;						///< Store all the curves that conects two corridors 
        string name {}; 							///< Name of block
        double length {};							///< Block length 
        double width {}; 							///< Block width 
        pair<double,double> bottomLeftCoords;		///< Bottom left extremety of the block 
        
    public:
        /**
         * @brief Constructor.
         */
        Block();

        /**
         * @brief Copy constructor. 
         * @param other The object to be copied. 
         */
        Block(const Block &other);

        /**
         * @brief Constructor.
         * @param blockName The block name.
         * @param bottomLeftCoordX The block bottom-left coord x.
         * @param bottomLeftCoordY The block bottom-left coord y.
         * @param width The block width.
         * @param lenght The block weight. 
         */
        Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double lenght);
        
        /**
         * @brief Get if the block has a valid configuration.
         * @return True if the block has a valid configuration, false otherwise. 
         */
        bool hasValidConfiguration();

        /**
		 * @brief Add an exit to the block. 
		 * @param exit The exit to be added. 
		 * @return A reference to the modified block.
         */
		Block & addExit(BlockExit &exit);
        
        /**
         * @brief Get the block name.
         * @return The block name. 
         */
        string getName() const;

        /**
		 * @brief Get the block width.
		 * @return The block width. 
         */
		double getWidth();

        /**
		 * @brief Get the block lenght.
		 * @return The block lenght.
         */
		double getLenght();

        /**
         * @brief Get the block shelves. 
         * @return The block shelves. 
         */
        const vector<Shelf> & getShelves() const;

        /**
		 * @brief Get the block shelves by shelf id. 
		 * @return A map from a shelf id to a shelf. 
         */
		const map<long int, Shelf> & getShelvesById() const; 
		
        /**
         * @brief Get the block exits. 
         * @return The block exits. 
         */
        const vector<BlockExit>& getExits() const;

        /**
         * @brief Get the block corridors. 
         * @return The block corridors.
         */
        const vector<Corridor>& getCorridors() const;

        /**
         * @brief Get the block curves. 
         * @return The block curves. 
         */
        const vector<Curve>& getCurves() const;

        /**
         * @brief Get the block bottom left coords. 
         * @return The block bottom left coords. 
         */
        const pair<double,double>& getBottomLeftCoords() const;
    
        /**
         * @brief Check if a point is inside the block. 
         * @param point The point queried. 
         * @return True if the point is in the block. False otherwise. 
         */
        bool isInBlock(const Point &point) const;

        /**
		 * @brief Set the block name. 
		 * @param name The block name. 
         */
		void setName(const string &name);

        /**
         * @brief Set the block corridors.
         * @param others The block corridors. 
         */
        void setCorridors(vector<Corridor> & others);
    
        /**
         * @brief Set the block shelves. 
         * @param other The block shelves. 
         */
        void setShelves(vector<Shelf> & other);
    
        /**
         * @brief Set the block curves. 
         * @param other The block curves. 
         */
        void setCurves(vector<Curve> &other);
    
        //TODO: Improve this
        
        /**
         * @brief Equals operator override.
         * @param other The right hand side object.
         * @return True if the objects are equal. False otherwise. 
         */
        bool operator==(const Block &other);

        /**
		 * @brief Less than operator override.
		 * @param other The right hand side object.
		 * @return True if the left hand side object is smaller than the right
         *         hand object.
         */
		bool operator<(const Block &other)const;

        /**
		 * @brief Assignment operator override.
		 * @param other The right hand side object.
		 * @return A reference to the modified object. 
         */
		Block & operator=(const Block &other);
		
        /**
		 * @brief Get the number of available positions on the block.
		 * @return The number of available positions on the block.
         */
		int getNumberOfAvailablePositions(); 

        /**
		 * @brief Print the block information.
         */
		void printBlockInformation();
};
