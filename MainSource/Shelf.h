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
        long int Id;
        vector<Cell> cells;         //TODO: Remeber to make this kind of relationship be consistent in both senses 
        pair<double,double> bottomLeftCoords;
        string blockName;
        int columns;
        int lines; 
        double cellLength;
        double cellWidth; 
        
        
    public:
        Shelf();
    Shelf(const Shelf &other);
        
        Shelf(long int Id,vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName,
              int columns, int lines, double cellLength, double cellWidth);
    
        long int getId();
        double getBottomLeftCoordX();
        double getBottomLeftCoordY();
        pair<double,double> getBottomLeftCoords();
        vector<Cell> getCells();
        string getBlockName();
        int getNumColumns();
        int getNumLines();
        double getCellLength();
        double getCellWidth();
        
        void setBottomLeftCoordX(double value);
        void setBottomLeftCoordY(double value);
        void setBottomLeftCoords(pair<double, double> value );
        void setCells(vector<Cell> &cells);
        void setBlockName(string name);
        void setNumColumns(int value);
        void setNumLines(int value);
        void setCellLength(double value);
        void setCellWidth(double value);
};

#endif
