#ifndef PRODUCT_ALLOCATION_PROHIBITIONS_H
#define PRODUCT_ALLOCATION_PROHIBITIONS_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include "Warehouse.h"
#include "Product.h"
#include "Shelf.h"
#include "Block.h"
#include "Cell.h"
using namespace std;



class ProductAllocationProhibitions{
    private:
        Product product;						///< Product to be allocated 
        vector<Shelf> forbiddenShelves;			///< Shelves where the product can not be stored
        vector<Cell> forbiddenCells;			///< Shelves where the product can not be stored 
        vector<Block> forbiddenBlocks;			///< Blocks where the product can not be stored 
        static void recoverWarehouseData(const Warehouse warehouse,map<string, Cell> & cellsByCode, map<long int, Shelf> &shelvesById, map<string, Block> & blocksByName);
    public:
        ProductAllocationProhibitions();
        ProductAllocationProhibitions(const ProductAllocationProhibitions &other);
        ProductAllocationProhibitions(Product &product,vector<Shelf>forbiddenShelves,vector<Cell> forbiddenCells,vector<Block> &block);
    
        void setProduct(Product & other);
        void setForbiddenShelves(vector<Shelf> & others);
        void setForbiddenCells(vector<Cell> &others);
        void setForbiddenBlocks(vector<Block> &others);
    
        Product getProduct() const; 
        vector<Shelf> getForbiddenShelves();
        vector<Cell> getForbiddenCells();
        vector<Block> getForbiddenBlocks();
    
        void addProhibition(Cell &cell);
        void addProhibition(Shelf &shelf);
        void addProhibition(Block &);
    
        void removeProductCellProhibition(int i);
    
        void removeProductShelfProhibition(int i);
    
        void removeProductBlockProhibition(int i);
    
        static vector<ProductAllocationProhibitions> readAllProhibitionsData(ifstream &fileName);
		
		ProductAllocationProhibitions & operator=(const ProductAllocationProhibitions &other); 
};

#endif /* PROHIBITION_H */
