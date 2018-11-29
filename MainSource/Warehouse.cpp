 #include<iostream>
 #include<cstdlib>
 #include<map>
 #include<utility>
 #include<vector>
 #include "Warehouse.h"
 
 using namespace std;
 
 
 ///////////////////////////////////////////////////////////////////
 ///
 ///
 ///////////////////////////////////////////////////////////////////
 void Warehouse::ReadWarehouseData(string fileName){
    
    ifstream file = ifstream.open(fileName);
    
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
    //          
    //3. The number n3 of shelves
    //      3.1. The next n3 lines will contain each one
    //          idShelve, blockName, bottomLeftCoordX, bottomLeftCoordY, Column, Lines, CellsLenght, CellsWidth


    if(file.is_open()){
        file>>numBlocks;

        //Those variables will store the basic data of each block in the warehouse
        string blockName;
        double blockBottomLeftCoordX;
        double blockBottomLeftCoordY; 

        for(int i=0; i<numBlocks; i++){
            file>> blockName>> blockBottomLeftCoordX >> blockBottomLeftCoordY;
            this->blocks[i].push_back(Block(blockName, blockBottomLeftCoordX, blockBottomLeftCoordY));
        }

        //Read all the data concerning block exits
        file>> numExists;
        long int IdExit; 
        double exitCoordX, exitCoordY; 
        string blockBName; 
        map<string, vector<BlockExit>> exitsByBlock; 
   
        if(nummExits == 0){
            for(int i=0; i<numExits; i++){
                file>> idExit >> exitCoordX >> exitCoordY>>blockName>>blockBName; 

                //Fill auxiliary structure to connect 
                if(blockBName != "#_#_#")
                    exitByBlock[blockName].push_back(BlockExit(idExit, coordX, coordY, blockA)); 
                else{
                    //Here are done two inserts because the data describing the exits can arrive in just one way, 
                    //but the exit should be inserted in both blocks objects (We can assume that a single exit connects
                    //just two blocks)
                    exitByBlock[blockName].push_back(BlockExit(idExit, coordX, coordY, blockA,blockBName));
                    exitByBlock[blockBName].push_back(BlockExit(idExit, coordX, coordY, blockA,blockBName));   
                }
            }

            //Now, for each block, we will insert all its exits. 
            //We assume that it will be few blocks and each block will have few exits, so this part of code will
            //not harm the code performance
            for(int i=0;i<blocks[i];i++){
                vector<BlockExits> exitsOfBlock = exitByBlock[blocks[i].getName()];
                for(int j=0;j<exitsOfBlock.size();j++)
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
            Shelf aux = Shelf(vetor<Cell>(), make_pair(blockBottomLeftCoordX, blockBottomLeftCoordY), 
                                                   blockName, columns, lines, cellsLenght, cellsWidth );
            shelves.push_back(aux);
            shelvesByBlock[blockName].push_back(shelvesByBlock);
        }

        //Now, for each block, we will insert all its shelves. 
        //We assume that it will be few blocks and each block will have few shelves, so this part of code will
        //not harm the code performance
        for(int i=0;i<blocks[i];i++){
            this->blocks[i].setShelves(shelves[blocks[i].getName()]);
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
 ///
 ///
 ///////////////////////////////////////////////////////////////////
void Warehouse::InsertNewBlock(Block &b){
    
    
}
 
///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveBlock(Block &b){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveBlock(int i){
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::SetProductAllocation(pair<Product, Cell> & productionAllocation){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::AddProductAllocation(pair<Product, Cell> & productionAllocation){
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveProductAllocation(Cell &cell); 


///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
void Warehouse::RemoveProductAllocation(int i){
    
    
}
            
///////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////            
string GetName(string &name){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
vector<Block &> GetBlocks(){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////////////////////// 
vector<pair<Product, Cell> > GetProductAllocation(){
    
}

///////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////             
void SetName(string &name){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////             
void SetBlocks(vector<Block &> blocks){
    
    
}

///////////////////////////////////////////////////////////////////
///
///
///////////////////////////////////////////////////////////////////             
void SetProductAllocation(vector<pair<Product, Cell> > & productAllocation){
    
}