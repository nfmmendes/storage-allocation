#pragma once

#include<iostream>
#include<vector>
#include<utility>
#include "Cell.h" 

class Shelf{

    private:
        long int Id;							    ///< Shelf id
        std::vector<Cell> cells;         		    ///< Cells inside the shelf TODO: Make this relationship be consistent in both senses 
        std::pair<double,double> bottomLeftCoords;	///< Coordinates of shelf the bottom left extremity 
        std::string blockName;					    ///< Name of block where the shelf is 
        int columns;							    ///< Number of columns in the shelf
        int rows; 								    ///< Number of rows in the shelf 
        double cellLength;						    ///< Shelf cells length (It is supposed that the cells have all the same size)
        double cellWidth; 						    ///< Shelf cells width (It is supposed that the cells have all the same size)
        
        
    public:
        Shelf();
        Shelf(const Shelf &other);
        
        Shelf(long int Id, std::vector<Cell> cells, std::pair<double, double> bottomLeftCoords, std::string blockName,
              int columns, int rows, double cellLength, double cellWidth);
    
        long int getId() const;
        double getBottomLeftCoordX() const;
        double getBottomLeftCoordY() const;
        std::pair<double,double> getBottomLeftCoords()const;
        std::vector<Cell> getCells();
        std::string getBlockName() const;
        int getNumColumns() const;
        int getNumRows() const;
        double getCellLength() const;
        double getCellWidth() const;
        
        void setBottomLeftCoordX(double value);
        void setBottomLeftCoordY(double value);
        void setBottomLeftCoords(std::pair<double, double> value );
        void setCells(std::vector<Cell> &cells);
        void setBlockName(std::string name);
        void setNumColumns(int value);
        void setNumRows(int value);
        void setCellLength(double value);
        void setCellWidth(double value);
		
		void printShelfInformation();
		int getNumberOfAvailablePositions(); 
		
		bool operator<(const Shelf &other)const; 
		bool operator==(const Shelf &other)const; 
		bool operator!=(const Shelf &other)const; 
		Shelf & operator=(const Shelf &other);
};

