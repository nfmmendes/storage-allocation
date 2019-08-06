#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
#include "Block.h"
using namespace std;

Block::Block(){}

Block::Block(const Block &other){
	
    for(unsigned int i = 0; i< other.shelves.size();i++)
        this->shelves.push_back(Shelf(other.shelves[i]));
    
    for(unsigned int i=0; i < other.exits.size(); i++)
        this->exits.push_back(BlockExit(other.exits[i]));
    
    for(unsigned int i=0; i< other.corridors.size(); i++)
        this->corridors.push_back(Corridor(other.corridors[i]));
    
    for(unsigned int i=0;i < other.curves.size();i++)
        this->curves.push_back(Curve(other.curves[i]));
    

    this->name = other.name;
    this->bottomLeftCoords = other.bottomLeftCoords;
    this->width = other.width;
    this->lenght = other.lenght;
}

/**********************************************************************************
*
*
***********************************************************************************/
Block::Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double lenght){

    this->name = blockName;
    this->bottomLeftCoords = make_pair(bottomLeftCoordX, bottomLeftCoordY);
    this->width = width;
    this->lenght = lenght;
	
}


/**********************************************************************************
*
*
***********************************************************************************/
bool Block::hasValidConfiguration(){
    bool isValid = true;
    for(unsigned int i = 0; i <exits.size();i++)
        if(exits[i].getCoordX() < bottomLeftCoords.first || exits[i].getCoordY() < bottomLeftCoords.second){
            isValid = false;
            break;
        }
    
    for(unsigned int i = 0; i< shelves.size(); i++){
        if(shelves[i].getBottomLeftCoordX() < bottomLeftCoords.first || shelves[i].getBottomLeftCoordY() < bottomLeftCoords.second){
            isValid = false;
            break;
        }
    }
    
    for(unsigned int i=0 ; i< corridors.size(); i++){
        /********** IMPLEMENT **+*/
        
    }
    
    return isValid;
}

/**********************************************************************************
*
*
***********************************************************************************/
string Block::getName() { return name; }

/**********************************************************************************
*
*
***********************************************************************************/
vector<Shelf> Block::getShelves() {return shelves; }

/**********************************************************************************
*
*
***********************************************************************************/
vector<BlockExit> Block::getExits() {return exits; }

/**********************************************************************************
*
*
***********************************************************************************/
vector<Corridor> Block::getCorridors() { return corridors;}

/**********************************************************************************
*
*
***********************************************************************************/
vector<Curve> Block::getCurves() { return curves; }

/**********************************************************************************
*
*
***********************************************************************************/
pair<double,double> Block::getBottomLeftCoords() {return bottomLeftCoords; }



/**********************************************************************************
*	Set corridors
*
***********************************************************************************/
void Block::setCorridors(vector<Corridor> & others){
    this->corridors.clear();
    
    for(unsigned int i=0; i<others.size();i++)
        this->corridors.push_back(Corridor(others[i]));
}


/**********************************************************************************
*	Set all the shelves of a block
*
***********************************************************************************/
void Block::setShelves(vector<Shelf > & other){
    this->shelves.clear();
    for(unsigned int i=0; i<other.size();i++)
        this->shelves.push_back(Shelf(other[i]));
    
}

/**********************************************************************************
*	Set all the shelves of a block
*
***********************************************************************************/
void Block::setCurves(vector<Curve> & other){
    this->curves.clear();
    for(unsigned int i=0; i < other.size(); i++)
        this->curves.push_back(Curve(other[i]));
}


/**********************************************************************************
*	Add a exit in a block (if it was not inserted a exit with same Id yet)
*
***********************************************************************************/
void Block::addExit(BlockExit & other) {
    if( find(exits.begin(), exits.end(), other) == exits.end()){
        BlockExit inserted(other);
        exits.push_back(inserted);
    }
}

/**********************************************************************************
*	@brief Removes the exit with id equals to Id in the block of exits
*
***********************************************************************************/
void Block::removeExitWithId(long int Id){
    for(unsigned int i=0; i<this->exits.size();i++)
        if(this->exits[i].getId() == Id){
            this->exits.erase(this->exits.begin()+i);
            break;
        }
}

/**********************************************************************************
*	Removes the exit with the index i in the block list of exits
*
***********************************************************************************/
void Block::removeExit(int index){
    if(index >= 0 && index < (int)this->exits.size())
        this->exits.erase(this->exits.begin()+index);
}


/**********************************************************************************
*	@brief TODO: Improve this
*
***********************************************************************************/
bool Block::operator==(const Block &other){
    return this->name == other.name;
}

/**********************************************************************************
 * 
 * 
 **********************************************************************************/
bool Block::isInBlock(const Point &point)const{
    return point.getCoordX() >= bottomLeftCoords.first && point.getCoordX() <= bottomLeftCoords.first + width &&
           point.getCoordY() >= bottomLeftCoords.second && point.getCoordY() <= bottomLeftCoords.second + lenght;
}


void Block::setName(const string &name){
	this->name = name; 
}


void Block::printBlockInformation(){
	
	cout<<"_________________________________________\n"; 
	cout<<"Block: \t"<<this->getName()<<endl;
	cout<<"\n\tNumber of shelves: \t"<<this->shelves.size()<<endl;
	cout<<"Number of exits: \t"<<this->exits.size()<<endl;
	cout<<"Number of corridor: \t"<<this->corridors.size()<<endl;
	cout<<"Number of curves: \t"<<this->curves.size()<<endl; 
	
	for(unsigned int i=0;i<this->shelves.size();i++)
		this->shelves[i].printShelfInformation();
	
	for(unsigned int i=0;i<this->exits.size();i++)
		this->exits[i].printExitInformation();
	
	for(unsigned int i=0;i<this->corridors.size();i++)
		this->corridors[i].printCorridorInformation();
	
	for(unsigned int i=0;i<this->curves.size();i++)
		this->curves[i].printCurveInformation(); 
	
	cout<<"_________________________________________\n";
	cout<<endl; 
}
