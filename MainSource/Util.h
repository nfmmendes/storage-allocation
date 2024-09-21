#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set> 
using std::vector;
using std::string;
using std::pair;
using std::set;

class Util{
    
    public:
    
        Util(){}
        static void splitString(vector<string>& returned, string originalString, string delimiter);
        static bool ChooseTwoProductIndexes(int &first, int &second, unsigned long long numProducts, const set<pair<int,int> > & swapsDone);
};

