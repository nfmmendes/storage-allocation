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
        string code;		///< Cell code 
        long int idShelf;	///< Id of shelf where the cell is located 
        int row;			///< Row on shelf where the cell is located 
        int column; 		///< Column on shelf where the cell is located 
        int levels;         ///< Vertical sub-division
  
    public:
        Cell(){
            
        }
        Cell(const Cell & other);
        
        Cell(string code, long int IdShelf,int levels, int row, int column);
        
        bool operator==(const Cell & other) const;
        bool operator<=(const Cell & other) const;
        bool operator<(const Cell & other) const;
		Cell & operator=(const Cell & other); 

        void setCode(string value);
        void setIdShelf(long int value );
        void setRow(int value);
        void setColumn(int value);
        void setLevels(int value);
        
        string getCode()const;
        long int getIdShelf()const;
        int getRow() const;
        int getColumn() const;
        int getLevels() const;
		
		void printCellInformation();
};

#endif
