#include<iostream>
#include<cmath>
#include<string>
#include<cstdlib>
#include<vector>
#include<set>
#include<map>
#include<iomanip>
#include "Order.h"
#include "Product.h"
#include "ABCAnalysis.h"
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
 * @param orders List of orders the will be used to proceed the evaluation
 * @param numClasses Number of classes that need to be generated by the analysis
 * @param thresholds List of thresholds to define each class. Those thresholds goes from 0 to 100 and must be in 
 *	      non descending order. The number of thresholds considered will be numClasses - 1
 */
ABCAnalysis::ABCAnalysis(vector<Order> &orders,unsigned int numClasses, vector<double> &thresholds){
    
    unsigned int distinctValues = 0;
    
    this->orders = orders;
    try{
		if(numClasses != thresholds.size()+1)
			throw "The number of thresholds does not is not consistent with the number of classes";


		sort(thresholds.begin(), thresholds.end());
		if(thresholds[0] <= 0)
			throw "All the threshold values must be greater than zero";


		if(thresholds.size()>0)
			distinctValues = 1; 
		else 
			throw "Threshold values vector is empty";

		for(unsigned int i=0; i<thresholds.size()-1; i++){
			if( fabs(thresholds[i]- thresholds[i+1]) >= 1e-3)
				distinctValues++;
		}

		if(distinctValues < thresholds.size())
			throw "The threshold vector has some repeated values";
		else if(distinctValues + 1 != numClasses)
			throw "The number of classes and the number of distinct thersholds are not consistent";
	}catch(const char* message){
		
		cout<<message<<endl;
	}

    this->numClasses = numClasses; 
    this->thresholds = thresholds; 
}

/**
 * Execute the assignment of classes to the products. 
 * The frequence class is assigned according to the relative frequence when compared with the number of orders. In
 * this case, the number of products by order is not considered. 
 * The volume class is assigned according to the total product volume compared with the total volume of all orders
 */
void ABCAnalysis::execute(){

    map<Product,int> productFrequences;
    map<Product, double> productVolumes;
    set<Product> products; 
    double totalVolume = 0;
    int totalFrequence = 0; 

    if(thresholds.size() == 0)
        throw "The thresholds must be setted before start this method";
    if(thresholds[0] <0 )
        throw "The thresholds must be setted before start this method";
    if(numClasses-1 != thresholds.size())
        throw "The number of classes and the number of thresholds are not consistent";
    //Get the frequences and volumes of all products
    for(unsigned int i=0; i<this->orders.size();i++){
        vector< pair<Product, double> > items = this->orders[i].getOrderItems();
		totalFrequence += items.size();
        
        for(unsigned int j=0; j<items.size(); j++){
            totalVolume += items[j].second;
            if(products.find(items[j].first) == products.end()){
                products.insert(items[j].first);
                productFrequences[items[j].first] = 1; 
                productVolumes[items[j].first] = items[j].second;
        
            }else{
                productFrequences[items[j].first]++;
                productVolumes[items[j].first]+= items[j].second;
            }
        }
    }

    //Sort the products by frequence and volume
    vector<pair<int,Product> > frequences;
    vector<pair<double, Product> > volumes;

    for(map<Product, int>::iterator it= productFrequences.begin(); it!= productFrequences.end(); it++)
        frequences.push_back(make_pair(it->second, it->first));

    for(map<Product, double>::iterator it= productVolumes.begin(); it!= productVolumes.end(); it++){
        volumes.push_back(make_pair(it->second, it->first));
	}

    //The products must be ordered in decreasing order because the most frequent/volumous products should 
    //be evaluated first 
    sort(frequences.begin(), frequences.end(), [](const pair<int,Product> &a, const pair<int,Product>& b) {return a.first < b.first;});
    reverse(frequences.begin(), frequences.end());
    sort(volumes.begin(), volumes.end(), [](const pair<double,Product> &a, const pair<double,Product>& b) {return a.first < b.first;});
    reverse(volumes.begin(), volumes.end());

    //Compute the thresholds that will be used on the classification
    vector<double> volumeThresholds; 
    vector<int> frequenceThresholds;
    double accumVolume=0;
    double accumFrequence=0; 

    for(unsigned int i=0;i<numClasses; i++){
        //The thresholds are evaluated based on the total frequence/volume
        volumeThresholds.push_back(totalVolume*this->thresholds[i]*1.0/100.0);
        frequenceThresholds.push_back(totalFrequence*this->thresholds[i]*1.0/100.0);
    }

	for(unsigned int i=0;i<numClasses;i++){
		cout<<"Volume: "<<volumeThresholds[i]<<" Frequence: "<<frequenceThresholds[i]<<endl;
	}

    //Assign the classes. 
    char currentVolumeClass = 'A';
    unsigned int currentVolumeClassIndex = 0;
    char currentFrequenceClass = 'A';
    unsigned int currentFrequenceClassIndex = 0;
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

		this->volumeClasses[volumes[i].second] = currentVolumeClass;
		this->frequenceClasses[frequences[i].second] = currentFrequenceClass;
    }
}


