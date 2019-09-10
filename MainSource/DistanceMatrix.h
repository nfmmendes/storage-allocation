#ifndef DISTANCE_MATRIX_H
#define DISTANCE_MATRIX_H

#include<iostream>
#include<map>
#include<vector>
#include<cmath>
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
        vector<T> getKeys() const;
        vector<vector< double > > getDistances()const;
        map<T, int> getElementsMap() const;
        double getDistance(T &first, T &second) const; 
        void setRow(vector<double> &d, T &);
        void setColumn(vector<double> &d, T&) ;
        void setRowOnIndex(vector<double> &d, int) ;
        void setColumnOnIndex(vector<double> &d, int);
};



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

#endif