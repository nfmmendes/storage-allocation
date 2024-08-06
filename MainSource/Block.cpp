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
using namespace std;

/**
 * Constructor default
 */
Block::Block(){}


/**
 *	Copy constructor 
 */
Block::Block(const Block &other){
	
    for(unsigned int i = 0; i< other.shelves.size();i++){
        this->shelves.push_back(Shelf(other.shelves[i]));
		shelvesById[other.shelves[i].getId()]= other.shelves[i];
	}
	
    for(unsigned int i=0; i < other.exits.size(); i++)
        this->exits.push_back(BlockExit(other.exits[i]));
    
    for(unsigned int i=0; i< other.corridors.size(); i++)
        this->corridors.push_back(Corridor(other.corridors[i]));
    
    for(unsigned int i=0;i < other.curves.size();i++)
        this->curves.push_back(Curve(other.curves[i]));
    
    this->name = other.name;
    this->bottomLeftCoords = other.bottomLeftCoords;
    this->width = other.width;
    this->length = other.length;
}

/**
 *	Member constructor 
 */
Block::Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double length){

    this->name = blockName;
    this->bottomLeftCoords = make_pair(bottomLeftCoordX, bottomLeftCoordY);
    this->width = width;
    this->length = length;
	
}

/**
 *	Define if the block has a valid configuration based on the position of exits, corridors and shelves 
 */
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

void Block::setCorridors(vector<Corridor> & others){
    this->corridors.clear();
    
	copy(begin(others), end(others), back_inserter(this->corridors));
}

void Block::setShelves(vector<Shelf > & others){
    this->shelves.clear();
	
	copy(begin(others), end(others), back_inserter(this->shelves));
	transform(begin(shelves), end(shelves), inserter(shelvesById, end(shelvesById)),
		 [](auto& s){ return make_pair(s.getId(), s);  });
}

void Block::setCurves(vector<Curve> & others){
    this->curves.clear();
	copy(begin(others),end(others), back_inserter(this->curves));
}

bool Block::operator<(const Block &other) const{
	return this->name < other.name; 
}

bool Block::operator==(const Block &other){

	if(! (this->name == other.name && fabs(this->length-other.length) <1e-5 && fabs(this->width - other.width)<1e-5))
		return false; 

	if( this->bottomLeftCoords != other.bottomLeftCoords)
		return false; 

	//If the blocks don't have the same number of exits, corridors and curves they are not equals 
	bool equalVertexes = this->shelves.size() == other.shelves.size();
	bool equalExits = this->exits.size() == other.exits.size(); 
	bool equalCorridors = this->corridors.size() == other.corridors.size(); 
	bool equalCurves = this->curves.size() == other.curves.size(); 

	if(!(equalVertexes && equalExits && equalCorridors && equalCurves))
		return false; 

	//The shelves, exits, corridors and curves are sort to be compared. Otherwise two lists with the same elements could 
	// result in a "false" return
	vector<Shelf> otherShelves = other.shelves; 	
	sort(this->shelves.begin(), this->shelves.end());
	sort(otherShelves.begin(), otherShelves.end()); 	

	vector<BlockExit> otherExits = other.exits;
	sort(this->exits.begin(), this->exits.end());
	sort(otherExits.begin(), otherExits.end()); 

	vector<Corridor> otherCorridors = other.corridors; 
	sort(this->corridors.begin(), this->corridors.end()); 
	sort(otherCorridors.begin(), otherCorridors.end()); 

	vector<Curve> otherCurves = other.curves;
	sort(this->curves.begin(), this->curves.end());
	sort(otherCurves.begin(), otherCurves.end()); 

	
	for(unsigned int i = 0; i< this->shelves.size(); i++)
		if(this->shelves[i] != otherShelves[i])  
			return false; 

	for(unsigned int i = 0; i< this->exits.size(); i++)
		if(this->exits[i] != otherExits[i])
			return false; 
		
	for(unsigned int i = 0; i < this->corridors.size(); i++)
		if(this->corridors[i] != otherCorridors[i])
			return false; 
	
	for(unsigned int i=0; i < this->curves.size(); i++)
		if(this->curves[i] != otherCurves[i])
			return false; 
	
	return true;
    
}

Block & Block::addExit(BlockExit &exit){
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
	for(unsigned int i=0; i < other.exits.size(); i++)
		this->exits.push_back(BlockExit(other.exits[i]));
	
	this->corridors.clear();
	for(unsigned int i=0; i< other.corridors.size(); i++)
		this->corridors.push_back(Corridor(other.corridors[i]));
	
	this->curves.clear();
	for(unsigned int i=0;i < other.curves.size();i++)
		this->curves.push_back(Curve(other.curves[i]));
	

	this->name = other.name;
	this->bottomLeftCoords = other.bottomLeftCoords;
	this->width = other.width;
	this->length = other.length;
	

	
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