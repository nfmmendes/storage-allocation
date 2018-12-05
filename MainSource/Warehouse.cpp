#include<iostream>
#include<string>
#include<cstdlib>
#include<map>
#include<fstream>
#include<utility>
#include<vector>
#include<cstdlib>

 #include "Warehouse.h"
 
 using namespace std;
 
 
 ///////////////////////////////////////////////////////////////////
 ///
 ///
 ///////////////////////////////////////////////////////////////////
 void Warehouse::ReadWarehouseData(string fileName){
    
     ifstream file;
     file.open(fileName,ios::in);
    
    int numBlocks;
    int numExits;
    int numShelves;
    
    //The reading sequence is 
    // 1. The number n1 of blocks
    //      1.1. The next n1 lines will contain each one 
    //           nomeOfBlock, beginBlockX, beginBlockY (top left corner) 
    // 2. The  number n2 of block exits
    //      2.1. The next n2 lines will contain each one
    //           idExit, exitCoordX, exitCoordY, blockA_name, blockB_name (nullable. If null the block name will be #_#_#)
    //3. The number n3 of shelves          
    //      3.1. The next n3 lines will contain each one
    //          idShelve, blockName, bottomLeftCoordX, bottomLeftCoordY, Column, Lines, CellsLenght, CellsWidth
    //4. The number n4 of corridors
    //
    //
    //
    //


    if(file.is_open()){
        file>>numBlocks;

        //Those variables will store the basic data of each block in the warehouse
        string blockName;
        double blockBottomLeftCoordX;
        double blockBottomLeftCoordY; 

        for(int i=0; i<numBlocks; i++){
            file>> blockName>> blockBottomLeftCoordX >> blockBottomLeftCoordY;
            this->blocks.push_back(Block(blockName, blockBottomLeftCoordX, blockBottomLeftCoordY));
        }

        //Read all the data concerning block exits
        file>> numExits;
        long int idExit;
        double exitCoordX, exitCoordY;
        string blockBName; 
        map<string, vector<BlockExit>> exitsByBlock; 
   
        if(numExits == 0){
            for(int i=0; i<numExits; i++){
                file>> idExit >> exitCoordX >> exitCoordY>>blockName>>blockBName; 

                //Fill auxiliary structure to connect 
                if(blockBName != "#_#_#")
                    exitsByBlock[blockName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockName));
                else{
                    //Here are done two inserts because the data describing the exits can arrive in just one way, 
                    //but the exit should be inserted in both blocks objects (We can assume that a single exit connects
                    //just two blocks)
                    exitsByBlock[blockName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockName,blockBName));
                    exitsByBlock[blockBName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockName,blockBName));
                }
            }

            //Now, for each block, we will insert all its exits. 
            //We assume that it will be few blocks and each block will have few exits, so this part of code will
            //not harm the code performance
            for(int i=0;i<(int)blocks.size();i++){
                vector<BlockExit> exitsOfBlock = exitsByBlock[blocks[i].getName()];
                for(int j=0;j<(int)exitsOfBlock.size();j++)
                    this->blocks[i].addExit(exitsOfBlock[j]);
            }
        }

        //Read all the data concerning shelves
        file>> numShelves; 
        long int idShelf;
        int columns;
        int lines; 
        double cellsLenght, cellsWidth; 
        vector<Shelf> shelves; 
        map<string, vector<Shelf> > shelvesByBlock; 
        for(int i=0; i<numShelves; i++){
            file>>idShelf>>blockName>> blockBottomLeftCoordX >> blockBottomLeftCoordY>> columns >> lines >> cellsLenght >> cellsWidth; 
            Shelf aux = Shelf(vector<Cell>(), make_pair(blockBottomLeftCoordX, blockBottomLeftCoordY),
                                                   blockName, columns, lines, cellsLenght, cellsWidth );
            shelves.push_back(aux);
            shelvesByBlock[blockName].push_back(aux);
        }

        //Now, for each block, we will insert all its shelves. 
        //We assume that it will be few blocks and each block will have few shelves, so this part of code will
        //not harm the code performance
        for(int i=0;i<(int)blocks.size();i++){
            this->blocks[i].setShelves(shelvesByBlock[blocks[i].getName()]);
        }
        
    }
 }
 
 ///////////////////////////////////////////////////////////////////
 ///
 ///
 ///////////////////////////////////////////////////////////////////
 void Warehouse::WriteWarehouseData(string fileName){
     
     
 }
 
 ///////////////////////////////////////////////////////////////////
 ///    Insert the data of a new block in the warehouse
 ///////////////////////////////////////////////////////////////////
void Warehouse::InsertNewBlock(Block &b){
    this->blocks.push_back(Block(b));
}
 
///////////////////////////////////////////////////////////////////
///     Remove a block "b" in the blocks list
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveBlock(Block &b){
    remove(this->blocks.begin(), this->blocks.end(),b);
}

///////////////////////////////////////////////////////////////////
///     Remove a block in the position i of blocks list
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveBlock(int i){
    if(i >= 0 && i <(int) this->blocks.size())
        this->blocks.erase(this->blocks.begin()+i);
}

///////////////////////////////////////////////////////////////////
///         Sets the product allocation in a warehouse
///     In this procedure is created a copy of the data, so the original one
///         will be not referecend by the warehouse object
/////////////////////////////////////////////////////////////////// 
void Warehouse::setProductAllocation(vector<pair<Product, Cell>> & productAllocation){
    this->productAllocation.clear();
    
    for(int i=0; i<(int)productAllocation.size(); i++)
        this->productAllocation.push_back(make_pair(productAllocation[i].first, productAllocation[i].second));
}

///////////////////////////////////////////////////////////////////
///     Inserts a new product allocation on the warehouse
/////////////////////////////////////////////////////////////////// 
void Warehouse::AddProductAllocation(pair<Product, Cell> & productAllocation){
    this->productAllocation.push_back(make_pair(productAllocation.first, productAllocation.second));
}

///////////////////////////////////////////////////////////////////
///     Remove a allocation of a product
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveProductAllocation(Cell &cell){
    vector<pair<Product,Cell>>::iterator it = this->productAllocation.begin();
    for(;it != this->productAllocation.end(); it++)
        if(it->second == cell){
            productAllocation.erase(it);
            break;
        }
}


///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveProductAllocation(int i){
    
    if(i >= 0 && i < (int) this->productAllocation.size())
        this->productAllocation.erase(this->productAllocation.begin()+i);
}
            
///////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////            
string Warehouse::getName(){ return this->name;}

///////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////// 
vector<Block> Warehouse::getBlocks(){ return this->blocks;}

///////////////////////////////////////////////////////////////////
///
/////////////////////////////////////////////////////////////////// 
vector<pair<Product, Cell> > Warehouse::getProductAllocation(){
    return this->productAllocation;
}

///////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////             
void Warehouse::setName(string &name){
    this->name = name;
}

///////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////             
void Warehouse::setBlocks(vector<Block>& blocks){
    this->blocks.clear();
    
    for(unsigned int i=0; i < blocks.size(); i++)
        this->blocks.push_back(Block(blocks[i]));
}

