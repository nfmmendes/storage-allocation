#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include "Warehouse.h"
#include "Product.h"
#include "Shelf.h"
#include "Block.h"
#include "Cell.h"
using std::vector; 
using std::map;

/**
 * @brief The class ProductAllocationProhibition handles data about the positions
 * in which the products cannot be allocated.  
 */
class ProductAllocationProhibitions{
    private:
        Product product;						    ///< Product to be allocated 
        vector<Shelf> forbiddenShelves;		///< Shelves where the product can not be stored
        vector<Cell> forbiddenCells;			///< Shelves where the product can not be stored 
        vector<Block> forbiddenBlocks;			///< Blocks where the product can not be stored 
        static void recoverWarehouseData(Warehouse &warehouse,map<string, Cell> & cellsByCode, 
                                        map<long int, Shelf> &shelvesById, map<string, Block> & blocksByName);
    public:
        /**
         * @brief Constructor.
         */
        ProductAllocationProhibitions();

        /**
         * @brief Copy constructor. 
         * @param other The object to be copied. 
         */
        ProductAllocationProhibitions(const ProductAllocationProhibitions &other);

        /**
         * @brief Constructor. 
         * @param product The product with an allocation prohibition. 
         * @param forbiddenShelves The list of forbidden shelves.
         * @param forbiddenCells The list of forbidden cells.
         * @param block The list of blocks.
         */
        ProductAllocationProhibitions(const Product &product, const vector<Shelf>& forbiddenShelves, const vector<Cell>& forbiddenCells, 
                                     const vector<Block> &blocks);
    
        /**
         * @brief Set the product with an allocation prohibition.
         * @param other The product.
         */ 
        void setProduct(const Product & other);

        /**
         * @brief Set the forbidden shelves. 
         * @param others The list of forbiddend shelves.
         */
        void setForbiddenShelves(const vector<Shelf> & others);

        /**
         * @brief Set the forbidden cells.
         * @param others The list of fobrbidden cells. 
         */
        void setForbiddenCells(const vector<Cell> &others);

        /**
         * @brief Set the forbidden blocks. 
         * @param others The list of forbidden blocks. 
         */
        void setForbiddenBlocks(const vector<Block> &others);
    
        /**
         * @brief Get the product with an allocation prohibition.
         * @return The product with an allocation prohibition.
         */
        const Product& getProduct() const; 
        
        /**
         * @brief Get the list of forbidden shelves. 
         * @return The list of forbidden shelves. 
         */
        const vector<Shelf>& getForbiddenShelves() const;

        /**
         * @brief Get the list of forbidden cells. 
         * @return THe list of forbidden cells.
         */
        const vector<Cell>& getForbiddenCells() const;

        /**
         * @brief Get the list of forbidden blocks.
         * @return The list of forbidden blocks. 
         */
        const vector<Block>& getForbiddenBlocks() const;
        
        /**
         * @brief Read prohibition data from a file. 
         * @param fileName The file name.
         * @return A list containing all the prohibitions. 
         */
        static vector<ProductAllocationProhibitions> readAllProhibitionsData(ifstream &fileName);
		
        /**
		 * @brief Assignment operator override. 
		 * @param other The operator right side object. 
		 * @return A reference to the modified object.
         */
		const ProductAllocationProhibitions& operator=(const ProductAllocationProhibitions &other); 
};
