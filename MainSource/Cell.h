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
        Cell(const Cell & other);
        
        Cell(string code, long int IdShelf,int levels, int row, int column);
        
        bool operator==(Cell & other) const;
        
        void setCode(string value);
        void setIdShelf(long int value );
        void setRow(int value);
        void setColumn(int value);
        void setLevels(int value);
        
        string getCode();
        long int getIdShelf();
        int getRow();
        int getColumn();
        int getLevels();
};

#endif
