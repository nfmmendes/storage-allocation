#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Cell.h"
#include "Shelf.h"

/**
 *	Default constructor 
 */
Shelf::Shelf(){}

/**
 *	Copy constructor 
 */
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

/**
 *	Member constructor
 */
Shelf::Shelf(long int Id, const std::vector<Cell>& cells, const std::pair<double, double>& bottomLeftCoords, std::string blockName,
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
const std::pair<double,double>& Shelf::getBottomLeftCoords() const { return bottomLeftCoords; }
const std::vector<Cell>& Shelf::getCells(){ return cells;}
const std::string& Shelf::getBlockName() const{ return blockName; }
int Shelf::getNumColumns() const { return columns;}
int Shelf::getNumRows() const { return rows;}
double Shelf::getCellLength()const { return cellLength;}
double Shelf::getCellWidth()const { return cellWidth;}

void Shelf::setBottomLeftCoordX(double value) { this->bottomLeftCoords.first = value; }
void Shelf::setBottomLeftCoordY(double value) { this->bottomLeftCoords.second = value; }
void Shelf::setBottomLeftCoords(std::pair<double, double> value ) { this->bottomLeftCoords = value;}
void Shelf::setCells(std::vector<Cell> &cells){ this->cells = cells;}
void Shelf::setBlockName(std::string name){ this->blockName = name;}
void Shelf::setNumColumns(int value){ if(value > 0) columns = value; }
void Shelf::setNumRows(int value){ if(value > 0) rows = value; }
void Shelf::setCellLength(double value){ if(value>0) cellLength = value;}
void Shelf::setCellWidth(double value){ if(value >0) cellWidth = value; }

void Shelf::printShelfInformation(){
	std::cout<<"_________________________\n";
	std::cout<<"Shelf: \t" << this->Id  <<"\tBlock name: \t"<<this->blockName<<std::endl;
	std::cout<<"Bottom-left coord: \t(x="<<this->bottomLeftCoords.first<<",y="<<this->bottomLeftCoords.second<<")"<<std::endl; 
	std::cout<<"Number of rows: \t"<<this->rows<<"\tNumber of columns: \t"<<this->columns<<std::endl;
	std::cout<<"Cell width: \t"<<this->cellWidth<<"\tCell length: \t"<<this->cellLength<<std::endl<<std::endl;
	
	for(unsigned int i=0;i<this->cells.size();i++)
		this->cells[i].printCellInformation();
	std::cout<<"_________________________\n";
}

int Shelf::getNumberOfAvailablePositions(){
	int total = 0;
	for(unsigned int i=0;i<cells.size();i++)
		total+= cells[i].getLevels();
	
	return total; 
}

/**
 *	Less than operator overload (Binary operator) 
 *	The shelves are compared first by id, after by number of rows, columns and finally position
 *  @param other Shelf on the right hand side of the operator
 */
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

/**
 *	Equals operator overload 
 *  @param other The shelf on the right hand of the operator 
 */
bool Shelf::operator==(const Shelf &other)const{
	return this->Id == other.Id && this->columns==other.columns && this->rows == other.rows && this->bottomLeftCoords == other.bottomLeftCoords &&
		   this->blockName == other.blockName && this->cellLength == other.cellLength && this->cellWidth == other.cellWidth; 

}

/**
 *	Not equals operator overload 
 *  @param other The shelf on the right hand of the operator
 */
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