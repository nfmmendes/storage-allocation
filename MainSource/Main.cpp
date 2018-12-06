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
        
        ///Input file names
        string warehouseDescriptionFileName;
        string ordersFileName;
        string parametersFileName;
        
        //Data structures
        Warehouse *warehouse;
        TSP *algorithm;
        vector<Order> orders;
        
        //READ THE INPUT
        ifstream file;
        file.open(indexFileName, ios::in);
        if(file.is_open()){
            cout<<"Starting the input reading...\n";
            file>>warehouseDescriptionFileName;
            file>>ordersFileName;
            file>>parametersFileName;
            
            file.close();
            
            cout<<"Reading warehouse data...\n";
            warehouse = new Warehouse();
            warehouse->ReadWarehouseData(warehouseDescriptionFileName);
            
            cout<<"Reading order data...\n";
            Order::readOrdersData(ordersFileName);
            
            cout<<"Reading parameters...\n";
            
        }else{
            cerr<<"The file could not be open!\n Verifiy if it exists or if the you passed the right path.";
            return 1;
        }
        
        //START THE DATA PROCESS
        cout<<"Start data processing...\n";
        HananGraph hanan;
        algorithm = new TSP(hanan, orders);
        
        
        
        //START THE SOLUTION PROCEDURE
        cout<<"Calling the solver...\n";
        
        
        
        //START THE
        cout<<"Processing the solution...\n";
        
        
        
        cout<<"Ending execution.";
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}
