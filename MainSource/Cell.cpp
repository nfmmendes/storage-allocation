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

Cell::Cell(string code, long int IdShelf,int levels, int row, int column){
    this->code = code;
    this->idShelf = IdShelf;
    this->row = row;
    this->column = column;
    this->levels = levels;
}

bool Cell::operator==(Cell & other) const{
    return code == other.code && idShelf == other.idShelf && row == other.row && column == other.column && levels == other.levels;
}

void Cell::setCode(string value){ this->code = value;}
void Cell::setIdShelf(long int value ){ if(value >= 0) this->idShelf = value;}
void Cell::setRow(int value){ if(value >= 0)this->row = value; }
void Cell::setColumn(int value) { if(value >=0) this->column = value;}
void Cell::setLevels(int value){ if(value > 0) this->levels = value; }

string Cell::getCode(){ return code;}
long int Cell::getIdShelf() { return idShelf;}
int Cell::getRow(){ return row;}
int Cell::getColumn() { return column; }
int Cell::getLevels() { return levels; }
