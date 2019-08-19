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
        map<Product, char> volumeClasses;
        map<Product, char> frequenceClasses;
        vector<Order> orders;
        unsigned int numClasses;
        vector<double> thresholds; 

    public: 
        ABCAnalysis();
        ABCAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds);
        void Execute();
        void setOrders(vector<Orders> &orders);
        void setNumClasses(int num);
        void setThresholds(vector<double> thre);
        vector<Order> getOrders() const;
        map<Product,char> getVolumeClasses() const;
        map<Product,char> getFrequenceClasses() const;
        int getNumClasses() const;
        vector<double> getThresholds() const;

}




#endif