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
using std::vector;
using std::cout;
using std::end;
using std::ios;
using std::ifstream;
using std::cerr;

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

InputData::InputData(const string&  dataFile){
    
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
        warehouse.readWarehouseData(file);
        
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


void InputData::setWarehouse(Warehouse &&warehouse){
    InputData::warehouse = warehouse;
    
}

const vector<Product> &InputData::getProducts() const {return products;}

const vector<Client>& InputData::getClients() const { return clients;}

const vector<Order> &InputData::getOrders() const { return orders;}

const vector<Parameter>& InputData::getParameters() const { return parameters;}

const Warehouse & InputData::getWarehouse() const { return warehouse; }

const vector<IsolatedFamily>& InputData::getIsolatedFamily() const { return isolatedFamilies; }

const vector<ProductAllocationProhibitions>& InputData::getAllocationProhibitions() const{ return prohibitions;	}