#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include"Cell.h"
using namespace std;

/**
 * Copy constructor
 */
Cell::Cell(const Cell & other){
    this->code = other.code;
    this->idShelf = other.idShelf;
    this->row = other.row;
    this->column = other.column;
    this->levels = other.levels;
}

Cell::Cell(string code, long int IdShelf,int levels, int row, int column){
    this->code = code;
    this->idShelf = IdShelf;
    this->row = row;
    this->column = column;
    this->levels = levels;
}

bool Cell::operator==(const Cell & other) const{
    return code == other.code && idShelf == other.idShelf && row == other.row && column == other.column && levels == other.levels;
}

bool Cell::operator<=(const Cell & other) const{
    if(*this == other)
        return true; 

    if(this->code < other.code)                         //Code <
        return true;
    else if(this->code == other.code){                  //Code ==
        if(this->idShelf < other.idShelf)                  //Shelf <
            return true;
        else if(this->idShelf == other.idShelf){        //Shelf ==
            if(this->row < other.row)                   //Row <
                return true;
            else if(this->row == other.row){            //Row == 
                if(this->column < other.column){
                    return true; 
                }else if(this->column == other.column){
                    return this->levels <= other.levels; 
                }else                                   // Else column
                    return false;                       
            }else                                       // Else row
                return false;                           
        }else                                           // Else Shelf
            return false;
    }else                                               // Else Code
        return false;

}

bool Cell::operator<(const Cell & other) const{
    return *this == other ? false: *this <= other; 
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
long int Cell::getIdShelf() const { return idShelf;}
int Cell::getRow() const { return row;}
int Cell::getColumn() const { return column; }
int Cell::getLevels() const { return levels; }

void Cell::printCellInformation(){ 

	cout<<"_____________________________\n";
	cout<<"Cell code: \t"<<this->code<<"\tCell shelf: \t"<<this->idShelf<<endl;
	cout<<"Row: \t"<<this->row<<"\tColumn: "<<this->column<<"\tNumber of Levels: \t"<<this->levels<<endl;
	cout<<"_____________________________\n"<<endl;
}