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
        //TODO: Implement 
    }
    
    return isValid;
}

/**
 * Define the name of the block
 */
string Block::getName() const { return name; }

/**
 *	Return the shelves of the block 
 */
vector<Shelf> & Block::getShelves() {return shelves; }


double Block::getWidth(){ return this->width;}
double Block::getLenght(){ return this->length;}

/**
 * 
 **/
map<long int, Shelf> Block::getShelvesById(){
	
	return shelvesById;
}

/**
 *	Return the exits of the block 
 **/
vector<BlockExit> Block::getExits() {return exits; }

/**
 * Return the corridors of the block 
 */ 
vector<Corridor> Block::getCorridors() { return corridors;}

/**
 *	Return all the curves in a block 
 **/
vector<Curve> Block::getCurves() { return curves; }

/**
 *	Return all the bottom left coordinates 
 **/
pair<double,double> Block::getBottomLeftCoords() {return bottomLeftCoords; }



/**
 *	Set corridors in the block 
 *  @param others List of block corridors. These blocks will replace the corridors currently in the block 
 **/
void Block::setCorridors(vector<Corridor> & others){
    this->corridors.clear();
    
    for(unsigned int i=0; i<others.size();i++)
        this->corridors.push_back(Corridor(others[i]));
}


/**
*	Set all the shelves of a block
*	@param others List of shelves. These shelves will replace the shelves currently in the block
**/
void Block::setShelves(vector<Shelf > & others){
    this->shelves.clear();
	for(unsigned int i=0; i<others.size();i++)
        this->shelves.push_back(Shelf(others[i]));
	
	//std::transform(shelves.begin(), shelves.end(), std::inserter(shelvesById, shelvesById.end()),
      //         [](const Shelf &s) { return std::make_pair(s.getId(), s); });
    for(Shelf & shelf : shelves )
		shelvesById[shelf.getId()] = shelf;
}

/**
*	Set all the curves of a block
*	@param others List of curves. These curves will replace the curves currently in the block 
**/ 
void Block::setCurves(vector<Curve> & others){
    this->curves.clear();
    for(unsigned int i=0; i < others.size(); i++)
        this->curves.push_back(Curve(others[i]));
}


/**
 *
 **/
bool Block::operator<(const Block &other) const{
	return this->name < other.name; 
}



/**
*	Equals operator overload 	
*	@param other The block in the right side of the operator 
*/
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

	/**
	 *	Add a shelf in the block. If a shelf with the same ID already exists, it will be replaced 
	 *  @param Shelf to be added 
	 */
	Block & Block::addShelf(Shelf &shelf){
		unsigned int i=0; 
		for( ; i<shelves.size() && shelves[i].getId() != shelf.getId(); i++);
		
		if(i != shelves.size())
			this->shelves.push_back(shelf); 
		else
			this->shelves[i] = shelf; 
		
		shelvesById[shelf.getId()] = shelf; 
		return *this; 
	}
	
	/**
	 * Add an exit in the block. If an exit with the same ID already exists, it will be replaced
	 * @param exit Exit to be added 
	 **/
	Block & Block::addExit(BlockExit &exit){
		unsigned int i=0; 
	
		for( ; i<exits.size() && exits[i].getId() != exit.getId(); i++);
	
		if(i >= exits.size())
			this->exits.push_back(exit); 
		else 
			this->exits[i] = exit; 
	
		return *this;
	}
	
	/**
	 *
	 */
	Block & Block::addCorridor(Corridor &corridor){
		unsigned int i=0; 
		for( ; i<corridors.size() && corridors[i].getId() != corridor.getId(); i++);
		
		if(i != corridors.size())
			this->corridors.push_back(corridor); 
		else 
			this->corridors[i] = corridor; 
		
		
		return *this;
	}
	
	/**
	 *
	 */
	Block & Block::addCurve(Curve & curve){
		
		unsigned int i=0; 
		for( ; i<curves.size() && curves[i].getId() != curve.getId(); i++);
		
		if(i != curves.size())
			this->curves.push_back(curve); 
		else 
			this->curves[i] = curve; 
		
		return *this; 
	} 
		
	/**
	 * Remove (if exists) a shelf in the block 
	 **/
	Block & Block::removeShelf(Shelf &shelf){
		unsigned int i=0; 
		for( ; i<shelves.size() && shelves[i].getId() != shelf.getId(); i++);
		
		if(i != shelves.size())
			this->shelves.erase(this->shelves.begin()+i); 
		
		
		shelvesById.erase(shelf.getId());
		
		return *this; 
	}
	
	/**
	 * Remove (if exists) an exit in the block
	 **/
	Block & Block::removeExit(BlockExit &exit){
		unsigned int i=0; 
		for( ; i<exits.size() && exits[i].getId() != exit.getId(); i++);
		
		if(i != exits.size())
			this->exits.erase(this->exits.begin()+i); 
		
		return *this; 
	}
	
	/**
	 * Remove (if exists) a corridor in the block
	 **/
	Block & Block::removeCorridor(Corridor &corridor){
		
		unsigned int i=0; 
		for( ; i<corridors.size() && corridors[i].getId() != corridor.getId(); i++);
		
		if(i != corridors.size())
			this->corridors.erase(this->corridors.begin()+i); 
		
		return *this; 
	}
	
	/**
	 *	Remove (if exists) a curve on the block
	 **/
	Block & Block::removeCuver(Curve & curve){

		unsigned int i=0; 
		for( ; i<curves.size() && curves[i].getId() != curve.getId(); i++);
		
		if(i != curves.size())
			this->curves.erase(this->curves.begin()+i); 

	
		return *this; 
	}

	/**
	 * Controls if a point is inside or in the border of a block based on the position and size of this block 
	 * @param point Point that will be checked 
	 **/
	bool Block::isInBlock(const Point &point)const{
		return point.getCoordX() >= bottomLeftCoords.first && point.getCoordX() <= bottomLeftCoords.first + width &&
			   point.getCoordY() >= bottomLeftCoords.second && point.getCoordY() <= bottomLeftCoords.second + length;
	}


	/**
	 * Set the block name 
	 * @param name New block name 
	 */
	void Block::setName(const string &name){
		this->name = name; 
	}

	/**
	 *
	 **/
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

	/**
	 *
	 */
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