#pragma once

#include<iostream>
#include<string>
#include<utility> 

class ExpeditionPoint{

	private: 
		std::string code;							///< Code of the expedition point 
		std::string blockCode;						///< Code of block where is located the expedition point (or from where the products come) 
		std::pair<double,double> coordinates;		///< Coordinates of expedition point 
	
	public:
		ExpeditionPoint();
		ExpeditionPoint(std::string &code, std::string &blockCode, std::pair<double,double> coord);
		ExpeditionPoint(const ExpeditionPoint &other);
		
		void setCode(const std::string code);
		void setBlockCode(const std::string blockCode);
		void setCoordinates(const std::pair<double, double> &coordinates);
		
		std::string getCode() const;
		std::string getBlockCode() const;
		std::pair<double,double> getCoordinates() const;
	
};
