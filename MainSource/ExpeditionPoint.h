#pragma once

#include<iostream>
#include<string>
#include<utility> 
using std::string;
using std::pair;

/**
 * @brief Class <c> Expedition Point </c> represents a delivery/expedition point in a warehouse. 
 */
class ExpeditionPoint{

	private: 
		string code {};							///< Code of the expedition point.
		string blockCode {};					///< Code of block where is located the expedition point (or from where the products come).
		pair<double,double> coordinates {};		///< Coordinates of expedition point.
	
	public:
		/**
		 * @brief Constructor.
		 * @param code Expedition point code.
		 * @param blockCode Code of the block in which is located the expedition point.
		 * @param coord The expedition point coordinate. 
		 */
		ExpeditionPoint(const string &code, const string &blockCode, const pair<double,double>& coord);

		/**
		 * @brief Copy constructor.
		 * @param other The point to be copied. 
		*/
		ExpeditionPoint(const ExpeditionPoint &other);
		
		/**
		 * @brief Get the expedition point code. 
		 * @return The expedition point code. 
		 */
		const string& getCode() const;

		/**
		 * @brief The expedition point block code.
		 * @return The expedition point block code.
		 */
		const string& getBlockCode() const;

		/**
		 * @brief Get the expedition point coordinates.
		 * @return The expedition point coordinates. 
		 */
		const pair<double,double>& getCoordinates() const;
};
