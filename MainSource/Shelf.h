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
        Shelf(const Shelf &other){
            for(unsigned int i=0; i <other.cells.size(); i++){
                Cell inserted(other.cells[i]);
                this->cells.push_back(inserted); 
            }
        }
        
        Shelf(vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName, 
              int columns, int lines, double cellLenght, double cellWidth){
                  
            for(unsigned int i=0;i<cells.size(); i++){
                Cell inserted(cells[i]);
                this->cells.push_back(inserted);
            }
            
            this->bottomLeftCoords = bottomLeftCoords;
            this->blockName = blockName;
            this->columns = columns;
            this->lines = lines;
            this->cellLenght = cellLenght;
            this->cellWidth = cellWidth; 
        }
         
        double getBottomLeftCoordX() { return bottomLeftCoords.first; }
        double getBottomLeftCoordY() { return bottomLeftCoords.second; }
        pair<double,double> getBottomLeftCoords() { return bottomLeftCoords; }
        
};