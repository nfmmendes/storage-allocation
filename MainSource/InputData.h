//
//  InputData.hpp
//  
//
//  Created by Nilson Mendes on 19/12/2018.
//

#ifndef InputData_h
#define InputData_h

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Product.h"
#include "Client.h"
#include "Order.h"
#include "Parameter.h"
#include "Warehouse.h"
using namespace std;

//=======================================================================================
//      This class allow to store all the input data of storage allocation problem
//=======================================================================================
class InputData{
    
    private:
        static vector<Product> products;
        static vector<Clients> clients;
        static vector<Orders> orders;
        static vector<Parameter> parameters;
        static Warehouse warehouse;
        bool alreadyCreated; 
    
    public:
        InputData();
        InputData(vector<Product> products, vector<Clients> clients, vector<Orders> orders,
                  vector<Parameter> paramters, Warehouse warehouse);
    
        InputData(string  metadataFile);
        InputData(string productsFile, string clientsFile, string ordersFile, string parametersFile, string warehouseFile);
    
        void setProducts(vector<Product> products);
        void setClients(vector<Clients> clients);
        void setOrders(vector<Order> orders);
        void setWarehouse(Warehouse warehouse);
    
        vector<Product> getProducts();
        vector<Clients> getClients();
        vector<Orders> getOrders();
        vector<Parameter> getParameters();
        Warehouse & getWarehouse();
    
};

#endif /* InputData_hpp */
