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
 * 
 */
ABCAnalysis::ABCAnalysis(){

}

/**
 * Full constructor to the ABC class analysis. 
 * This constructor validates the thresholds and the number of classes. If the threshold vector has 
 * repeated values or if the number of (distinct) elemens in the vector plus one is different than the
 * number of classes a exception will be thrown. Take care and use a try-catch statement when you use
 * this constructor
 */
ABCAnalysis::ABCAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds){
    
    int distinctValues = 0;
    
    this->orders = orders;
    
    if(numClasses != thresholds.size()+1)
        throw Exception("The number of thresholds does not is not consistent with the number of classes");
    

    sort(thresholds.begin(), thresholds.end());
    if(thresholds[0] <= 0)
        throw Exception("All the threshold values must be greater than zero");


    if(thresholds.size()>0)
        distinctValues = 1; 
    else 
        throw Exception("Threshold values vector is empty");

    for(int i=0; i<thresholds.size()-1; i++)
        if( fabs(thresholds[i]- thresholds[i+1]) >= 1e-3)
            distinctValues++;
    
    if(distinctValues <= threshold.size())
        throw Exception("The threshold vector has some repeated values");
    else if(distinctValues + 1 != numClasses)
        throw Exception("The number of classes and the number of distinct thersholds are not consistent");

    this->numClasses = numClasses; 
    this->thresholds = thresholds; 
}

/**
 * Execute the assignment of classes to the products. 
 * The frequence class is assigned according to the relative frequence when compared with the number of orders. In
 * this case, the number of products by order is not considered. 
 * The volume class is assigned according to the total product volume compared with the total volume of all orders
 */
void ABCAnalysis::Execute(){

    map<Product,int> frequenceByProduct;
    map<Product, double> volumeByProduct;
    set<Product> products; 
    double totalVolume = 0;
    int totalFrequence =this->orders.size(); 

    if(thresholds.size() == 0)
        throw Exception("The thresholds must be setted before start this method");
    if(thresholds[0] <0 )
        throw Exception("The thresholds must be setted before start this method");
    if(numClasses-1 != thresholds.size())
        throw Exception("The number of classes and the number of thresholds are not consistent");

    //Get the frequences and volumes of all products
    for(unsigned int i=0; i<this->orders.size()){
        vector< pair<Product, double> > items = this->orders[i].getOrderItems();
        for(int j=0; j<items.size(); j++){
            totalVolume*= items[j].second;
            if(products.find(this->items[j].first) == products.end()){
                products.insert(this->items[j].first);
                frequenceByProduct[this->items[j].first] = 1; 
                volumeByProduct[this->items[j].first] = this->items[i].second;
            }else{
                frequenceByProduct[items[j].first]++;
                frequenceByProduct[items[j].first]+= items[j].second;
            }
        }
    }

    //Sort the products by frequence and volume
    vector<pair<int,Product> > frequences;
    vector<pair<double, Product> > volumes;

    for(map<Product, int>::iterator it= frequenceByProduct.begin(); it!= frequenceByProduct.end(); it++)
        frequences.push_back(make_pair(it->second, it->first));

    for(map<Product, double>::iterator it= volumeByProduct.begin(); it!= volumeByProduct.end(); it++)
        volumes.push_back(make_pair(it->second, it->first));

    //The products must be ordered in decreasing order because the most frequent/volumous products should 
    //be evaluated first 
    sort(frequences.begin(), frequences.end());
    reverse(frequences.begin(), frequences.end());
    sort(volumes.begin(), volumes.end());
    reverse(volumes.begin(), volumes.end());


    //Compute the thresholds that will be used on the classification
    vector<double> volumeThresholds; 
    vector<int> frequenceThresholds;
    double acumVolume=0;
    double acumFrequence=0; 

    for(unsigned int i=0;i<numberOfClasses; i++){
        //The thresholds are evaluated based on the total frequence/volume
        volumeThresholds.push_back(totalVolume*this->thresholds[i]/100.0);
        frequenceThresholds.push_back(totalFrequence*this->thresholds[i]/100.0);
    }

    //Assign the classes. 
    char currentVolumeClass = 'A';
    int currentVolumeClassIndex = 0;
    char currentFrequenceClass = 'A';
    int currentFrequenceClassIndex = 0;
    for(unsigned int i=0; i<products.size(); i++){
        accumVolume += volumes[i].first;
        accumFrequence += frequences[i].first;
        //Always remember. The number of thresholds is one unit lower than the number of classes
        //If the accumulated volume is bigger than the current threshold we should go to the next threshold/class
        if(currentVolumeClassIndex < numClasses-1 && accumVolume >= volumeThresholds[currentVolumeClassIndex]){            
            currentVolumeClass++; 
            currentVolumeClassIndex++;
        }        

        if(currentFrequenceClassIndex < numClasses-1 && accumFrequence >= frequenceThresholds[currentFrequenceClassIndex]){
            currentFrequenceClass++;
            currentFrequenceClassIndex++;
        }

        this->volumeClasses[volume[i].second] = currentVolumeClass;
        this->frequenceClass[frequence[i].second] = currentFrequenceClass;
    }

}

/**
 * 
 */
void ABCAnalysis::setOrders(vector<Orders> &orders){
    this->orders = orders;
}

/**
 * Set the number of classes and resize the threshold vector to receive the values
 * You must always set the threshold values BEFORE call the method Execute
 */
void ABCAnalysis::setNumClasses(int num){
    this->numClasses = numClasses; 
    this->thresholds.resize(numClasses-1,-1);
}

/**
 * Set the thresholds of classes and set the number of classes
 * If some threshold value is lower or equal than zero, the vector is empty or a value is repeated
 * the function will throw an exception. 
 * minDelta >= 1e-3
 */
void ABCAnalysis::setThresholds(vector<double> & thre){

    sort(thre.begin(), thre.end());
    int distinctValues = 0; 
    if(thre[0] <= 0)
        throw Exception("All the threshold values must be greater than zero");


    if(thre.size()>0)
        distinctValues = 1; 
    else 
        throw Exception("Threshold values vector is empty");

    for(int i=0; i<thre.size()-1; i++)
        if( fabs(thre[i]- thre[i+1]) >= 1e-3)
            distinctValues++;
    
    if(distinctValues <= thre.size())
        throw Exception("The threshold vector has some repeated values");


    this->thresholds = thre;
    this->numClasses = thre.size()+1; 
}



/**
 * 
 */
vector<Order> ABCAnalysis::getOrders(){
    return this->orders; 
}

/**
 * 
 */
map<Product,char> ABCAnalysis::getVolumeClasses(){
    return this->volumeClasses;
}

/**
 * 
 */
map<Product,char> ABCAnalysis::getFrequenceClasses(){
    return this->frequenceClasses; 
}
