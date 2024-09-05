#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include"Cell.h"
using namespace std;

Cell::Cell(const Cell & other){
    this->code = other.code;
    this->idShelf = other.idShelf;
    this->row = other.row;
    this->column = other.column;
    this->levels = other.levels;
}

Cell::Cell(string code, unsigned long int IdShelf, unsigned short levels, unsigned short row, unsigned short column){
    this->code = code;
    this->idShelf = IdShelf;
    this->row = row;
    this->column = column;
    this->levels = levels;
}

bool Cell::operator==(const Cell & other) const {
    return code == other.code && idShelf == other.idShelf && row == other.row && column == other.column && levels == other.levels;
}

bool Cell::operator<(const Cell & other) const {
    if(this->code > other.code)
        return false;
    if(this->code < other.code)                    
        return true;
    
    // Same code.
    if(this->idShelf > other.idShelf)          
        return false;               
    if(this->idShelf < other.idShelf)          
        return true;
    
    // Same code and shelf.
    if(this->row > other.row)
        return false;        
    if(this->row < other.row)              
        return true;
    
    // Same code, shelf and row.
    if(this->column > other.column)
        return false;          
    if(this->column < other.column)
        return true; 

    // Same code, shelf, row and column.
    return this->levels < other.levels;     
}


Cell & Cell::operator=(const Cell &other){
	this->code = other.code;
    this->idShelf = other.idShelf;
    this->row = other.row;
    this->column = other.column;
    this->levels = other.levels;
	
	return *this;
}

string Cell::getCode() const{ return code;}
unsigned long int Cell::getIdShelf() const { return idShelf;}
unsigned short Cell::getRow() const { return row;}
unsigned short Cell::getColumn() const { return column; }
unsigned short Cell::getLevels() const { return levels; }

void Cell::printCellInformation(){ 

	cout<<"_____________________________\n";
	cout<<"Cell code: \t"<<this->code<<"\tCell shelf: \t"<<this->idShelf<<endl;
	cout<<"Row: \t"<<this->row<<"\tColumn: "<<this->column<<"\tNumber of Levels: \t"<<this->levels<<endl;
	cout<<"_____________________________\n"<<endl;
}