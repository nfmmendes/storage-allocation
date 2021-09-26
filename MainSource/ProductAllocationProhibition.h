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



class ProductAllocationProhibitions{
    private:
        Product product;						///< Product to be allocated 
        std::vector<Shelf> forbiddenShelves;			///< Shelves where the product can not be stored
        std::vector<Cell> forbiddenCells;			///< Shelves where the product can not be stored 
        std::vector<Block> forbiddenBlocks;			///< Blocks where the product can not be stored 
        static void recoverWarehouseData(Warehouse &warehouse,std::map<std::string, Cell> & cellsByCode, 
                                        std::map<long int, Shelf> &shelvesById, std::map<std::string, Block> & blocksByName);
    public:
        ProductAllocationProhibitions();
        ProductAllocationProhibitions(const ProductAllocationProhibitions &other);
        ProductAllocationProhibitions(Product &product, std::vector<Shelf>forbiddenShelves, std::vector<Cell> forbiddenCells, 
                                     std::vector<Block> &block);
    
        void setProduct(Product & other);
        void setForbiddenShelves(std::vector<Shelf> & others);
        void setForbiddenCells(std::vector<Cell> &others);
        void setForbiddenBlocks(std::vector<Block> &others);
    
        Product getProduct() const; 
        std::vector<Shelf> getForbiddenShelves();
        std::vector<Cell> getForbiddenCells();
        std::vector<Block> getForbiddenBlocks();
    
        void addProhibition(Cell &cell);
        void addProhibition(Shelf &shelf);
        void addProhibition(Block &);
    
        void removeProductCellProhibition(int i);
    
        void removeProductShelfProhibition(int i);
    
        void removeProductBlockProhibition(int i);
    
        static std::vector<ProductAllocationProhibitions> readAllProhibitionsData(std::ifstream &fileName);
		
		ProductAllocationProhibitions & operator=(const ProductAllocationProhibitions &other); 
};
