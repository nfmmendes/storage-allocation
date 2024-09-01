#pragma once

#include<iostream>
#include<vector>
#include<utility>
#include "Cell.h" 
using std::vector;
using std::pair;
using std::string;

/**
 * @brief The Shelf class handles the data concerning a warehouse shelf. 
 */
class Shelf{

    private:
        long int Id;							///< Shelf id
        vector<Cell> cells;         		    ///< Cells inside the shelf TODO: Make this relationship be consistent in both senses 
        pair<double,double> bottomLeftCoords;	///< Coordinates of shelf the bottom left extremity 
        string blockName;					    ///< Name of block where the shelf is 
        int columns;							///< Number of columns in the shelf
        int rows; 								///< Number of rows in the shelf 
        double cellLength;						///< Shelf cells length (It is supposed that the cells have all the same size)
        double cellWidth; 						///< Shelf cells width (It is supposed that the cells have all the same size)
        
        
    public:
        /**
         *  @brief Constructor.
         */
        Shelf();

        /**     
         * @brief Copy constructor.
         * @param other The shelf being copied. 
         */
        Shelf(const Shelf &other);
        
        /**
         * @brief Constructor.
         * @param Id The shelf id.
         * @param cells The list of shelf cells.
         * @param bottomLeftCoords The shelf bottom left coordinates.
         * @param blockName The shelf block name. 
         * @param columns The number of columns in the shelf.
         * @param rows The number of rows in the shelf. 
         * @param cellLength The shelf cell lenght.
         * @param cellWidth The shelf cell width.
         */
        Shelf(long int Id, const vector<Cell>& cells, const pair<double, double>& bottomLeftCoords, string blockName,
              int columns, int rows, double cellLength, double cellWidth);
    
        /**
         *  @brief Get shelf id.
         * @return The shelf id. 
         */
        long int getId() const;

        /**  
         * @brief Get the shelf bottom left coordinate X. 
         * @return The shelf bottom left coordinate X. 
         */
        double getBottomLeftCoordX() const;

        /**
         * @brief Get the shelf bottom left coordinate Y.
         * @return The shelf bottom left coordinate Y.
         */
        double getBottomLeftCoordY() const;

        /**
         * @brief Get the shelf bottom left coordinates. 
         * @return The shelf bottom left coordinate. 
         */
        const pair<double,double>& getBottomLeftCoords()const;

        /**
         * @brief Get the shelf cells.
         * @return A list containing the shelf cells.
         */
        const vector<Cell>& getCells() const;

        /**
         * @brief Get the name of the block in which the shelf is located.
         * @return The name of the block in which the shelf it located. 
         */
        const string& getBlockName() const;

        /**
         * @brief Get the number of columns in the shelf.
         * @return The number of columns in the shelf.
         */ 
        int getNumColumns() const;

        /**
         * @brief Get the number of rows in the shelf. 
         * @return The number of rows in the shelf. 
         */
        int getNumRows() const;

        /**
         * @brief Get the shelf cells length. 
         * @return The shelf cells length.
         */
        double getCellLength() const;

        /**
         * @brief Get the shelf cells width. 
         * @return THe shelf cells width. 
         */
        double getCellWidth() const;
       
        /**
         * @brief Set the shelf cells.
         * @param cells The shelf cells. 
         */
        void setCells(vector<Cell> &cells);
		
        /**
		 * @brief Print shelf information in the console. 
         */
		void printShelfInformation();

        /**
    	 *  @brief Get the number of available positions in the shelf. 
		 * @return The number of available positions. 
         */
		int getNumberOfAvailablePositions(); 
		
        /**
		 * @brief Override less than operator<
		 * @param other The right side object.
		 * @return True if the left side object is smaller 
         *         than the right side object. False otherwise.
         */
		bool operator<(const Shelf &other)const; 
        
        /**
    	 *  @brief Override equals operator==. 
		 * @param other The right side object.
		 * @return True if the objects are equals. False otherwise.
         */
        
        bool operator==(const Shelf &other)const; 
        /**
    	 *  @brief Override not equals operator!=. 
		 * @param other The right side object.
		 * @return True if the objects are different. False otherwise.
         */
		
        bool operator!=(const Shelf &other)const; 
        
        /**
    	 *  @brief Override the assignment operator=.
		 * @param other The right side object.
		 * @return The reference to the modified object. 
        */
		Shelf & operator=(const Shelf &other);
};

