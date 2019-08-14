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


#endif