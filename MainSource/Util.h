#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <set> 

class Util{
    
    public:
    
        Util(){}
        static void splitString(std::vector<std::string>& returned ,std::string originalString, std::string delimiter);
        static bool ChooseTwoProductIndexes(int &first, int &second, int numProducts, const std::set<std::pair<int,int> > & swapsDone);
};

