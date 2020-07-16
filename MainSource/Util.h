#ifndef Util_h
#define Util_h

#include <iostream>
#include <string>
#include <vector>
#include <set> 
using namespace std;


class Util{
    
    public:
    
        Util(){}
        static void splitString(vector<string>& returned ,string originalString, string delimiter);
        static bool ChooseTwoProductIndexes(int &first, int &second, int numProducts, const set<pair<int,int> > & swapsDone);
};

#endif 