void ABCAnalysis::printClassification(){
	
	set<Product> products;
	for(map<Product, char>::iterator it = volumeClasses.begin(); it != volumeClasses.end(); it++) products.insert(it->first);
	for(map<Product, char>::iterator it = frequenceClasses.begin(); it != frequenceClasses.end(); it++) products.insert(it->first);
	
	
	cout<<setw(50)<<"Product "<<setw(15)<<"Freq. Class" << setw(15)<<"Vol. Class."<<endl;
	cout<<"================================================================================\n";
	for(set<Product>::iterator it = products.begin(); it != products.end();it++){
		cout<<it->getID()<<" ";
		
		if(frequenceClasses.find(*it) != frequenceClasses.end())
			cout<<frequenceClasses[*it]<<" ";
		if(volumeClasses.find(*it) != volumeClasses.end())
			cout<<volumeClasses[*it]<<" ";
		cout<<endl; 
	}
	
}



/**
 * Set the orders that will be used in the analysis 
 */
void ABCAnalysis::setOrders(vector<Order> &orders){
    this->orders = orders;
}

/**
 * Set the number of classes and resize the threshold vector to receive the values
 * You must always set the threshold values BEFORE call the method Execute
 * @param num Number of classes 
 */
void ABCAnalysis::setNumClasses(int num){
    this->numClasses = num; 
    this->thresholds.resize(numClasses-1,-1);
}

/**
 * Set the thresholds of classes and set the number of classes
 * If some threshold value is lower or equal than zero, the vector is empty or a value is repeated
 * the function will throw an exception. 
 * minDelta >= 1e-3
 */
void ABCAnalysis::setThresholds(vector<double>& thre){

    sort(thre.begin(), thre.end());
    unsigned int distinctValues = 0; 
    if(thre[0] <= 0)
        throw "All the threshold values must be greater than zero";


    if(thre.size()>0)
        distinctValues = 1; 
    else 
        throw "Threshold values vector is empty";

    for(unsigned int i=0; i<thre.size()-1; i++)
        if( fabs(thre[i]- thre[i+1]) >= 1e-3)
            distinctValues++;
    
    if(distinctValues <= thre.size())
        throw "The threshold vector has some repeated values";


    this->thresholds = thre;
    this->numClasses = thre.size()+1; 
}



/**
 * Return all the orders that were used in the ABC analysis
 */
vector<Order> ABCAnalysis::getOrders() const {
    return this->orders; 
}

/**
 * Get the classes by volume of all products 
 */
map<Product,char> ABCAnalysis::getVolumeClasses() const{
    return this->volumeClasses;
}

/**
 * Get the total volume of all products
 */
map<Product, double> ABCAnalysis::getProductVolumes() const{
	return productVolumes;
}


/**
 * Get the classes by frequence of all products  
 */
map<Product,char> ABCAnalysis::getFrequenceClasses() const{
    return this->frequenceClasses; 
}

/**
 * Get all the product frequencies 
 */
map<Product, int> ABCAnalysis::getProductFrequences() const{
	return productFrequences; 
}

