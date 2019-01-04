#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include "allClasses.h"
#include "Warehouse.h"
#include "Product.h"
#include "Order.h"
#include "TSP.h"
using namespace std;
using namespace QuickTSP;

int main(int argc, char **argv){
    
    if(argc > 1){
        //Main input file name. This file will say which input files will be used
        string indexFileName = argv[1];
        InputData input(indexFileName);

        
        TSP *algorithm;
        
        //START THE DATA PROCESS
        cout<<"Start data processing...\n";
        HananGraph hanan;
        algorithm = new TSP(hanan, input.getOrders());
        
        
        
        //START THE SOLUTION PROCEDURE
        cout<<"Calling the solver...\n";
        
        
        
        //START THE
        cout<<"Processing the solution...\n";
        
        
        
        cout<<"Ending execution.";
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}
