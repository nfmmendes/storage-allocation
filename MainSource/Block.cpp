#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<functional>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
#include "Block.h"
using std::cout;
using std::max;
using std::endl;
using std::make_pair;

Block::Block(): length(0), width(0), name(""){
}

Block::Block(const Block &other): name(other.name), width(max(0.0, other.width)), 
    length(max(0.0, other.length)){
	
    for(unsigned int i = 0; i< other.shelves.size();i++){
        this->shelves.push_back(Shelf(other.shelves[i]));
		shelvesById[other.shelves[i].getId()]= other.shelves[i];
	}
	
	copy(begin(other.exits), end(other.exits), back_inserter(exits));
	copy(begin(other.corridors), end(other.corridors), back_inserter(corridors));
	copy(begin(other.curves), end(other.curves), back_inserter(curves));
	
	this->bottomLeftCoords = other.bottomLeftCoords;
}

Block::Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double length):
	length(max(0.0, length)), width(max(0.0, width)), name(blockName)
{
    this->bottomLeftCoords = make_pair(bottomLeftCoordX, bottomLeftCoordY);
}

bool Block::hasValidConfiguration(){
    bool isValid = true;
	isValid &= none_of(begin(exits), end(exits), [this](auto &e){ 
		return e.getCoordX() < bottomLeftCoords.first || e.getCoordY() < bottomLeftCoords.second;
	});

	isValid &= none_of(begin(shelves), end(shelves), [this](auto &s) { 
		return s.getBottomLeftCoordX() < bottomLeftCoords.first || s.getBottomLeftCoordY() < bottomLeftCoords.second;
	});
    
    for(unsigned int i=0 ; i< corridors.size(); i++){
        /********** IMPLEMENT **+*/
        //TODO: Implement 
    }
    
    return isValid;
}

string Block::getName() const { return name; }
const vector<Shelf> & Block::getShelves() const {  return shelves; }
double Block::getWidth(){ return this->width;}
double Block::getLenght(){ return this->length;}
const map<long int, Shelf> & Block::getShelvesById() const{ return shelvesById; }
const vector<BlockExit> & Block::getExits() const {return exits; }
const vector<Corridor> & Block::getCorridors() const { return corridors;}
const vector<Curve> & Block::getCurves() const { return curves; }
const pair<double,double> & Block::getBottomLeftCoords() const { return bottomLeftCoords; }

void Block::setCorridors(const vector<Corridor> & others){
    this->corridors.clear();
    
	copy(begin(others), end(others), back_inserter(this->corridors));
}

void Block::setShelves(const vector<Shelf > & others){
    this->shelves.clear();
	
	copy(begin(others), end(others), back_inserter(this->shelves));
	transform(begin(shelves), end(shelves), inserter(shelvesById, end(shelvesById)),
		 [](auto& s){ return make_pair(s.getId(), s);  });
}

void Block::setCurves(const vector<Curve> & others){
    this->curves.clear();
	copy(begin(others),end(others), back_inserter(this->curves));
}

bool Block::operator<(const Block &other) const{
	return this->name < other.name; 
}

Block & Block::addExit(const BlockExit &exit){
	unsigned int i=0; 

	for( ; i<exits.size() && exits[i].getId() != exit.getId(); i++);

	if(i >= exits.size())
		this->exits.push_back(exit); 
	else 
		this->exits[i] = exit; 

	return *this;
}

bool Block::isInBlock(const Point &point)const{
	return point.getCoordX() >= bottomLeftCoords.first && point.getCoordX() <= bottomLeftCoords.first + width &&
			point.getCoordY() >= bottomLeftCoords.second && point.getCoordY() <= bottomLeftCoords.second + length;
}


void Block::setName(const string &name){
	this->name = name; 
}

Block & Block::operator=(const Block &other){
	
	this->shelves.clear();
	for(unsigned int i = 0; i< other.shelves.size();i++){
		this->shelves.push_back(Shelf(other.shelves[i]));
		shelvesById[other.shelves[i].getId()]= this->shelves[this->shelves.size()-1];
	}

	this->exits.clear();	
	copy(begin(other.exits), end(other.exits), back_inserter(this->exits));
	copy(begin(other.corridors), end(other.corridors), back_inserter(this->corridors));
	copy(begin(other.curves), end(other.curves), back_inserter(this->curves));

	this->name = other.name;
	this->bottomLeftCoords = other.bottomLeftCoords;
	this->width = max(0.0, other.width);
	this->length = max(0.0, other.length);

	return *this;
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


int Block::getNumberOfAvailablePositions(){
	int total = 0; 
	
	for(unsigned int i=0;i<shelves.size();i++)
		total += shelves[i].getNumberOfAvailablePositions(); 
	
	return total; 
}