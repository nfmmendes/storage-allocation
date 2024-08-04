#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include "InputData.h"
#include "ProductAllocationProhibition.h"
using namespace std;

ProductAllocationProhibitions::ProductAllocationProhibitions(){
    
}

ProductAllocationProhibitions::ProductAllocationProhibitions(const ProductAllocationProhibitions &other){
    this->product = other.product;
    
    copy(begin(other.forbiddenCells), end(other.forbiddenCells), back_inserter(this->forbiddenCells));
    copy(begin(other.forbiddenShelves), end(other.forbiddenShelves), back_inserter(this->forbiddenShelves));
    copy(begin(other.forbiddenBlocks), end(other.forbiddenBlocks), back_inserter(this->forbiddenBlocks));
}

ProductAllocationProhibitions & ProductAllocationProhibitions::operator=(const ProductAllocationProhibitions &other){
    this->product = other.product;
    
	this->forbiddenCells.clear();
	this->forbiddenShelves.clear();    
	this->forbiddenBlocks.clear();

    copy(begin(other.forbiddenCells), end(other.forbiddenCells), back_inserter(this->forbiddenCells));
    copy(begin(other.forbiddenShelves), end(other.forbiddenShelves), back_inserter(this->forbiddenShelves));
    copy(begin(other.forbiddenBlocks), end(other.forbiddenBlocks), back_inserter(this->forbiddenBlocks));
	
	return *this;
}

ProductAllocationProhibitions::ProductAllocationProhibitions(Product &product,vector<Shelf>forbiddenShelves,vector<Cell> forbiddenCells,vector<Block> &blocks){
    
	this->product = product; 
	
	for(unsigned int i=0; i<forbiddenCells.size(); i++)
        this->forbiddenCells.push_back(forbiddenCells[i]);
    
    for(unsigned int i=0; i<forbiddenShelves.size(); i++)
        this->forbiddenShelves.push_back(forbiddenShelves[i]);
    
    for(unsigned int i=0; i<blocks.size(); i++)
        this->forbiddenBlocks.push_back(blocks[i]);
}

void ProductAllocationProhibitions::setProduct(Product & other){ this->product = other; }
void ProductAllocationProhibitions::setForbiddenShelves(vector<Shelf> & others){  this->forbiddenShelves = others; }
void ProductAllocationProhibitions::setForbiddenCells(vector<Cell> &others){  this->forbiddenCells = others; }
void ProductAllocationProhibitions::setForbiddenBlocks(vector<Block> &others) {  this->forbiddenBlocks = others; }

Product ProductAllocationProhibitions::getProduct() const{   return this->product;}
vector<Shelf> & ProductAllocationProhibitions::getForbiddenShelves(){ return this->forbiddenShelves;}
vector<Cell> & ProductAllocationProhibitions::getForbiddenCells(){ return this->forbiddenCells; }
vector<Block> & ProductAllocationProhibitions::getForbiddenBlocks() { return this->forbiddenBlocks; }

/**
 *	Adds a cell to the pool of forbidden cells 
 *  @param cell Cell to be inserted 
 */ 
void ProductAllocationProhibitions::addProhibition(Cell &cell){
    this->forbiddenCells.push_back(cell);
}

/**
 *	Adds a shelf to the pool of forbidden shelves
 *  @param shelf Shelf to be inserted  
 */
void ProductAllocationProhibitions::addProhibition(Shelf &shelf){
    this->forbiddenShelves.push_back(shelf);
}


/**
 *	Adds a block to the pool of forbidden blocks 
 *  @param block Block to be inserted 
 */
void ProductAllocationProhibitions::addProhibition(Block &block){
    this->forbiddenBlocks.push_back(block);
}

/**
 *	Remove the i-esime cell from the pool of forbidden cells 
 *  @param i Cell index 
 */
void ProductAllocationProhibitions::removeProductCellProhibition(int i){
    if(i>=0 && i<(int)forbiddenCells.size())
        this->forbiddenCells.erase(this->forbiddenCells.begin()+i);
}

/**
 *	Remove the i-esime shelf from the pool of forbidden shelves
 *  @param i Shelf index  
 */
