#include<iostream>
#include<string>
#include<cstdlib>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include "allClasses.h"
#include "Warehouse.h"
#include "Product.h"
#include "Order.h"
#include "QuickTSP.h"
using namespace std;
using namespace QuickTSP;

int main(int argc, char **argv){
    
    string paramFileName = argv[0];
    string warehouseDescriptionFileName; 
    string ordersFileName; 
    Warehouse *warehouse; 
    QuickTSP::QuickTSP *algorithm;
    //vector<Order> orders; 
    
    //READ THE INPUT 
    ifstream file;
    file.open(paramFileName, ios::in); 
    if(file.is_open()){
        cout<<"Starting the input reading...\n";
        file>>warehouseDescriptionFileName;
        file>>ordersFileName; 
        file.close();
    }else{
        cerr<<"The file could not be open!\n Verifiy if it exists or if the you passed the right path.";
        return 1;
    }
      
    //START THE DATA PROCESS
    cout<<"Start data processing...\n";

    
    
    //START THE SOLUTION PROCEDURE
    cout<<"Calling the solver...\n";
    
    
    
    //START THE 
    cout<<"Processing the solution...\n";
    
    
    
    cout<<"Ending execution.";
    
    return 0; 
}