//
//  InputData.hpp
//  
//
//  Created by Nilson Mendes on 19/12/2018.
#pragma once

#include <vector>
#include "Product.h"
#include "Client.h"
#include "Order.h"
#include "Parameter.h"
#include "Warehouse.h"
#include "ProductAllocationProhibition.h"
#include "IsolatedFamily.h"
using std::vector; 


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
		static vector<IsolatedFamily> isolatedFamilies; 
        static Warehouse warehouse;
        bool alreadyCreated = false; 
    
    public:
        InputData();
        InputData(string  metadataFile);
    
        void setProducts(vector<Product> products);
        void setClients(vector<Client> clients);
        void setOrders(vector<Order> orders);
        void setParameters(vector<Parameter> parameters);
        void setWarehouse(Warehouse warehouse);
		void setIsolatedFamilies(vector<IsolatedFamily> &isolatedFamilies);
    
        vector<Product> &getProducts();
        vector<Client> getClients();
        vector<Order> &getOrders();
        vector<Parameter> getParameters();
		vector<IsolatedFamily> getIsolatedFamily();
		vector<ProductAllocationProhibitions> getAllocationProhibitions(); 
        Warehouse & getWarehouse();
    
};