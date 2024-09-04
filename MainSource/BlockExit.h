#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<utility>
using std::string;
using std::pair;

/** 
 * @brief Class <c> BlockExit </c> describes a block exit. These exits can connect one warehouse
 * to another or just to a warehouse exit. In this implementation, a exit can
 * not connect more than two blocks.
 */
class BlockExit{
    
    private:
        long int Id { 0 };
        double coordX { 0.0 };					    ///< X-coordinate of central exit point 
        double coordY { 0.0 };					    ///< Y-coordinate of central exit point  
        string blockAName { "" };   				///< First block of exit 
        string blockBName { "" };	    			///< Second block of exit. The second block can be empty if the exit goes out of warehouse
    public:
        /**
         * @brief 
         */
        BlockExit();

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
        */
        BlockExit(const BlockExit &other);
        
        /**
         * @brief Constructor.
         * @param id The exit id. 
         * @param coordX The exit coordinate x.
         * @param coordY The exit coordinate y.
         * @param blockA The exit block A (origin) name.
         * @param blockB The exit block B (destination) name.
         */
        BlockExit(long int id, double coordX, double coordY, std::string blockA, std::string blockB="");
        
        /**
         * @brief Get the exit id.
         * @return The exit id. 
         */
        long int getId() const;

        /**
         * @brief Get the exit coordinate x.
         * @return The exit coordinate x.
         */
        double getCoordX() const;

        /**
         * @brief Get the exit coordinate y. 
         * @return The exit coordinate y.
         */
        double getCoordY() const;

        /**
         * @brief Get the block A (origin) name.
         * @return The block A name. 
         */
        string getBlockAName() const;

        /**
         * @brief Get the block B (destination) name.
         * @return The block B name. 
         */
        string getBlockBName() const;

        /**
         * @brief Get the exit coordinates. 
         * @return The exit coordinates.
         */
        pair<double, double> getCoords() const;

        /**
         * @brief Equal operator override.
         * @param other The right hand side object. 
         * @return True if both objects are considered equal. False otherwise. 
         */
        bool operator==(const BlockExit &other) const;

        /**
         * @brief Not equal operator override.
         * @param other The right hand side object.
         * @return True if the objects are considered not equal. False otherwise. 
         */
        bool operator!=(const BlockExit &other) const;

        /**
         * @brief Less than operator override 
         * @param other The right hand side object. 
         * @return True if the left hand side object is lower than the right hand side object. 
         *         False otherwise. 
         */
        bool operator<(const BlockExit & other) const;

        /**
		 * @brief ASsignment operator override
		 * @param other The right side operator object that will be copied. 
		 * @return A reference to the modified object. 
		 */
        BlockExit & operator=(const BlockExit &other);
		
        /**
		 * @brief Print block information. 
         */
		void printExitInformation();
};
