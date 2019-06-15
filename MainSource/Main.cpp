#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include "TSP.h"
#include "VND.h"
#include "InputData.h"
using namespace std;
using namespace QuickTSP;

int main(int argc, char **argv){
    
    if(argc > 1){
        //Main input file name. This file will say which input files will be used
        string indexFileName = argv[1];
        InputData input(indexFileName);

        cout<<"Converting algorithm to graph\n";
        TSP *router;
        VND *vnd;
        
        
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}
