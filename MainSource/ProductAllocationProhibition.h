#ifndef PRODUCT_ALLOCATION_PROHIBITIONS_H
#define PRODUCT_ALLOCATION_PROHIBITIONS_H

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
#include<utility>
#include "Product.h"
#include "Shelf.h"
#include "Block.h"
#include "Cell.h"
using namespace std;



class ProductAllocationProhibitions{
    private:
        Product product;
        vector<Shelf> forbiddenShelves;
        vector<Cell> forbiddenCells;
        vector<Block> forbiddenBlocks;
    public:
        ProductAllocationProhibitions();
        ProductAllocationProhibitions(const ProductAllocationProhibitions &other);
        ProductAllocationProhibitions(Product &product,vector<Shelf>forbiddenShelves,vector<Cell> forbiddenCells,vector<Block> &block);
    
        void setProduct(Product & other){ this->product = other; }
        void setForbiddenShelves(vector<Shelf> & others){ return this->forbiddenShelves = others; }
        void setForbiddenCells(vector<Cell> &others){ return this->forbiddenCells = others; }
        void setForbiddenBlocks(vector<Block> &others) { return this->forbiddenBlocks = other; }
    
        Product getProduct(){   return this->product;}
        vector<Shelf> getForbiddenShelves(){ return this->forbiddenShelves;}
        vector<Cell> getForbiddenCells(){ return this->forbiddenCells; }
        vector<Block> getForbiddenBlocks() { return this->forbiddenBlocks; }
    
        void addProhibition(Product &product, Cell &cell);
        void addProhibition(Product &product, Shelf &shelf);
        void addProhibition(Product &product, Block &);
    
        void removeProductCellProhibition(int i){
            if(i>=0 && i<(int)forbiddenCells.size())
                this->forbiddenCells.erase(this->forbiddenCells.begin()+i);
        }
    
        void removeProductShelfProhibition(int i){
            if(i>=0 && i<(int)forbiddenShelves.size())
                this->forbiddenShelves.erase(this->forbiddenShelves.begin()+i);
        }
    
        void removeProductBlockProhibition(int i){
            if(i>=0 && i<(int)forbiddenBlocks.size())
                this->forbiddenBlocks.erase(this->forbiddenBlocks.begin()+i);
        }
    
        void removeProductProhibitions(Product &product){
            
        }
};

#endif /* PROHIBITION_H */
