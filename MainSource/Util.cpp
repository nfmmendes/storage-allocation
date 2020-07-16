#include<iostream>
#include<string>
#include<vector>
#include<set>
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
    }
	
    returned.push_back(originalString);
}
	
	
	
bool Util::ChooseTwoProductIndexes(int &first, int &second, int numProducts, const set<pair<int,int> > & swapsDone){
	first = rand()%numProducts;
	second = rand()%numProducts; 
	
	int countTries = 0; 
	while(swapsDone.find(make_pair(first, second)) != swapsDone.end() || swapsDone.find(make_pair(second,first)) != swapsDone.end() || second == first){
		first = rand()%numProducts;
		second = rand()%numProducts; 
		if( countTries >= numProducts*numProducts)
			break;
	}

	return countTries < numProducts*numProducts;
}
