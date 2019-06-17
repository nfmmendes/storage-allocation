#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include "Util.h"


void Util::splitString(vector<string> & returned,string originalString, string delimiter){
    
	returned.clear();
    //cout<<originalString<<endl;
    size_t pos = 0;
    std::string token;
    while ((pos = originalString.find(delimiter)) != std::string::npos) {
        token = originalString.substr(0, pos);
        returned.push_back(token);
        originalString.erase(0, pos + delimiter.length());
		//cout<<token<<endl;
    }
	
    returned.push_back(originalString);
}
