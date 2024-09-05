#pragma once

#include<iostream>
using std::string;

/**
 * The <c> Cell </c> class defines a cell in a shelf warehouse
 * without refering to the products stored on it
 */
class Cell{

    private: 
        string code {}; 		            ///< Cell code 
        unsigned long int idShelf {};	    ///< Id of shelf where the cell is located 
        unsigned short row { 0 };			///< Row on shelf where the cell is located 
        unsigned short column { 0 }; 		///< Column on shelf where the cell is located 
        unsigned short levels { 1 };        ///< Vertical sub-division
  
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
        Cell(string code, unsigned long int IdShelf, unsigned short levels, unsigned short row, unsigned short column);
        
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
        string getCode()const;
        
        /**
         * @brief Get the cell shelf id.
         * @return The cell shelf id.
         */
        unsigned long int getIdShelf()const;
        
        /**
         * @brief Get the cell row index.
         * @return The cell row index.
         */
        unsigned short getRow() const;
        
        /**
         * @brief Get the cell column index.
         * @return The cell column index.
         */
        unsigned short getColumn() const;
        
        /**
         * @brief Get the cell number of levels.
         * @return The cell number of levels.
         */
        unsigned short getLevels() const;
		
        /**
         * @brief Print cell information. 
         */
		void printCellInformation();
};
