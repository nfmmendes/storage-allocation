#pragma once

#include<iostream>

/**
 * The <c> Cell </c> class defines a cell in a shelf warehouse
 * without refering to the products stored on it
 */
class Cell{

    private: 
        std::string code;		///< Cell code 
        long int idShelf;	///< Id of shelf where the cell is located 
        int row;			///< Row on shelf where the cell is located 
        int column; 		///< Column on shelf where the cell is located 
        int levels;         ///< Vertical sub-division
  
    public:
        /**
         * @brief Constructor.
         */
        Cell(){}

        /**
         * @brief Copy constructor. 
         * @param other The object to be copied. 
         */
        Cell(const Cell & other);
        
        /**
         * @brief Member constructor 
         * @param code    Cell code 
         * @param idShelf Id of the shelf where the cell is  
         * @param levels  Number of vertical divisions of the cell
         * @param row 	  The shelf row where the cell is
         * @param column  The column row where the cell is 
         */
        Cell(std::string code, long int IdShelf,int levels, int row, int column);
        
        /**
         * @brief The equality operator override. 
         * @param other The right hand side object.
         * @return True if the objects are considered equals. False otherwise.
         */
        bool operator==(const Cell & other) const;
        
        /**
         * @brief The less than or equal operator override. 
         * @param other The right hand side object.
         * @return True if the left side hand object is considered to be lower than
         *          or equal to the right hand side object. False otwerwise
         */
        bool operator<=(const Cell & other) const;

        /**
         * @brief The less thanoperator override. 
         * @param other The right hand side object.
         * @return True if the left side hand object is considered to be lower than
         *         the right hand side object. False otwerwise
         */
        bool operator<(const Cell & other) const;

        /**
         * @brief The assignment operator override. 
         * @param other The right hand side object.
         * @return A reference to the modified left side hand object. 
         */
		Cell & operator=(const Cell & other); 
        
        /**
         * @brief Get the cell code.
         * @return The cell code.
         */
        std::string getCode()const;
        
        /**
         * @brief Get the cell shelf id.
         * @return The cell shelf id.
         */
        long int getIdShelf()const;
        
        /**
         * @brief Get the cell row index.
         * @return The cell row index.
         */
        int getRow() const;
        
        /**
         * @brief Get the cell column index.
         * @return The cell column index.
         */
        int getColumn() const;
        
        /**
         * @brief Get the cell number of levels.
         * @return The cell number of levels.
         */
        int getLevels() const;
		
        /**
         * @brief Print cell information. 
         */
		void printCellInformation();
};
