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
#include "ProductAllocationProhibition.h"
using namespace std;

//=======================================================================================
//      This class allow to store all the input data of storage allocation problem
//=======================================================================================
class InputData{
    
    private:
        static vector<Product> products;
        static vector<Client> clients;
        static vector<Order> orders;
        static vector<Parameter> parameters;
        static vector<ProductAllocationProhibitions> prohibitions;
        static Warehouse warehouse;
        bool alreadyCreated; 
    
    public:
        InputData();
        InputData(string  metadataFile);
    
        void setProducts(vector<Product> products);
        void setClients(vector<Client> clients);
        void setOrders(vector<Order> orders);
        void setWarehouse(Warehouse warehouse);
    
        vector<Product> getProducts();
        vector<Client> getClients();
        vector<Order> &getOrders();
        vector<Parameter> getParameters();
        Warehouse & getWarehouse();
    
};

#endif /* InputData_hpp */
