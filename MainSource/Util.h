#ifndef Util_h
#define Util_h

#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Util{
    
    public:
    
        Util(){}
        static void splitString(vector<string>& returned ,string originalString, string delimiter);
};

#endif 
