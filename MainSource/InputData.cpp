#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "InputData.h"


InputData::alredyCreated = false;

InputData::InputData(){
    alredyCreated = true;
}


InputData::InputData(vector<Product> products, vector<Clients> clients, vector<Orders> orders,
                     vector<Parameter>parameters,  Warehouse warehouse){
    if(!alredyCreated){
        alredyCreated = true;
        setProducts(products);
        setClients(clients);
        setOrders(orders);
        setWarehouse(warehouse);
        setParameters(parameters);
    }
    
}


InputData::InputData(string  metadataFile){
    
    ///Input file names
    string warehouseDescriptionFileName;
    string productsFileName;
    string clientsFileName;
    string ordersFileName;
    string parametersFileName;
    
    //Data structures
    
    
    
    //READ THE INPUT
    ifstream file;
    file.open(metadataFile, ios::in);
    if(file.is_open()){
        cout<<"Starting the input reading...\n";
        file>>warehouseDescriptionFileName;
        file>>productsFileName
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
}


InputData::InputData(string productsFile, string clientsFile, string ordersFile, string warehouseFile){
    
    
}

void InputData::setProducts(vector<Product> products){
    InputData::products.clear();
    
    for(unsigned int i=0; i< products.size(); i++)
        InputData::products.push_back(Product( products[i]));
    
}

void InputData::setClients(vector<Clients> clients){
    InputData::clients.clear();
    
    for(unsigned int i=0; i<clients.size(); i++)
        InputData::clients.push_back(Client(clients[i]));
    
}

void InputData::setOrders(vector<Order> orders){
    InputData::orders.clear();
    
    for(unsigned int i=0; i< orders.size(); i++)
        InputData::orders.push_back(Order(orders[i]));
    
}

//==============================================================
//
//==============================================================
void InputData::setParameters(vector<Parameter> parameters){
    InputData::parameters.clear();
    
    for(unsigned int i=0; i< parameters.size(); i++)
        InputData::orders.push_back(Parameter(parameters[i]));
    
}

void InputData::setWarehouse(Warehouse warehouse){
    InputData::warehouse = warehouse;
    
}

vector<Product> InputData::getProducts(){return products;}

vector<Clients> InputData::getClients(){ return clients;}

vector<Orders> InputData::getOrders() { return orders;}

vector<Parameter> getParameters() { return parameters;}

Warehouse & InputData::getWarehouse() { return warehouse; }
