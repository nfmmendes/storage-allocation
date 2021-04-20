#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include<iostream>
#include<map>
#include<vector>
#include<cmath>
#include<iomanip>
#include<set>
#include<map>
using namespace std; 


template <class T> 
class DistanceMatrix{

    private: 
        vector<T> orderedKeys; 
        map<T, int> keyIndex; 
        vector<vector<double> > distances;
    public:
        DistanceMatrix(){}
        DistanceMatrix(DistanceMatrix<T> & other);
		DistanceMatrix(map<pair<T,T> , double> & distances);  
		DistanceMatrix<T> & buildMatrix(map<pair<T,T> , double> & distances);
        vector<T> & getKeys();
        vector<vector< double > > getDistances()const;
        map<T, int> getElementsMap() const;
        double getDistance(const T &first,const T &second) const; 
        void setRow(vector<double> &d, T &);
        void setColumn(vector<double> &d, T&) ;
        void setRowOnIndex(vector<double> &d, int) ;
        void setColumnOnIndex(vector<double> &d, int);
		DistanceMatrix<T> & operator=(DistanceMatrix<T> &other); 
		void print(); 
};


template<class T>
DistanceMatrix<T>::DistanceMatrix(map<pair<T,T> , double> & distancesPairs){
	this->buildMatrix(distancesPairs);
}

template<class T> 
DistanceMatrix<T> & DistanceMatrix<T>::buildMatrix(map<pair<T,T> , double> &distancesPairs){
	set<T> keys; 

	for(auto &mapPair : distancesPairs){
		keys.insert(mapPair.first.first);
		keys.insert(mapPair.first.second); 
	}
	
	T aux; 
	for(auto it = keys.begin(); it != keys.end();it++){
		keyIndex[*it] = orderedKeys.size();
		aux = *it; 
		orderedKeys.push_back(aux); 
	}
	
	distances.resize(orderedKeys.size());
	for(unsigned int i=0;i<distances.size(); i++)
		distances[i].resize(distances.size()); 
	
	int firstIndex, secondIndex; 
	for(const auto & pair : distancesPairs){
		firstIndex = keyIndex[pair.first.first]; 
		secondIndex = keyIndex[pair.first.second]; 
		
		distances[firstIndex][secondIndex] = pair.second; 	
	}
	
	return *this; 
}




template<class T>
DistanceMatrix<T>::DistanceMatrix(DistanceMatrix<T> & other){

    for(unsigned int i=0; i<other.orderedKeys.size();i++)
        this->orderedKeys.push_back(other.orderedKeys[i]);

    this->distances.resize(orderedKeys.size());
    for(unsigned int i=0; i< orderedKeys.size(); i++){
        this->distances[i].resize(orderedKeys.size());

        for(unsigned int j=0; j<orderedKeys.size();j++)
            this->distances[i][j] = other.distances[i][j]; 
    }

    for(unsigned int i=0; i<this->orderedKeys.size(); i++)
        this->keyIndex[orderedKeys[i]] = i; 
}


template<class T>
DistanceMatrix<T> & DistanceMatrix<T>::operator=(DistanceMatrix<T> &other){
	
	this->orderedKeys.clear(); 
	for(unsigned int i=0; i<other.orderedKeys.size();i++)
        this->orderedKeys.push_back(other.orderedKeys[i]);

    this->distances.resize(orderedKeys.size());
    for(unsigned int i=0; i< orderedKeys.size(); i++){
        this->distances[i].resize(orderedKeys.size());

        for(unsigned int j=0; j<orderedKeys.size();j++)
            this->distances[i][j] = other.distances[i][j]; 
    }

	this->keyIndex.clear();
	for(unsigned int i=0; i<this->orderedKeys.size(); i++)
        this->keyIndex[orderedKeys[i]] = i; 
	
	return *this;
}



template<class T>
map<T, int> DistanceMatrix<T>::getElementsMap() const {
    return keyIndex;
}

template<class T>
vector<vector< double > > DistanceMatrix<T>::getDistances() const {
    return distances; 
}

template<class T>
vector<T> & DistanceMatrix<T>::getKeys() {
    return orderedKeys; 
}


template<class T>
double DistanceMatrix<T>::getDistance(const T &first,const T &second) const {
	
    auto itFirst = keyIndex.find(first);
    auto itSecond = keyIndex.find(second);
	
	try{
		if(itFirst != keyIndex.end() && itSecond!= keyIndex.end())
			return distances[itFirst->second][itSecond->second] ;
	}catch(const std::out_of_range& oor){
		cerr<<"There is a error here! Function return 1e5"<<endl;
		return 1e5;
	}
	
	return -1;
}

template<class T>
void DistanceMatrix<T>::setRow(vector<double> &d, T &elem) {
    typename std::vector<T>::iterator itFirst = keyIndex.find(elem);
    if(itFirst != orderedKeys.end()){
        int index = keyIndex[itFirst];
        int maxAdvance = min(orderedKeys.size(), distances.size());
        for(int i=0; i<maxAdvance; i++)
            orderedKeys[index][i] = d[i];
    }
}

template<class T>
void DistanceMatrix<T>::setColumn(vector<double> &d, T&elem) {
    typename std::vector<T>::iterator itFirst = keyIndex.find(elem);
    if(itFirst != orderedKeys.end()){
        int index = keyIndex[itFirst];
        int maxAdvance = min(orderedKeys.size(), distances.size());
        for(int i=0; i<maxAdvance; i++)
            orderedKeys[i][index] = d[i];
    }
}

template<class T>
void DistanceMatrix<T>::setRowOnIndex(vector<double> &d, int index)  {
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for(int i=0; i<maxAdvance; i++)
        orderedKeys[index][i] = d[i];
}

template<class T>
void DistanceMatrix<T>::setColumnOnIndex(vector<double> &d, int index)  {
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for(int i=0; i<maxAdvance; i++)
        orderedKeys[i][index] = d[i];
}


template<class T> 
void DistanceMatrix<T>::print(){
	
	cout<<setw(15)<<"****************\n"; 
	for(unsigned int i=0;i<orderedKeys.size();i++){
		cout<<setw(15)<<orderedKeys[i]<<endl;
	}
	
	for(unsigned int i=0; i< orderedKeys.size();i++){
		int indexI = keyIndex[orderedKeys[i]]; 
		for(unsigned int j=0; j< orderedKeys.size();j++)
			cout<<setw(15)<<distances[indexI][keyIndex[ orderedKeys[j] ] ];
		cout<<endl; 
		
	}
		
	
}

#endif