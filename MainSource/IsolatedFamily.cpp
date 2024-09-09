#include "IsolatedFamily.h"
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<fstream>
using std::cout;
using std::endl;
using std::ifstream;

IsolatedFamily::IsolatedFamily(const IsolatedFamily &other){
	this->Force = other.Force;
	this->Level = other.Level;
	this->Code = other.Code; 
}

IsolatedFamily::IsolatedFamily(string f, string l, string c){
	this->Force = f;
	this->Level = l;
	this->Code = c; 
}

string IsolatedFamily::getForce() const{ return this->Force; }

string IsolatedFamily::getLevel() const{ return this->Level; }

string IsolatedFamily::getCode() const{ return this->Code; }

void IsolatedFamily::setForce(const string &other){
	if(other == "STRONG" || other == "WEAK")
		this->Force = other;
}

void IsolatedFamily::setLevel(const string &other){
	this->Level = other;
}

void IsolatedFamily::setCode(const string &other){
	this->Code = other;
}

void IsolatedFamily::printIsolatedFamily(){
	cout<<"___________________________________\n";
	cout<<"Printing Isolated Family information";
	cout<<this->Code<<" "<<this->Level<<" "<<this->Code<<endl; 
}

vector<IsolatedFamily> IsolatedFamily::readIsolatedFamilyData(ifstream &file){
	vector<IsolatedFamily> returned;
	int numIsolations;
	string c, f, l;
	
	file>>numIsolations;
	for(int i=0;i<numIsolations;i++){
		file>>l>>c>>f;
		returned.push_back(IsolatedFamily(f,l,c));
	}

	return returned; 
}

bool IsolatedFamily::operator==(const IsolatedFamily &other){
	return this->Force == other.Force && this->Code == other.Code && this->Level == other.Level; 
}
bool IsolatedFamily::operator<=(const IsolatedFamily &other){
	return this->Code+this->Level+this->Force <= other.Code+other.Level+other.Force;
}

IsolatedFamily & IsolatedFamily::operator=(const IsolatedFamily & other){
	this->Force = other.Force;
	this->Level = other.Level;
	this->Code = other.Code; 
	
	return *this;
}

bool IsolatedFamily::isLowerOrEqualLevel(string firstLevel,string secondLevel){

	if(firstLevel != CELL_LEVEL && firstLevel != SHELF_LEVEL && firstLevel != BLOCK_LEVEL){
		return false; 
	}if(secondLevel != CELL_LEVEL && secondLevel != SHELF_LEVEL && secondLevel != BLOCK_LEVEL){
		return false; 
	}
	
	if(firstLevel == CELL_LEVEL){
		return true;
	}if((firstLevel == SHELF_LEVEL) && (secondLevel == CELL_LEVEL || secondLevel == BLOCK_LEVEL)){
		return true;
	}if(firstLevel == BLOCK_LEVEL && secondLevel == BLOCK_LEVEL){
		return true;
	}
	return false; 

}