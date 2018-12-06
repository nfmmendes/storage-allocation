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
        vector<Cell> cells; 
        pair<double,double> bottomLeftCoords;
        string blockName;
        int columns;
        int lines; 
        double cellLength;
        double cellWidth; 
        
        
    public:
        Shelf();
        Shelf(const Shelf &other){
            for(unsigned int i=0; i <other.cells.size(); i++){
                Cell inserted(other.cells[i]);
                this->cells.push_back(inserted); 
            }
            
            this->Id = other.Id;
            this->bottomLeftCoords = other.bottomLeftCoords;
            this->blockName = other.blockName;
            this->columns = other.columns;
            this->cellLength = other.cellLength;
            this->cellWidth = other.cellWidth;
        }
        
        Shelf(long int Id,vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName,
              int columns, int lines, double cellLength, double cellWidth){
                  
            for(unsigned int i=0;i<cells.size(); i++){
                Cell inserted(cells[i]);
                this->cells.push_back(inserted);
            }
            
            this->Id = Id;
            this->bottomLeftCoords = bottomLeftCoords;
            this->blockName = blockName;
            this->columns = columns;
            this->lines = lines;
            this->cellLength = cellLength;
            this->cellWidth = cellWidth; 
        }
    
        long int getId(){ return Id;}
        double getBottomLeftCoordX() { return bottomLeftCoords.first; }
        double getBottomLeftCoordY() { return bottomLeftCoords.second; }
        pair<double,double> getBottomLeftCoords() { return bottomLeftCoords; }
        vector<Cell> getCell(){ return cells;}
        string getBlockName(){ return blockName; }
        int getNumColumns() {return columns;}
        int getNumLines(){ return lines;}
        double getCellLength() { return cellLength;}
        double getCellWidth() { return cellWidth;}
    
        void setBottomLeftCoordX(double value) { this->bottomLeftCoords.first = value; }
        void setBottomLeftCoordY(double value) { this->bottomLeftCoords.second = value; }
        void setBottomLeftCoords(pair<double, double> value ) { this->bottomLeftCoords = value;}
        void setCells(vector<Cell> &cells){ this->cells = cells;}
        void setBlockName(string name){ this->blockName = name;}
        void setNumColumns(int value){ if(value > 0) columns = value; }
        void setNumLines(int value){ if(value > 0) lines = value; }
        void setCellLength(double value){ if(value>0) cellLength = value;}
        void setCellWidth(double value){ if(value >0) cellWidth = value; }
};
