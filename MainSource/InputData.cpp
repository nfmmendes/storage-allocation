#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include "Parameter.h"
#include "InputData.h"
#include "Product.h"
#include "Client.h"
#include "Order.h"
#include "Warehouse.h"
#include "ProductAllocationProhibition.h"
#include "IsolatedFamily.h"
using namespace std;

vector<Product> InputData::products;
vector<Client> InputData::clients;
vector<Order> InputData::orders;
vector<Parameter> InputData::parameters;
vector<ProductAllocationProhibitions> InputData::prohibitions;
vector<IsolatedFamily> InputData::isolatedFamilies;
Warehouse InputData::warehouse;

InputData::InputData(){
    alreadyCreated = true;
}



InputData::InputData(string  dataFile){
    
    ///Input file names
    string warehouseDescriptionFileName;
    string productsFileName;
    string clientsFileName;
    string ordersFileName;
    string prohibitionsFileName;
    string parametersFileName;
    
    //Data structures    
    
    
    //READ THE INPUT
    ifstream file;
    file.open(dataFile, ios::in);
    if(file.is_open()){
       // cout<<"Starting the input reading...\n";
        
        
        cout<<"Reading warehouse data...\n";
        warehouse.ReadWarehouseData(file);
        
        cout<<"Reading products data..\n";
        products = Product::readProductsData(file);
        
        cout<<"Reading order data...\n";
        orders = Order::readOrdersData(file);
        
        
        cout<<"Reading allocation prohibitions...\n";
        prohibitions = ProductAllocationProhibitions::readAllProhibitionsData(file);
		isolatedFamilies = IsolatedFamily::readIsolatedFamilyData(file);
        
        //cout<<"Reading parameters...\n";
        //parameters = Parameter::readParametersData(file);
        
        file.close();
        
    }else{
        cerr<<"The file could not be open!\n Verifiy if it exists or if the you passed the right path.";
    }
}



void InputData::setProducts(vector<Product> products){
    InputData::products.clear();
    
    for(unsigned int i=0; i< products.size(); i++)
        InputData::products.push_back(Product( products[i]));
    
}

void InputData::setClients(vector<Client> clients){
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
        InputData::parameters.push_back(Parameter(parameters[i]));
    
}

void InputData::setWarehouse(Warehouse warehouse){
    InputData::warehouse = warehouse;
    
}

void InputData::setIsolatedFamilies(vector<IsolatedFamily> &_isolatedFamilies){
	for(unsigned int i=0; i < _isolatedFamilies.size(); i++)
		this->isolatedFamilies.push_back(IsolatedFamily(_isolatedFamilies[i]));
}

vector<Product> &InputData::getProducts(){return products;}

vector<Client> InputData::getClients(){ return clients;}

vector<Order> &InputData::getOrders() { return orders;}

vector<Parameter> InputData::getParameters() { return parameters;}

Warehouse & InputData::getWarehouse() { return warehouse; }

vector<IsolatedFamily> InputData::getIsolatedFamily(){ return isolatedFamilies; }

vector<ProductAllocationProhibitions> InputData::getAllocationProhibitions(){ return prohibitions;	}