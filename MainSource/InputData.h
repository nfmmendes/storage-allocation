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


//=======================================================================================
//      This class allow to store all the input data of storage allocation problem
//=======================================================================================
class InputData{
    
    private:
        static std::vector<Product> products;
        static std::vector<Client> clients;
        static std::vector<Order> orders;
        static std::vector<Parameter> parameters;
        static std::vector<ProductAllocationProhibitions> prohibitions;
		static std::vector<IsolatedFamily> isolatedFamilies; 
        static Warehouse warehouse;
        bool alreadyCreated = false; 
    
    public:
        InputData();
        InputData(string  metadataFile);
    
        void setProducts(std::vector<Product> products);
        void setClients(std::vector<Client> clients);
        void setOrders(std::vector<Order> orders);
        void setParameters(std::vector<Parameter> parameters);
        void setWarehouse(Warehouse warehouse);
		void setIsolatedFamilies(std::vector<IsolatedFamily> &isolatedFamilies);
    
        std::vector<Product> &getProducts();
        std::vector<Client> getClients();
        std::vector<Order> &getOrders();
        std::vector<Parameter> getParameters();
		std::vector<IsolatedFamily> getIsolatedFamily();
		std::vector<ProductAllocationProhibitions> getAllocationProhibitions(); 
        Warehouse & getWarehouse();
    
};