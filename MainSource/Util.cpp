#include<iostream>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include "Util.h"


void Util::splitString(std::vector<std::string> & returned, std::string originalString, std::string delimiter){
    
	returned.clear();
    //cout<<originalString<<endl;
    size_t pos = 0;
    std::string token;
    while ((pos = originalString.find(delimiter)) != std::string::npos) {
        token = originalString.substr(0, pos);
        returned.push_back(token);
        originalString.erase(0, pos + delimiter.length());
    }
	
    returned.push_back(originalString);
}
	
	
	
bool Util::ChooseTwoProductIndexes(int &first, int &second, int numProducts, const std::set<std::pair<int,int> > & swapsDone){
	first = rand()%numProducts;
	second = rand()%numProducts; 
	
	int countTries = 0; 
	while(swapsDone.find(std::make_pair(first, second)) != swapsDone.end() || swapsDone.find(std::make_pair(second,first)) != swapsDone.end() || second == first){
		first = rand()%numProducts;
		second = rand()%numProducts; 
		if( countTries >= numProducts*numProducts)
			break;
	}

	return countTries < numProducts*numProducts;
}
