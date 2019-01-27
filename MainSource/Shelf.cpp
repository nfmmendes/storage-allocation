#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Cell.h"
#include "Shelf.h"
using namespace std;


Shelf::Shelf(){}
Shelf::Shelf(const Shelf &other){
    for(unsigned int i=0; i <other.cells.size(); i++){
        Cell inserted(other.cells[i]);
        this->cells.push_back(inserted);
    }
    
    this->Id = other.Id;
    this->bottomLeftCoords = other.bottomLeftCoords;
    this->blockName = other.blockName;
    this->columns = other.columns;
    this->rows = other.rows;
    this->cellLength = other.cellLength;
    this->cellWidth = other.cellWidth;
}

Shelf::Shelf(long int Id,vector<Cell> cells, pair<double, double> bottomLeftCoords, string blockName,
      int columns, int rows, double cellLength, double cellWidth){
    
    for(unsigned int i=0;i<cells.size(); i++){
        Cell inserted(cells[i]);
        this->cells.push_back(inserted);
    }
    
    this->Id = Id;
    this->bottomLeftCoords = bottomLeftCoords;
    this->blockName = blockName;
    this->columns = columns;
    this->rows = rows;
    this->cellLength = cellLength;
    this->cellWidth = cellWidth;
}

long int Shelf::getId(){ return Id;}
double Shelf::getBottomLeftCoordX() const { return bottomLeftCoords.first; }
double Shelf::getBottomLeftCoordY() const { return bottomLeftCoords.second; }
pair<double,double> Shelf::getBottomLeftCoords() const { return bottomLeftCoords; }
vector<Cell> Shelf::getCells(){ return cells;}
string Shelf::getBlockName(){ return blockName; }
int Shelf::getNumColumns() const { return columns;}
int Shelf::getNumRows() const { return rows;}
double Shelf::getCellLength()const { return cellLength;}
double Shelf::getCellWidth()const { return cellWidth;}

void Shelf::setBottomLeftCoordX(double value) { this->bottomLeftCoords.first = value; }
void Shelf::setBottomLeftCoordY(double value) { this->bottomLeftCoords.second = value; }
void Shelf::setBottomLeftCoords(pair<double, double> value ) { this->bottomLeftCoords = value;}
void Shelf::setCells(vector<Cell> &cells){ this->cells = cells;}
void Shelf::setBlockName(string name){ this->blockName = name;}
void Shelf::setNumColumns(int value){ if(value > 0) columns = value; }
void Shelf::setNumRows(int value){ if(value > 0) rows = value; }
void Shelf::setCellLength(double value){ if(value>0) cellLength = value;}
void Shelf::setCellWidth(double value){ if(value >0) cellWidth = value; }
