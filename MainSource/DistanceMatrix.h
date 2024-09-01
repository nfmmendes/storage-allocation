#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>
#include <set>
#include <unordered_map>
using std::vector;
using std::pair;
using std::map;
using std::cout;
using std::endl;
using std::setw;
using std::unordered_map;


template <class T>
class DistanceMatrix {

private:
    vector<T> orderedKeys;
    unordered_map<T, int> keyIndex;
    vector<vector<double> > distances;

public:
    DistanceMatrix() {}
    DistanceMatrix(const DistanceMatrix<T>& other);
    DistanceMatrix(map<pair<T, T>, double>& distances);
    DistanceMatrix<T>& buildMatrix(map<pair<T, T>, double>& distances);
    const vector<T>& getKeys() const;
    vector<vector<double> > getDistances() const;
    map<T, int> getElementsMap() const;
    double getDistance(const T& first, const T& second) const;
    void setRow(const vector<double>& d, T&);
    void setColumn(const vector<double>& d, T&);
    void setRowOnIndex(const vector<double>& d, int);
    void setColumnOnIndex(const vector<double>& d, int);
    DistanceMatrix<T>& operator=(const DistanceMatrix<T>& other);
    void print();
};

template <class T>
DistanceMatrix<T>::DistanceMatrix(map<pair<T, T>, double>& distancesPairs)
{
    this->buildMatrix(distancesPairs);
}

template <class T>
DistanceMatrix<T>& DistanceMatrix<T>::buildMatrix(map<pair<T, T>, double>& distancesPairs)
{
    set<T> keys;

    for (const auto& [extremities, distance] : distancesPairs) {
        keys.insert({extremities.first, extremities.second});
    }

    T aux;
    for (auto it = keys.begin(); it != keys.end(); it++) {
        keyIndex[*it] = orderedKeys.size();
        aux = *it;
        orderedKeys.push_back(aux);
    }

    distances.resize(orderedKeys.size());
    for (unsigned int i = 0; i < distances.size(); i++)
        distances[i].resize(distances.size(),1e5);

    int firstIndex, secondIndex;
    for (const auto& pair : distancesPairs) {
        firstIndex = keyIndex[pair.first.first];
        secondIndex = keyIndex[pair.first.second];

        distances[firstIndex][secondIndex] = pair.second;
    }

    return *this;
}

template <class T>
DistanceMatrix<T>::DistanceMatrix(const DistanceMatrix<T>& other)
{
    copy(begin(other.orderedKeys), end(other.orderedKeys), back_inserter(orderedKeys));

    this->distances.resize(orderedKeys.size());
    for (unsigned int i = 0; i < orderedKeys.size(); i++) {
        copy(begin(other.distances[i]), end(other.distances[i]), back_inserter(distances[i]));
    }

    for (unsigned int i = 0; i < this->orderedKeys.size(); i++)
        this->keyIndex[orderedKeys[i]] = i;
}

template <class T>
DistanceMatrix<T>& DistanceMatrix<T>::operator=(const DistanceMatrix<T>& other)
{
    this->orderedKeys.clear();
    copy(begin(other.orderedKeys), end(other.orderedKeys), back_inserter(orderedKeys));

    this->distances.resize(orderedKeys.size());
    for (unsigned int i = 0; i < orderedKeys.size(); i++) {
        copy(begin(other.distances[i]), end(other.distances[i]), back_inserter(distances[i]));
    }

    this->keyIndex.clear();
    for (unsigned int i = 0; i < this->orderedKeys.size(); i++)
        this->keyIndex[orderedKeys[i]] = i;

    return *this;
}

template <class T>
map<T, int> DistanceMatrix<T>::getElementsMap() const
{
    return keyIndex;
}

template <class T>
const vector<T>& DistanceMatrix<T>::getKeys() const
{
    return orderedKeys;
}

template <class T>
double DistanceMatrix<T>::getDistance(const T& first, const T& second) const
{
    auto itFirst = keyIndex.find(first);

    if(itFirst == keyIndex.end())
        return 1e5;

    auto itSecond = keyIndex.find(second);
    if(itSecond == keyIndex.end())
        return 1e5;

    return distances[itFirst->second][itSecond->second];
}

template <class T>
void DistanceMatrix<T>::setRow(const vector<double>& d, T& elem)
{
    auto itFirst = keyIndex.find(elem);
    if(itFirst == orderedKeys.end())
        return;

    int index = keyIndex[itFirst];
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for (int i = 0; i < maxAdvance; i++)
        orderedKeys[index][i] = d[i];
}

template <class T>
void DistanceMatrix<T>::setColumn(const vector<double>& d, T& elem)
{
    auto itFirst = keyIndex.find(elem);
    if(itFirst == orderedKeys.end())
        continue;
        
    int index = keyIndex[itFirst];
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for (int i = 0; i < maxAdvance; i++)
        orderedKeys[i][index] = d[i];
}

template <class T>
void DistanceMatrix<T>::setRowOnIndex(const vector<double>& d, int index)
{
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for (int i = 0; i < maxAdvance; i++)
        orderedKeys[index][i] = d[i];
}

template <class T>
void DistanceMatrix<T>::setColumnOnIndex(const vector<double>& d, int index)
{
    int maxAdvance = min(orderedKeys.size(), distances.size());
    for (int i = 0; i < maxAdvance; i++)
        orderedKeys[i][index] = d[i];
}

template <class T>
void DistanceMatrix<T>::print()
{
    cout << setw(15) << "****************\n";
    for (unsigned int i = 0; i < orderedKeys.size(); i++) {
        cout << setw(15) << orderedKeys[i] << endl;
    }

    for (unsigned int i = 0; i < orderedKeys.size(); i++) {
        int indexI = keyIndex[orderedKeys[i]];
        for (unsigned int j = 0; j < orderedKeys.size(); j++)
            cout << setw(15) << distances[indexI][keyIndex[orderedKeys[j]]];
        cout << endl;
    }
}
