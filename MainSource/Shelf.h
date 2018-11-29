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
        vector<Cell> cells; 
        pair<double,double> bottomLeftCoords;
        string blockName;
        int columns;
        int lines; 
        double cellLenght;
        double cellWidth; 
        
        
    public:
        Shelf();
        Shelf(Shelf &other){
            for(unsigned int i=0; i <other.cells.size(); i++)
                this->cells.push_back(Cell(other.cells[i])); 
        }
        
        Shelf(vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName, 
              int columns, int lines, double cellLenght, double cellWidth){
                  
            for(int i=0;i<cells.size(); i++)
                this->cells.push_back(cells[i]);
            
            this->bottomLeftCoords = bottomLeftCoords;
            this->blockName = blockName;
            this->columns = columns;
            this->lines = lines;
            this->cellLenght = cellLenght;
            this->cellWidth = cellWidth; 
        }
         
        double getBottomLeftCoordX() { return bottomLeftCoord.first; }
        double getBottomLeftCoordY() { return bottomLeftCoord.second; }
        double getBottomLeftCoords() { return bottomLeftCoords; }
        
};