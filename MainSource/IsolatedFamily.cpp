#include "IsolatedFamily.h"
#include<iostream>
#include<cmath>
#include<cstdlib>
#include<cassert>
#include<string>
#include<map>
#include<fstream>
using std::cout;
using std::map;
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

const string& IsolatedFamily::getForce() const{ return this->Force; }

const string& IsolatedFamily::getLevel() const{ return this->Level; }

const string& IsolatedFamily::getCode() const{ return this->Code; }

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

IsolatedFamily & IsolatedFamily::operator=(const IsolatedFamily & other){
	this->Force = other.Force;
	this->Level = other.Level;
	this->Code = other.Code; 
	
	return *this;
}

bool IsolatedFamily::isLowerOrEqualLevel(string firstLevel,string secondLevel){

	assert(firstLevel == CELL_LEVEL || firstLevel == SHELF_LEVEL || firstLevel == BLOCK_LEVEL );
	assert(secondLevel == CELL_LEVEL || secondLevel == SHELF_LEVEL || secondLevel == BLOCK_LEVEL );

	const static map<string, int> levelValues = { 
		{CELL_LEVEL, 0},
		{SHELF_LEVEL, 1},
		{BLOCK_LEVEL, 2}
	};

	return levelValues.at(firstLevel) <= levelValues.at(secondLevel); 

}