#pragma once

#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include "Order.h"
#include "Product.h"
using std::map;
using std::vector;

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
        unsigned int numClasses;					    ///< Store the number of classes
        vector<double> thresholds; 				///< Store the thresholds used to divide the classes 

    public: 
        ABCAnalysis();
        ABCAnalysis(const vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
        void execute();
		void printClassification() const;
        void setOrders(vector<Order> &orders);
        void setNumClasses(int num);
        void setThresholds(vector<double> &thre);
        vector<Order> getOrders() const;
        const map<Product,char>& getFrequenceClasses() const;
        int getNumClasses() const;
        vector<double> getThresholds() const;

};
