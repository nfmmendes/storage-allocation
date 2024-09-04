#pragma once

#include<iostream>

///This class defines a cell in a shelf warehouse
///without refering to the products stored on it
class Cell{

    private: 
        std::string code;		///< Cell code 
        long int idShelf;	///< Id of shelf where the cell is located 
        int row;			///< Row on shelf where the cell is located 
        int column; 		///< Column on shelf where the cell is located 
        int levels;         ///< Vertical sub-division
  
    public:
        Cell(){}
        Cell(const Cell & other);
        
        Cell(std::string code, long int IdShelf,int levels, int row, int column);
        
        bool operator==(const Cell & other) const;
        bool operator<=(const Cell & other) const;
        bool operator<(const Cell & other) const;
		Cell & operator=(const Cell & other); 
        
        std::string getCode()const;
        long int getIdShelf()const;
        int getRow() const;
        int getColumn() const;
        int getLevels() const;
		
		void printCellInformation();
};
