#ifndef ISOLATED_FAMILY_H
#define ISOLATED_FAMILY_H

#include<iostream>
#include<cmath>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
using namespace std;


#define STRONG_ISOLATION "STRONG"
#define WEAK_ISOLATION "WEAK"
#define SHELF_LEVEL "SHELF"
#define CELL_LEVEL "CELL"
#define BLOCK_LEVEL "BLOCK"


class IsolatedFamily{


	private:
		string Force;		///< Strongness of the isolation (STRONG, WEEL)
		string Level;		///< Level of isolation (BLOCK, SHELVE, CELL)
		string Code;		///< Family code'
		
	public:
		IsolatedFamily(){}
		IsolatedFamily(const IsolatedFamily &other);
		IsolatedFamily(string f, string l, string c);
		string getForce() const;
		string getLevel() const;
		string getCode() const;
		void setForce(const string &other);
		void setLevel(const string &other);
		void setCode(const string &other);
		void printIsolatedFamily();
		static vector<IsolatedFamily> readIsolatedFamilyData(ifstream &file);
		bool operator==(const IsolatedFamily &other);
		bool operator<=(const IsolatedFamily &other);
		IsolatedFamily & operator=(const IsolatedFamily & other);
};


#endif