void ProductAllocationProhibitions::removeProductShelfProhibition(int i){
    if(i>=0 && i<(int)forbiddenShelves.size())
        this->forbiddenShelves.erase(this->forbiddenShelves.begin()+i);
}

void ProductAllocationProhibitions::removeProductBlockProhibition(int i){
    if(i>=0 && i<(int)forbiddenBlocks.size())
        this->forbiddenBlocks.erase(this->forbiddenBlocks.begin()+i);
}

/**
 *	Read all the data concerning to individual product storage prohibitions 
 *  @param file File stream object that references the file where the data is stored 
 */
vector<ProductAllocationProhibitions> ProductAllocationProhibitions::readAllProhibitionsData(ifstream &file){
    vector<ProductAllocationProhibitions> prohibitions;
    long int idShelve;
	string productCode;
    string cellCode, blockName;
    int numProhibitions,numCellProhibitions, numShelvesProhibitions, numBlocksProhibitions;
    
    InputData input;
    
    //Recovering the data about the warehouse and products
    Warehouse warehouse = input.getWarehouse();
    
    map<string, Block> blocksByName;
    map<long int, Shelf> shelvesById;
    map<string, Cell> cellsByCode;
    vector<Product> products = input.getProducts();
    map<string,Product> productsByCode;
	
    for(unsigned int i=0; i < products.size(); i++)
		productsByCode[products[i].getName()] = products[i];
	
	ProductAllocationProhibitions::recoverWarehouseData(warehouse,cellsByCode,shelvesById,blocksByName);
	
	int numIterations; //Change the name of this variable
	
	file>>numIterations; 
	for(int w= 0; w < numIterations; w++){
		file>>productCode;
		file>>numProhibitions;
	
		file>>numCellProhibitions>>numShelvesProhibitions>>numBlocksProhibitions;
	
		if(numCellProhibitions > 0 || numShelvesProhibitions >0|| numBlocksProhibitions >0 ){	
            ProductAllocationProhibitions prohibition;
         
            vector<Cell> _cells;
            vector<Shelf> _shelves;
            vector<Block> _blocks;
            
            if(productsByCode.find(productCode) != productsByCode.end()){
                for(int i=0; i<numCellProhibitions; i++){
					file>>cellCode;
					_cells.push_back(cellsByCode[cellCode]);
                }
                
                for(int i=0; i<numShelvesProhibitions; i++){
                    file>>idShelve;
                    _shelves.push_back(shelvesById[idShelve]);
                }
                
                for(int i=0; i<numBlocksProhibitions; i++){
                    file>>blockName;
                    _blocks.push_back(blocksByName[blockName]);
                }
                
                
                prohibition.setForbiddenCells(_cells);
                prohibition.setForbiddenShelves(_shelves);
                prohibition.setForbiddenBlocks(_blocks);
                prohibition.setProduct(productsByCode[productCode]);
                
                prohibitions.push_back(prohibition);
            }else{
                string fake;
                for(int i=0;i<numProhibitions;i++)
                    file>>fake;
            }
        }
		
		
	}

    return prohibitions;
}

void ProductAllocationProhibitions::recoverWarehouseData(Warehouse & warehouse, map<string, Cell> & cellsByCode, map<long int, Shelf> &shelvesById, map<string, Block> & blocksByName){
    vector<Block> blocks = warehouse.getBlocks();
    vector<Shelf> shelves;
    vector<Cell> cells;
    
    //Fill blocksById dictionary, while get the shelves of the block
    for(unsigned int i=0; i<blocks.size(); i++){
        blocksByName[blocks[i].getName()]= blocks[i];
        
        vector<Shelf> shelvesOnBlock = blocks[i].getShelves();
        shelves.insert(shelves.end(), shelvesOnBlock.begin(), shelvesOnBlock.end());
    }
    
    //Fill shelvesById dictionary, while get the cells of the shelf
	for(unsigned int i=0; i< shelves.size(); i++){
        shelvesById[shelves[i].getId()] = shelves[i];
        
        vector<Cell> cellsOnShelf = shelves[i].getCells();
        cells.insert(cells.end(), cellsOnShelf.begin(), cellsOnShelf.end());
    }
    
	
    for(unsigned int i=0; i<cells.size();i++)
        cellsByCode[cells[i].getCode()] = cells[i];
}
