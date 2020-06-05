#ifndef SHELF_H
#define SHELF_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Cell.h"
using namespace std; 


class Shelf{

    private:
        long int Id;							///< Shelf id
        vector<Cell> cells;         			///< Cells inside the shelf TODO: Make this relationship be consistent in both senses 
        pair<double,double> bottomLeftCoords;	///< Coordinates of shelf the bottom left extremity 
        string blockName;						///< Name of block where the shelf is 
        int columns;							///< Number of columns in the shelf
        int rows; 								///< Number of rows in the shelf 
        double cellLength;						///< Shelf cells length (In all the shelves is supposed that the cells have all the same size)
        double cellWidth; 						///< Shelf cells width (In all the shelves is supposed that the cells have all the same size)
        
        
    public:
        Shelf();
        Shelf(const Shelf &other);
        
        Shelf(long int Id,vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName,
              int columns, int rows, double cellLength, double cellWidth);
    
        long int getId() const;
        double getBottomLeftCoordX() const;
        double getBottomLeftCoordY() const;
        pair<double,double> getBottomLeftCoords()const;
        vector<Cell> getCells();
        string getBlockName() const;
        int getNumColumns() const;
        int getNumRows() const;
        double getCellLength() const;
        double getCellWidth() const;
        
        void setBottomLeftCoordX(double value);
        void setBottomLeftCoordY(double value);
        void setBottomLeftCoords(pair<double, double> value );
        void setCells(vector<Cell> &cells);
        void setBlockName(string name);
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

#endif
