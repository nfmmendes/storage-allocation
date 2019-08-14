#include<iostream>
#include<map>
#include<vector>
#include<functional>
#include<cmath>
#include<algorithm>
#include "DistanceMatrix.h"
using namespace std;


template<class T>
DistanceMatrix<T>::DistanceMatrix(DistanceMatrix<T> & other){

    for(int i=0; i<other.orderedKeys.size();i++)
        this->orderedKeys.push_back(other.orderedKeys[i]);

    this->distances.resize(orderedKeys.size());
    for(int i=0; i< orderedKeys.size(); i++){
        this->distances[i].resize(orderedKeys.size());

        for(int j=0; j<orderedKeys.size();j++)
            this->distances[i][j] = other.distances[i][j]; 
    }

    for(int i=0; i<this->orderedKeys.size(); i++)
        this->orderedKeys[orderedKeys[i]] = i; 
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
vector<T> DistanceMatrix<T>::getKeys() const {
    return orderedKeys; 
}


template<class T>
double DistanceMatrix<T>::getDistance(T &first, T &second) const {
    typename std::vector<T>::iterator itFirst = keyIndex.find(first);
    typename std::vector<T>::iterator itSecond = keyIndex.find(first);

    if(itFirst != orderedKeys.end() && itSecond!= orderedKeys.end())
        return distances[itFirst->second][itSecond->second] ;
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