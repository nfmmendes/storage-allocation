#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>


#define STRONG_ISOLATION "STRONG"
#define WEAK_ISOLATION "WEAK"
#define SHELF_LEVEL "SHELF"
#define CELL_LEVEL "CELL"
#define BLOCK_LEVEL "BLOCK"


class IsolatedFamily{


	private:
		std::string Force;		///< Strongness of the isolation (STRONG, WEEL)
		std::string Level;		///< Level of isolation (BLOCK, SHELVE, CELL)
		std::string Code;		///< Family code'
		
	public:
		IsolatedFamily(){}
		IsolatedFamily(const IsolatedFamily &other);
		IsolatedFamily(std::string f, std::string l, std::string c);
		std::string getForce() const;
		std::string getLevel() const;
		std::string getCode() const;
		void setForce(const std::string &other);
		void setLevel(const std::string &other);
		void setCode(const std::string &other);
		void printIsolatedFamily();
		static std::vector<IsolatedFamily> readIsolatedFamilyData(std::ifstream &file);
		bool operator==(const IsolatedFamily &other);
		bool operator<=(const IsolatedFamily &other);
		IsolatedFamily & operator=(const IsolatedFamily & other);
		static bool isLowerOrEqualLevel(std::string fisrtLevel, std::string secondLevel);
};
