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
 
 
 
 /**
  *
  **/
 Warehouse::Warehouse(const Warehouse &other){
	
	this->name = other.name;
	
	for(unsigned int i=0; i<other.blocks.size();i++)
		this->blocks.push_back(other.blocks[i]);
	
    for(unsigned int i=0; i<other.expeditionPoints.size();i++)
        this->expeditionPoints.push_back(other.expeditionPoints[i]);
	 
 }
 
 
 /**
  *
  *
  **/
 void Warehouse::ReadWarehouseData(ifstream &file){
    
    
    int numBlocks;
    int numExits;
    int numShelves;
    int numCorridors; 
    int numCells;
    int numCurves;
	int numExpeditionPoints;
     
    //The reading sequence is 
    // 1. The number n1 of blocks
    //      1.1. The next n1 lines will contain each one 
    //           blockName, beginBlockX, beginBlockY (top left corner)
	// 2. The number n2 of expeditionPoints
	//		2.1. The next n2 lines will contain each one
	//			expeditionPointCode, blockName, coordX, coordY
    // 3. The  number n2 of block exits
    //      3.1. The next n2 lines will contain each one
    //           idExit, exitCoordX, exitCoordY, blockA_name, blockB_name (nullable. If null the block name will be #_#_#)
    // 4. The number n3 of shelves          
    //      4.1. The next n3 lines will contain each one
    //          idShelve, blockName, bottomLeftCoordX, bottomLeftCoordY, Column, Lines, CellsLenght, CellsWidth
    // 5. The number n4 of corridors
    //      5.1. The next n3 lines will contain each one
    //          idCorridor, blockName, CorridorDirection, CorridorSense, beginCoordX, beginCoordEnd, length
    // 6. The number n5 of cells
    //      6.1. The next n5 lines will contain each one
    //          idShelve, code, num_of_levels, row, column
    // 7. The number n6 of curves
    //      7.1. The next n6 lines will contain each one
    //          blockName, idCurva, corridor1Id, corridor2Id, pointXCorridor1, pointYCorridor1, pointXCorridor1, pointYCorridor2
    //
    //
    //

    if(file.is_open()){
        

        //Those variables will store the basic data of each block in the warehouse
        string blockName;
        double blockBottomLeftCoordX;
        double blockBottomLeftCoordY;
        double width, lenght; 

	
		file>>numBlocks;
		cout<<"Reading blocks...\n";
		cout<<numBlocks<<endl;
        for(int i=0; i<numBlocks; i++){
            file>> blockName>> blockBottomLeftCoordX >> blockBottomLeftCoordY>> width >> lenght;
            this->blocks.push_back(Block(blockName, blockBottomLeftCoordX, blockBottomLeftCoordY, width, lenght));
        }
		
		file>>numExpeditionPoints;
		cout<<"Reading expedition points...\n";
		double coordX, coordY;
		string expeditionCode; 
		cout<<numExpeditionPoints<<endl;
		for(int i=0;i<numExpeditionPoints;i++){
			file>>expeditionCode>>blockName>>coordX>>coordY; 
			this->expeditionPoints.push_back(ExpeditionPoint(expeditionCode, blockName, pair<double,double>(coordX, coordY)));
		}

        //Read all the data concerning block exits
        file>> numExits;
        long int idExit;
        double exitCoordX, exitCoordY;
        string blockBName; 
        map<string, vector<BlockExit> > exitsByBlock;
   
		cout<<"Reading blocks exits...\n";
		cout<<numExits<<endl;
        if(numExits != 0){
            for(int i=0; i<numExits; i++){
				
                file>> idExit >> exitCoordX >> exitCoordY>>blockName>>blockBName; 

				//Fill auxiliary structure to connect 
                if(blockBName == "#_#_#")
                    exitsByBlock[blockName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockName));
                else{
					
                    //Here are done two inserts because the data describing the exits can arrive in just one way, 
                    //but the exit should be inserted in both blocks objects (We can assume that a single exit connects
                    //just two blocks)
                    exitsByBlock[blockName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockName,blockBName));
                    exitsByBlock[blockBName].push_back(BlockExit(idExit, exitCoordX, exitCoordY, blockBName,blockName));
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
		
		
		cout<<"Reading shelves...\n";
        //Read all the data concerning shelves
        file>> numShelves; 
		cout<<numShelves<<endl;
        long int idShelf;
        int columns;
        int lines; 
        double cellsLenght, cellsWidth; 
        vector<Shelf> shelves; 
        map<string, vector<Shelf> > shelvesByBlock; 
        for(int i=0; i<numShelves; i++){
            file>>idShelf>>blockName>> blockBottomLeftCoordX >> blockBottomLeftCoordY>> columns >> lines >> cellsLenght >> cellsWidth; 
            Shelf aux(idShelf,vector<Cell>(), make_pair(blockBottomLeftCoordX, blockBottomLeftCoordY),
                                                   blockName, columns, lines, cellsLenght, cellsWidth );
            shelves.push_back(aux);
            shelvesByBlock[blockName].push_back(aux);
			//cout<<"Current block shelve size: "<<blockName<<" " <<shelvesByBlock[blockName].size()<<endl;
        }

        //Now, for each block, we will insert all its shelves. 
        //We assume that it will be few blocks and each block will have few shelves, so this part of code will
        //not harm the code performance
        for(int i=0;i<(int)blocks.size();i++){
			cout<<"Shelves on block: \n" <<shelvesByBlock[blocks[i].getName()].size()<<endl;
            this->blocks[i].setShelves(shelvesByBlock[blocks[i].getName()]);
        }
		
        cout<<"Reading corridors...\n";
        //Read all data concerning corridors
        file>>numCorridors;
		cout<<numCorridors<<endl;
        long int idCorridor;
        string dirCorridor, senseCorridor;
        double beginCoordX, beginCoordY,length;
        map<string, vector<Corridor> > corridorsByBlock;
        for(int i=0; i < numCorridors; i++){
            file>>idCorridor>>blockName>>dirCorridor>>senseCorridor>>beginCoordX>>beginCoordY>>length;
			//cout<<idCorridor<<" "<<dirCorridor<<" "<<senseCorridor<<" "<<beginCoordX<<" "<<beginCoordY<<" "<<length<<endl;
            string dir = dirCorridor;
            string sense = senseCorridor;
            corridorsByBlock[blockName].push_back(Corridor(idCorridor,blockName, dir, sense, make_pair(beginCoordX, beginCoordY), length));
        }
        
        //Now, for each block, we insert all its corridors
        //We assume that it be few blocks, so this part of code will not harm too much the code perfomance
        for(unsigned int i=0; i<blocks.size();i++)
            this->blocks[i].setCorridors(corridorsByBlock[this->blocks[i].getName()]);
        
		cout<<"Reading cells...\n";
        //Read all data concerning cells
        file>>numCells;
		cout<<numCells<<endl;
        int row, column;
        string cellCode;
        int numLevels;
        map<int,vector<Cell> > cellsByShelf;
		
        for(int i=0;i<numCells;i++){
            file>>idShelf>>cellCode>>numLevels>>row>>column;
            cellsByShelf[idShelf].push_back(Cell(cellCode,idShelf,numLevels,row,column));
        }
        
        for(unsigned int i= 0; i<blocks.size();i++){
            vector<Shelf> blockShelves = blocks[i].getShelves();
            for(unsigned j=0; j<blockShelves.size();j++){
                blockShelves[j].setCells(cellsByShelf[blockShelves[j].getId()]);
			}
			
			
			
            blocks[i].setShelves(blockShelves);
        }
        
		cout<<"Reading curves...\n";
        file>>numCurves;
		cout<<numCurves<<endl;
        long int idCurve, startCorridor, endCorridor;
        double endCoordX, endCoordY;
        map<string, vector<Curve> > curvesByBlock;
        for(int i=0;i<numCurves;i++){
            file>>blockName>>idCurve>>startCorridor>>endCorridor>>beginCoordX>>beginCoordY>>endCoordX>>endCoordY;
			//cout<<blockName<<" "<<idCurve<<" "<<startCorridor<<" "<<endCorridor<<" "<<beginCoordX<<" "<<beginCoordY<<" "<<endCoordX<<" "<<endCoordY;
            curvesByBlock[blockName].push_back(Curve(idCurve, startCorridor, endCorridor,
                                                     Point("beginCurve"+to_string(idCurve),beginCoordX, beginCoordY,0), 
			  									   Point("endCurve"+to_string(idCurve),endCoordX, endCoordY,0)));
            
        }
        
        for(unsigned int i=0; i<blocks.size();i++)
            blocks[i].setCurves(curvesByBlock[blocks[i].getName()]);
    }
 }
 
 /**
  *
  *
  **/
 void Warehouse::WriteWarehouseData(string fileName){
     
     ofstream file;
     file.open(fileName, ios::out);
     file.close();
 }
 
 /**
  *    Insert the data of a new block in the warehouse
  **/
void Warehouse::InsertNewBlock(Block &b){
    this->blocks.push_back(Block(b));
}
 
/**
 *     Remove a block "b" in the blocks list
 **/
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

/**
 *         Sets the product allocation in a warehouse
 *     In this procedure is created a copy of the data,
 *       so the original one will be not referecend by the
 *             warehouse object
 **/
void Warehouse::setProductAllocation(vector<pair<Product, Cell> > & productAllocation){
    this->productAllocation.clear();
    
    for(int i=0; i<(int)productAllocation.size(); i++)
        this->productAllocation.push_back(make_pair(productAllocation[i].first, productAllocation[i].second));
}

/**
 *     Inserts a new product allocation on the warehouse
 **/
void Warehouse::AddProductAllocation(pair<Product, Cell> & productAllocation){
    this->productAllocation.push_back(make_pair(productAllocation.first, productAllocation.second));
}

/**
 *     Remove a allocation of a product
 **/
void Warehouse::RemoveProductAllocation(Cell &cell){
    vector<pair<Product,Cell> >::iterator it = this->productAllocation.begin();
    for(;it != this->productAllocation.end(); it++)
        if(it->second == cell){
            productAllocation.erase(it);
            break;
        }
}


/**
 *
 **/
void Warehouse::RemoveProductAllocation(int i){
    
    if(i >= 0 && i < (int) this->productAllocation.size())
        this->productAllocation.erase(this->productAllocation.begin()+i);
}
            
/**
 *
 **/
string Warehouse::getName() const { return this->name;}

/**
 *
 **/
vector<Block> Warehouse::getBlocks() const { return this->blocks;}

/**
 *
 **/
map<string, Block> Warehouse::getBlocksByName(){
	map<string, Block> result; 
	
	for(unsigned int i = 0; i< this->blocks.size(); i++)
		result[blocks[i].getName()] = blocks[i];
	
	return result; 
}

/**
 *
 **/
 vector<pair<Product, Cell> > Warehouse::getProductAllocation() const {
    return this->productAllocation;
}

/**
 *
 **/
void Warehouse::setName(string &name){
    this->name = name;
}

/**
 *
 **/
void Warehouse::setBlocks(vector<Block>& blocks){
    this->blocks.clear();
    
    for(unsigned int i=0; i < blocks.size(); i++)
        this->blocks.push_back(Block(blocks[i]));
}

/**
 *
 **/
vector<ExpeditionPoint> Warehouse::getExpeditionPoints(){
    return this->expeditionPoints;
}


/**
 *
 **/
void Warehouse::printWarehouseInformation(){
	
	cout<<"Printing warehouse information...\n\n\n";
	cout<<"\tNumber of pavilion: \t"<<this->blocks.size() <<endl;
	cout<<"\tNumber of expedition points \t"<<this->expeditionPoints.size()<<endl;
	
	
	cout<<"Printing detailed information of blocks...\n\n\n";
	for(unsigned int i =0;i<blocks.size();i++)
		this->blocks[i].printBlockInformation();
}


/**
 *
 **/
Warehouse & Warehouse::operator=(const Warehouse &other){
	this->name = other.name;
	
	for(unsigned int i=0; i<other.blocks.size();i++)
		this->blocks.push_back(other.blocks[i]);
	
	for(unsigned int i=0; i<other.expeditionPoints.size();i++)
        this->expeditionPoints.push_back(other.expeditionPoints[i]);
	
	return *this;
}