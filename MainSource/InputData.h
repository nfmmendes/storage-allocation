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

/**
 * @brief  Class <c> InputData </c> allows to store all the input data of the storage allocation problem
 */
class InputData{
    
    //TODO: Correct this "singleton" implementation. 
    private:
        static vector<Product> products;            ///< The list of products.
        static vector<Client> clients;              ///< The list of clients. 
        static vector<Order> orders;                ///< The list of orders. 
        static vector<Parameter> parameters;        ///< The list of problem parameters. 
        static vector<ProductAllocationProhibitions> prohibitions; ///< The list of allocation prohibitions. 
		static vector<IsolatedFamily> isolatedFamilies; ///< THe list of isolated families. 
        static Warehouse warehouse;                 ///< The warehouse layout.
        bool alreadyCreated = false;                ///< Store if an object have been created already. 
    
    public:
        /**
         * @brief Constructor. 
         */
        InputData();

        /**
         * @brief Constructor
         * @param metadataFile Name of the file containing the input data.  
         */
        InputData(string  metadataFile);
    
        /**
         * @brief Set the list of products. 
         * @param products The list of products. 
         */
        void setProducts(vector<Product> products);

        /**
         * @brief Set the list of clients. 
         * @param clients The list of clients. 
         */
        void setClients(vector<Client> clients);

        /**
         * @brief Set the list of orders. 
         * @param orders The list of orders. 
         */
        void setOrders(vector<Order> orders);

        /**
         * @brief Set the list of optimization parameters. 
         * @param parameters The list of optimization parameters. 
         */
        void setParameters(vector<Parameter> parameters);

        /**
         * @brief Set the warehouse layout. 
         * @param warehouse The hourehouse layout. 
         */
        void setWarehouse(Warehouse&& warehouse);

        /**
		 * @brief Set the list of isolated families. 
		 * @param isolatedFamilies The list of isolated families. 
         */
		void setIsolatedFamilies(vector<IsolatedFamily> &isolatedFamilies);
    
        /**
         * @brief Get the list of products in the input. 
         * @return A list of products. 
         */
        const vector<Product> &getProducts();

        /**
         * @brief Get the list of clients in the input. 
         * @return A list of clients. 
         */
        const vector<Client>& getClients();

        /**
         * @brief Get the list of orders in the input. 
         * @return A list of orders. 
         */
        const vector<Order> &getOrders();

        /**
         * @brief Get the list of parameters in the input.
         * @return A list of parameters. 
         */
        const vector<Parameter>& getParameters();

        /**
		 * @brief Get the list of isolated families in the input.
		 * @return A list of isolated famlies.
         */
		const vector<IsolatedFamily>& getIsolatedFamily();

        /**
		 * @brief Get a list of allocation prohibitions in the input.
		 * @return A list of allocation prohibitions. 
         */
		const vector<ProductAllocationProhibitions>& getAllocationProhibitions(); 

        /**
         * @brief Get the input warehouse layout. 
         * @return A warehouse layout object. 
         */
        const Warehouse& getWarehouse();  
};