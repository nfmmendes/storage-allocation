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
using namespace std;

/**
 * @brief The class ProductAllocationProhibition handles data about the positions
 * in which the products cannot be allocated.  
 */
class ProductAllocationProhibitions{
    private:
        Product product;						    ///< Product to be allocated 
        std::vector<Shelf> forbiddenShelves;		///< Shelves where the product can not be stored
        std::vector<Cell> forbiddenCells;			///< Shelves where the product can not be stored 
        std::vector<Block> forbiddenBlocks;			///< Blocks where the product can not be stored 
        static void recoverWarehouseData(Warehouse &warehouse,std::map<std::string, Cell> & cellsByCode, 
                                        std::map<long int, Shelf> &shelvesById, std::map<std::string, Block> & blocksByName);
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
        ProductAllocationProhibitions(Product &product, std::vector<Shelf>forbiddenShelves, std::vector<Cell> forbiddenCells, 
                                     std::vector<Block> &blocks);
    
        /**
         * @brief Set the product with an allocation prohibition.
         * @param other The product.
         */ 
        void setProduct(Product & other);

        /**
         * @brief Set the forbidden shelves. 
         * @param others The list of forbiddend shelves.
         */
        void setForbiddenShelves(std::vector<Shelf> & others);

        /**
         * @brief Set the forbidden cells.
         * @param others The list of fobrbidden cells. 
         */
        void setForbiddenCells(std::vector<Cell> &others);

        /**
         * @brief Set the forbidden blocks. 
         * @param others The list of forbidden blocks. 
         */
        void setForbiddenBlocks(std::vector<Block> &others);
    
        /**
         * @brief Get the product with an allocation prohibition.
         * @return The product with an allocation prohibition.
         */
        Product getProduct() const; 
        
        /**
         * @brief Get the list of forbidden shelves. 
         * @return The list of forbidden shelves. 
         */
        std::vector<Shelf> & getForbiddenShelves();

        /**
         * @brief Get the list of forbidden cells. 
         * @return THe list of forbidden cells.
         */
        std::vector<Cell> & getForbiddenCells();

        /**
         * @brief Get the list of forbidden blocks.
         * @return The list of forbidden blocks. 
         */
        std::vector<Block> & getForbiddenBlocks();
        
        /**
         * @brief Read prohibition data from a file. 
         * @param fileName The file name.
         * @return A list containing all the prohibitions. 
         */
        static std::vector<ProductAllocationProhibitions> readAllProhibitionsData(std::ifstream &fileName);
		
        /**
		 * @brief Assignment operator override. 
		 * @param other The operator right side object. 
		 * @return A reference to the modified object.
         */
		ProductAllocationProhibitions & operator=(const ProductAllocationProhibitions &other); 
};
