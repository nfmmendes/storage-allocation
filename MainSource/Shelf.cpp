#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Cell.h"
#include "Shelf.h"
using std::vector;
using std::cout;
using std::pair;
using std::endl;

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

Shelf::Shelf(long int Id, const vector<Cell>& cells, const pair<double, double>& bottomLeftCoords, string blockName,
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

long int Shelf::getId() const { return Id;}
double Shelf::getBottomLeftCoordX() const { return bottomLeftCoords.first; }
double Shelf::getBottomLeftCoordY() const { return bottomLeftCoords.second; }
const pair<double,double>& Shelf::getBottomLeftCoords() const { return bottomLeftCoords; }
const vector<Cell>& Shelf::getCells(){ return cells;}
const string& Shelf::getBlockName() const{ return blockName; }
int Shelf::getNumColumns() const { return columns;}
int Shelf::getNumRows() const { return rows;}
double Shelf::getCellLength()const { return cellLength;}
double Shelf::getCellWidth()const { return cellWidth;}

void Shelf::setCells(vector<Cell> &cells){ this->cells = cells;}

void Shelf::printShelfInformation(){
	cout<<"_________________________\n";
	cout<<"Shelf: \t" << this->Id  <<"\tBlock name: \t"<<this->blockName<<endl;
	cout<<"Bottom-left coord: \t(x="<<this->bottomLeftCoords.first<<",y="<<this->bottomLeftCoords.second<<")"<<endl; 
	cout<<"Number of rows: \t"<<this->rows<<"\tNumber of columns: \t"<<this->columns<<endl;
	cout<<"Cell width: \t"<<this->cellWidth<<"\tCell length: \t"<<this->cellLength<<endl<<endl;
	
	for(unsigned int i=0;i<this->cells.size();i++)
		this->cells[i].printCellInformation();
	cout<<"_________________________\n";
}

int Shelf::getNumberOfAvailablePositions(){
	int total = 0;
	for(unsigned int i=0;i<cells.size();i++)
		total+= cells[i].getLevels();
	
	return total; 
}

bool Shelf::operator<(const Shelf &other)const{
	if(this->Id > other.Id)
		return false;
	else if(this->Id < other.Id)
		return true; 
	
	if(this->columns*this->rows > other.columns*other.rows)
		return false; 
	else if(this->columns*this->rows < other.columns*other.rows)
		return true; 
	
	return this->bottomLeftCoords< other.bottomLeftCoords; 
}

bool Shelf::operator==(const Shelf &other)const{
	return this->Id == other.Id && this->columns==other.columns && this->rows == other.rows && this->bottomLeftCoords == other.bottomLeftCoords &&
		   this->blockName == other.blockName && this->cellLength == other.cellLength && this->cellWidth == other.cellWidth; 

}

bool Shelf::operator!=(const Shelf &other)const{
	return !(*this == other); 	
}

Shelf & Shelf::operator=(const Shelf &other){
	this->cells.clear();
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
	
	return *this;
}