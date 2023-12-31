#include<iostream>
#include<cmath>
#include<ctime>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include "ExpeditionPoint.h"
using namespace std; 

/**
 *	Default constructor 
 */
ExpeditionPoint::ExpeditionPoint(){
}

/**
 *	Member constructor 
 */
ExpeditionPoint::ExpeditionPoint(string &code, string &blockCode, pair<double,double> coord){
	this->code = code;
	this->blockCode = blockCode;
	this->coordinates = coord; 
}

/**
 *	Copy constructor 
 */
ExpeditionPoint::ExpeditionPoint(const ExpeditionPoint &other){
	this->code = other.code;
	this->blockCode = other.blockCode;
	this->coordinates = other.coordinates;
}


void ExpeditionPoint::setCode(const string code){ this->code = code;}

void ExpeditionPoint::setBlockCode(const string blockCode){ this->blockCode = blockCode;}
void ExpeditionPoint::setCoordinates(const pair<double, double> &coordinates){this->coordinates = coordinates;}
	
string ExpeditionPoint::getCode() const { return this->code; }
string ExpeditionPoint::getBlockCode() const  {return this->blockCode; }
pair<double,double> ExpeditionPoint::getCoordinates() const { return this->coordinates; }