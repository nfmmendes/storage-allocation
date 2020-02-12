#ifndef ABC_ANALYSIS_H
#define ABC_ANALYSIS_H


#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<vector>
#include<set>
#include<map>
#include "Order.h"
#include "Product.h"
using namespace std;

/**
 * This class performs a generalized ABC class analysis, where we can assign one between any number of classes 
 * to a product based in its frequence or in its volume
 */
class ABCAnalysis{

    private:
        map<Product, char> volumeClasses;			///< Store the volume class by product 
		map<Product, double> productVolumes;		///< Store the volume by product
		map<Product, char> frequenceClasses;		///< Store the frequence by classes 
		map<Product, int> productFrequences; 		///< Store the product frequences 
		vector<Order> orders;						///< Store the orders 
        unsigned int numClasses;					///< Store the number of classes
        vector<double> thresholds; 					///< Store the thresholds used to divide the classes 

    public: 
        ABCAnalysis();
        ABCAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
        void execute();
		void printClassification();
        void setOrders(vector<Order> &orders);
        void setNumClasses(int num);
        void setThresholds(vector<double> &thre);
        vector<Order> getOrders() const;
        map<Product,char> getVolumeClasses() const;
		map<Product, double> getProductVolumes() const;
        map<Product,char> getFrequenceClasses() const;
		map<Product, int> getProductFrequences() const; 
        int getNumClasses() const;
        vector<double> getThresholds() const;

};




#endif