#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include "BlockExit.h"
using namespace std;

/**
 * Default constructor 
 */
BlockExit::BlockExit(){}

/**
 *	Copy constructor
 */
BlockExit::BlockExit(const BlockExit &other){
    this->Id = other.Id;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
    this->blockAName = other.blockAName;
    this->blockBName = other.blockBName;
}

/**
 * Member constructor
 */ 
BlockExit::BlockExit(long int id, double coordX, double coordY, string blockA, string blockB){
    this->Id = id;
    this->coordX = coordX;
    this->coordY = coordY;
    this->blockAName = blockA;
    this->blockBName = blockB;
}

long int BlockExit::getId() const { return Id; }
double BlockExit::getCoordX() const {return coordX; }
double BlockExit::getCoordY() const {return coordY; }
string BlockExit::getBlockAName() const { return blockAName; }
string BlockExit::getBlockBName() const { return blockBName; }
pair<double, double> BlockExit::getCoords(){ return make_pair(coordX, coordY); }



void BlockExit::setId(long int value) { Id = value; }  //There is no Id value validation
void BlockExit::setCoordX(double value) { coordX = value; }
void BlockExit::setCoordY(double value) { coordY = value; }
void BlockExit::setBlockAName(double value) { blockAName = value; }
void BlockExit::setBlockBName(double value) { blockBName = value; }

bool BlockExit::operator==(const BlockExit &other) const { return this->Id == other.Id; }
bool BlockExit::operator!=(const BlockExit &other) const { return this->Id != other.Id; }


/**
 * Allow the use of an object of this class as a key in a map
 */
bool BlockExit::operator<(const BlockExit & other) const { 
		
		if(this->Id > other.Id)
			return false;
		if(this->Id < other.Id)
			return true; 
	
		pair<double,double> thisCoords= make_pair(coordX, coordY);
		pair<double,double> otherCoords= make_pair(other.coordX, other.coordY);
		
		if(thisCoords > otherCoords)
			return false;
		else
			return this->Id == other.Id && thisCoords < otherCoords;
		
}

/**
 *
 **/
BlockExit & BlockExit::operator=(const BlockExit &other){
	this->Id = other.Id;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
    this->blockAName = other.blockAName;
    this->blockBName = other.blockBName;
	
	return *this; 
}  

/**
 *	Print the exit main information 
 */
void BlockExit::printExitInformation(){
	cout<<"_____________________________\n";
	cout<<"Exit Id: \t"<<this->Id<<endl;
	cout<<"Block start: \t"<<this->blockAName<<"\t Block finish:\t"<<(this->blockBName!= "" ? this->blockBName : "No block")<<endl;
	cout<<"Exit coordinates: \t(x="<<this->coordX<<",y="<<this->coordY<<")"<<endl; 
	cout<<"_____________________________\n";
	
}