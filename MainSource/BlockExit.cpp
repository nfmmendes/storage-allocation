#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include "BlockExit.h"
using namespace std;

BlockExit::BlockExit(){}

BlockExit::BlockExit(const BlockExit &other){
    this->Id = other.Id;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
    this->blockAName = other.blockAName;
    this->blockBName = other.blockBName;
}
 
BlockExit::BlockExit(unsigned long int id, double coordX, double coordY, string blockA, string blockB){
    this->Id = id;
    this->coordX = coordX;
    this->coordY = coordY;
    this->blockAName = blockA;
    this->blockBName = blockB;
}

unsigned long int BlockExit::getId() const { return Id; }
double BlockExit::getCoordX() const {return coordX; }
double BlockExit::getCoordY() const {return coordY; }
string BlockExit::getBlockAName() const { return blockAName; }
string BlockExit::getBlockBName() const { return blockBName; }
pair<double, double> BlockExit::getCoords() const { return make_pair(coordX, coordY); }


bool BlockExit::operator==(const BlockExit &other) const { 
	// We connsider that double values are equal only if they effectivelly 
	// are represented by the same double representation.
	return Id == other.Id && 
		   coordX == other.coordX && coordY == other.coordY && 
		   blockAName == other.blockAName && blockBName == other.blockBName; 	
}
bool BlockExit::operator!=(const BlockExit &other) const 
{ 
	return Id != other.Id ||
		   coordX != other.coordX || coordY != other.coordY ||
		   blockAName != other.blockAName || blockBName != other.blockBName; 

}
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

BlockExit & BlockExit::operator=(const BlockExit &other){
	this->Id = other.Id;
    this->coordX = other.coordX;
    this->coordY = other.coordY;
    this->blockAName = other.blockAName;
    this->blockBName = other.blockBName;
	
	return *this; 
}  

void BlockExit::printExitInformation(){
	cout<<"_____________________________\n";
	cout<<"Exit Id: \t"<<this->Id<<endl;
	cout<<"Block start: \t"<<this->blockAName<<"\t Block finish:\t"<<(this->blockBName!= "" ? this->blockBName : "No block")<<endl;
	cout<<"Exit coordinates: \t(x="<<this->coordX<<",y="<<this->coordY<<")"<<endl; 
	cout<<"_____________________________\n";
	
}