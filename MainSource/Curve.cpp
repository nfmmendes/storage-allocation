#include "Curve.h"
using std::cout;
using std::endl;

/**
 *	Default constructor 
 */
Curve::Curve(){}

/**
 *	Copy constructor 
 */
Curve::Curve(const Curve & other){
    this->Id = other.Id;
    this->startingPoint = other.startingPoint;
    this->endingPoint = other.endingPoint;
    this->startingCorridorId = other.startingCorridorId;
    this->endingCorridorId = other.endingCorridorId;
    
}

/**
 * Member constructor 
 * @param id Curve id
 * @param startingCorridor Id of corridor where the curve starts 
 * @param endingCorridor Id of corridor where the curve ends 
 * @param startingPoint The begining curve coordinates 
 * @param endingPoint The ending curve coordinates 
 */
Curve::Curve(long int id, long int startingCorridor, long int endingCorridor, Point startingPoint, Point endingPoint){
    this->Id = id;
    this->startingCorridorId = startingCorridor;
    this->endingCorridorId = endingCorridor;
    this->startingPoint = startingPoint;
    this->endingPoint = endingPoint;
}

long int Curve::getStartCorridor() const { return startingCorridorId; }
long int Curve::getEndCorridor() const { return endingCorridorId; }
Point Curve::getStartingPoint() const { return startingPoint;}
Point Curve::getEndingPoint() const { return endingPoint; }
long int Curve::getId()const{ return Id; }

/**
 * Assignment operator overload 
 * @param other The curve in the right side of operator that will pass its value to the other object  
 */
Curve & Curve::operator=(const Curve &other){
    this->Id = other.Id;
    this->startingCorridorId = other.startingCorridorId;
    this->endingCorridorId = other.endingCorridorId;
    this->startingPoint = other.startingPoint;
    this->endingPoint = other.endingPoint;
    
    return *this;
}

/**
 * Equals operator overload 
 * @param other Curve in the right hand side of the operator 
 */
bool Curve::operator==(const Curve &other) const {
	return this->Id == other.Id && this->startingCorridorId == other.startingCorridorId && this->endingCorridorId == other.endingCorridorId && 
		   this->startingPoint == other.startingPoint && this->endingPoint == other.endingPoint;
}

/**
 *	Not equal operator overload 
 * @param other Curve in the right hand side of the operator 
 */
bool Curve::operator!=(const Curve &other) const {
	return !(*this == other);
}



/**
 * Less operator overload 
 * @param other Curve in the right hand side of the operator 
 */
bool Curve::operator<(const Curve &other) const{
	if(this->startingPoint > other.startingPoint)
		return false;
	else
		return this->startingPoint < other.startingPoint || this->endingPoint < other.endingPoint; 
}

/**
 * Print main informations about the curve
 */
void Curve::printCurveInformation(){
	
	cout<<"____________________________________\n";
	cout<<"Curve: \t"<<this->Id <<endl;
	cout<<"Starting corridor: \t"<<this->startingCorridorId<<"\t"<<"Ending corridor \n"<<endl; 
	cout<<"Starting point: (x=\t"<<this->startingPoint.getCoordX()<<", y="<<this->startingPoint.getCoordY()<<")";
	cout<<"Ending point: (x=\t"<<this->endingPoint.getCoordX()<<", y="<<this->endingPoint.getCoordY()<<")\n";
	cout<<"____________________________________\n";
}