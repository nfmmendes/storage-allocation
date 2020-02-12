#ifndef EXPEDITION_POINT_H
#define EXPEDITION_POINT_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<string>
#include<utility>
using namespace std; 

class ExpeditionPoint{

	private: 
		string code;							///< Code of the expedition point 
		string blockCode;						///< Code of block where is located the expedition point (or from where the products come) 
		pair<double,double> coordinates;		///< Coordinates of expedition point 
	
	public:
		ExpeditionPoint();
		ExpeditionPoint(string &code, string &blockCode, pair<double,double> coord);
		ExpeditionPoint(const ExpeditionPoint &other);
		
		void setCode(const string code);
		void setBlockCode(const string blockCode);
		void setCoordinates(const pair<double, double> &coordinates);
		
		string getCode() const;
		string getBlockCode() const;
		pair<double,double> getCoordinates() const;
	
};


#endif