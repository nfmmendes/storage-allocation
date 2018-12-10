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

BlockExit::BlockExit(long int id, double coordX, double coordY, string blockA, string blockB){
    this->Id = id;
    this->coordX = coordX;
    this->coordY = coordY;
    this->blockAName = blockA;
    this->blockBName = blockB;
}

long int BlockExit::getId() { return Id; }
double BlockExit::getCoordX() {return coordX; }
double BlockExit::getCoordY() {return coordY; }
string BlockExit::getBlockAName() { return blockAName; }
string BlockExit::getBlockBName() { return blockBName; }
pair<double, double> BlockExit::getCoords(){ return make_pair(coordX, coordY); }



void BlockExit::setId(long int value) { Id = value; }  //There is no Id value validation
void BlockExit::setCoordX(double value) { coordX = value; }
void BlockExit::setCoordY(double value) { coordY = value; }
void BlockExit::setBlockAName(double value) { blockAName = value; }
void BlockExit::setBlockBName(double value) { blockBName = value; }

bool BlockExit::operator==(const BlockExit &other) { return this->Id == other.Id; }
bool BlockExit::operator!=(const BlockExit &other) { return this->Id != other.Id; }
bool BlockExit::operator<(const BlockExit & other) const { return this->Id < other.Id;} //<! Allow the use of an object of this class
// as a key in a map
