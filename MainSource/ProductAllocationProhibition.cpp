#include <iostream>
#include <vector>
#include <cstdlib>
#include <map>
#include "InputData.h"
#include "ProductAllocationProhibition.h"
using std::vector;
using std::map;
using std::ifstream;
using std::back_inserter;

ProductAllocationProhibitions::ProductAllocationProhibitions(){
    
}

ProductAllocationProhibitions::ProductAllocationProhibitions(const ProductAllocationProhibitions &other){
    this->product = other.product;
    
    copy(begin(other.forbiddenCells), end(other.forbiddenCells), back_inserter(this->forbiddenCells));
    copy(begin(other.forbiddenShelves), end(other.forbiddenShelves), back_inserter(this->forbiddenShelves));
    copy(begin(other.forbiddenBlocks), end(other.forbiddenBlocks), back_inserter(this->forbiddenBlocks));
}

const ProductAllocationProhibitions & ProductAllocationProhibitions::operator=(const ProductAllocationProhibitions &other){
    this->product = other.product;
    
	this->forbiddenCells.clear();
	this->forbiddenShelves.clear();    
	this->forbiddenBlocks.clear();

    copy(begin(other.forbiddenCells), end(other.forbiddenCells), back_inserter(this->forbiddenCells));
    copy(begin(other.forbiddenShelves), end(other.forbiddenShelves), back_inserter(this->forbiddenShelves));
    copy(begin(other.forbiddenBlocks), end(other.forbiddenBlocks), back_inserter(this->forbiddenBlocks));
	
	return *this;
}

ProductAllocationProhibitions::ProductAllocationProhibitions(const Product &product, const vector<Shelf>& forbiddenShelves, 
                                                        const vector<Cell>& forbiddenCells,const vector<Block> &blocks){
    
	this->product = product; 
	
    copy(begin(forbiddenCells), end(forbiddenCells), back_inserter(this->forbiddenCells));
    copy(begin(forbiddenShelves), end(forbiddenShelves), back_inserter(this->forbiddenShelves));
    copy(begin(forbiddenBlocks), end(forbiddenBlocks), back_inserter(this->forbiddenBlocks));
}

void ProductAllocationProhibitions::setProduct(const Product & other){ this->product = other; }
void ProductAllocationProhibitions::setForbiddenShelves(const vector<Shelf> & others){  this->forbiddenShelves = others; }
void ProductAllocationProhibitions::setForbiddenCells(const vector<Cell> &others) {  this->forbiddenCells = others; }
void ProductAllocationProhibitions::setForbiddenBlocks(const vector<Block> &others) {  this->forbiddenBlocks = others; }

const Product& ProductAllocationProhibitions::getProduct() const{   return this->product;}
const vector<Shelf>& ProductAllocationProhibitions::getForbiddenShelves() const { return this->forbiddenShelves;}
const vector<Cell>& ProductAllocationProhibitions::getForbiddenCells() const { return this->forbiddenCells; }
const vector<Block>& ProductAllocationProhibitions::getForbiddenBlocks() const { return this->forbiddenBlocks; }

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
	
    for(const auto& product : products)
		productsByCode[product.getName()] = product;
	
	ProductAllocationProhibitions::recoverWarehouseData(warehouse,cellsByCode,shelvesById,blocksByName);
	
	int numIterations; //Change the name of this variable
	
	file>>numIterations; 
	for(int w= 0; w < numIterations; w++){
		file>>productCode;
		file>>numProhibitions;
	
		file>>numCellProhibitions>>numShelvesProhibitions>>numBlocksProhibitions;

        if(numCellProhibitions <= 0 && numShelvesProhibitions < 0 && numBlocksProhibitions <= 0)
            continue;
	
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

    return prohibitions;
}

void ProductAllocationProhibitions::recoverWarehouseData(Warehouse& warehouse, map<string, Cell> & cellsByCode, map<long int, Shelf> &shelvesById, map<string, Block> & blocksByName){
    vector<Block> blocks = warehouse.getBlocks();
    vector<Shelf> shelves;
    vector<Cell> cells;
    
    //Fill blocksById dictionary, while get the shelves of the block
    for(const auto& block : blocks){
        blocksByName[block.getName()] = block;
        
        const auto& shelvesOnBlock = block.getShelves();
        shelves.insert(shelves.end(), shelvesOnBlock.begin(), shelvesOnBlock.end());
    }
    
    //Fill shelvesById dictionary, while get the cells of the shelf
    for(const auto& shelf : shelves){
        shelvesById[shelf.getId()] = shelf;
        
        const auto& cellsOnShelf = shelf.getCells();
        cells.insert(cells.end(), cellsOnShelf.begin(), cellsOnShelf.end());
    }
    
    for(const auto& cell : cells)
        cellsByCode[cell.getCode()] = cell;
}
