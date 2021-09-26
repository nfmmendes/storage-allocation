#pragma once

#include<iostream>
#include<cstdlib>
#include<vector>
#include<map>
#include "Order.h"
#include "Product.h"

/**
 * This class performs a generalized ABC class analysis, where we can assign one between any number of classes 
 * to a product based in its frequence or in its volume
 */
class ABCAnalysis{

    private:
        std::map<Product, char> volumeClasses;			///< Store the volume class by product 
		std::map<Product, double> productVolumes;		///< Store the volume by product
		std::map<Product, char> frequenceClasses;		///< Store the frequence by classes 
		std::map<Product, int> productFrequences; 		///< Store the product frequences 
		std::vector<Order> orders;						///< Store the orders 
        unsigned int numClasses;					    ///< Store the number of classes
        std::vector<double> thresholds; 				///< Store the thresholds used to divide the classes 

    public: 
        ABCAnalysis();
        ABCAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
        void execute();
		void printClassification();
        void setOrders(vector<Order> &orders);
        void setNumClasses(int num);
        void setThresholds(vector<double> &thre);
        std::vector<Order> getOrders() const;
        std::map<Product,char> getVolumeClasses() const;
		std::map<Product, double> getProductVolumes() const;
        std::map<Product,char> getFrequenceClasses() const;
		std::map<Product, int> getProductFrequences() const; 
        int getNumClasses() const;
        std::vector<double> getThresholds() const;

};
