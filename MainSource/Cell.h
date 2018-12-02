#ifndef CELL_H
#define CELL_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 

class Cell{

    private: 
        string code;
        long int idShelf;
        int row;
        int column; 
        int levels; 
  
    public:
        Cell();
        Cell(const Cell & other);
        Cell(string code, long int IdShelf, int row, int column, int levels); 
};

#endif