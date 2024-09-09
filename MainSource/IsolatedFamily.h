#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
using std::string;
using std::vector;
using std::ifstream;

#define STRONG_ISOLATION "STRONG"
#define WEAK_ISOLATION "WEAK"
#define SHELF_LEVEL "SHELF"
#define CELL_LEVEL "CELL"
#define BLOCK_LEVEL "BLOCK"

 /**
 * @brief Class <c> IsolatedFamily <c> holds the data and functions needed to represent
 * a family isolation inside the warehouse. 
 */ 
class IsolatedFamily{


	private:
		string Force;		///< Strongness of the isolation (STRONG, WEEL)
		string Level;		///< Level of isolation (BLOCK, SHELVE, CELL)
		string Code;		///< Family code'
		
	public:
		/**
		 * @brief Constructor.
		 */
		IsolatedFamily(){}

		/**
		 * @brief Copy constructor.
		 * @param other Object to be copied.
		 */
		IsolatedFamily(const IsolatedFamily &other);
		
		/**
		 * @brief Constructor.
		 * @param force The isolation force (STRONG or WEAK)
		 * @param level The isolation level (CELL, SHELF, BLOCK)
		 * @param code The family code.
		 */
		IsolatedFamily(string force, string level, string code);
		
		/**
		 * @brief Get the isolation force.
		 * @return The isolation force.
		 */
		string getForce() const;
		
		/**
		 * @brief Get the isolation level.
		 * @return The isolation level.
		*/
		string getLevel() const;
		
		/**
		 * @brief Get the family code.
		 * @return The family code.
		 */
		string getCode() const;
		
		/**
		 * @brief Set the isolation force.
		 * @param other The isolation force.
		 */
		void setForce(const string &other);
		
		/**
		 * @brief Set the isolation level.
		 * @param other The isolation level.
		 */
		void setLevel(const string &other);
		
		/**
		 * @brief Set the family code.
		 * @param other The family code.
		 */
		void setCode(const string &other);
		
		/**
		 * @brief Print isolation information. 
		 */
		void printIsolatedFamily();
		
		/**
		 * @brief Read isolation data from a file.
		 * @param file The file name with isolation data. 
		 * @return A list of isolated families, with their respective isolation force and levels.
		 */ 
		static vector<IsolatedFamily> readIsolatedFamilyData(ifstream &file);
		
		/**
		 * @brief The equality operator override.  
		 * @param other The right hand side object.
		 * @return True if the two object are considered equals. False otherwise. 
		 */
		bool operator==(const IsolatedFamily &other);
		
		/**
		 * @brief The less than or equal operator override.  
		 * @param other The right hand side object.
		 * @return True if the left hand side object is considered less than or equal to the
		 * 			right hand side object. False otherwise. 
		 */
		bool operator<=(const IsolatedFamily &other);
		
		/**
		 * @brief The assignment operator override.
		 * @param other The object to be assigned to the left hand side object. 
		 * @return A reference to the modified left hand side object. 
		 */
		IsolatedFamily & operator=(const IsolatedFamily & other);
		
		/**
		 * @brief Compare two isolation levels. 
		 * @param fisrtLevel The first isolation level.
		 * @param secondLevel The second isolation level.
		 * @return True if the first isolation level is less than or equal to the second level
		 * 			object. False otherwise. 
		 */
		static bool isLowerOrEqualLevel(string fisrtLevel, std::string secondLevel);
};
