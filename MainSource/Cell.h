#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 

///This class defines a cell in a shelf warehouse
///without refering to the products stored on it
class Cell{

    private: 
        string code;
        long int idShelf;
        int row;
        int column; 
        int levels;         //<! vertical sub-division
  
    public:
        Cell(){
            
        }
        Cell(const Cell & other){
            this->code = other.code;
            this->idShelf = other.idShelf;
            this->row = other.row;
            this->column = other.column;
            this->levels = other.levels;
        }
    
        Cell(string code, long int IdShelf, int row, int column, int levels){
            this->code = code;
            this->idShelf = IdShelf;
            this->row = row;
            this->column = column;
            this->levels = levels;
        }
    
        void setCode(string value){ this->code = value;}
        void setIdShelf(long int value ){ if(value >= 0) this->idShelf = value;}
        void setRow(int value){ if(value >= 0)this->row = value; }
        void setColumn(int value) { if(value >=0) this->column = value;}
        void setLevels(int value){ if(value > 0) this->levels = value; }
    
        string getCode(){ return code;}
        long int getIdShelf() { return idShelf;}
        int getRow(){ return row;}
        int getColumn() { return column; }
        int getLevels() { return levels; }
};

#endif
