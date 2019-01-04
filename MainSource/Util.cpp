#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "Util.h"


vector<string> Util::splitString(string originalString, string delimiter){
    
    vector<string> returned;
    
    size_t pos = 0;
    std::string token;
    while ((pos = originalString.find(delimiter)) != std::string::npos) {
        token = originalString.substr(0, pos);
        returned.push_back(toke);
        originalString.erase(0, pos + delimiter.length());
    }
    returned.push_back(originalString);
}
