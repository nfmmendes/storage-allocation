#pragma once 

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<utility>
#include "Product.h"
#include "Date.h"
#include "Time.h"
#include "Client.h"
#include "Time.h"
#include "Date.h"

/**
 * @brief Class to describe the orders that arrives to a warehouse. It's independent of 
 *        the warehouse configuration or delivery policy (and MUST BE maintened in this way).
 *        To create specific behavior or elements use a derived class.
 */
class Order{
    
    private:
        std::vector<std::pair<Product, double> > orderItens; //!< The first element describe the product and
                                                             //!  the second the quantity
        std::pair<Date, Time> deadline;                      //!< It can be initialized or not. If it is not
                                                             //!  its default value will be 2001/01/01
    
        std::string client;                                  //The amount of data needed in this object will depend of
        
    public:
        /**
         * @brief Default constructor.
         */
        Order();
    
        /**
         * @brief Copy constructor. 
         * @param other The source object. 
         */
        Order(const  Order &other);
    
        /**
         * @brief Constructor. 
         * @param items The order items.
         * @param dataDeadline The order data deadline.
         * @param hourDeadline The order hour deadline.
         * @param client The client.
         */
        Order(std::vector<std::pair<Product, double> >items, Date dataDeadline, Time hourDeadline, std::string client);

        /**
         * @brief Set the product orders. 
         * @param The new products. 
         */
        void setOrders(std::vector<std::pair<Product, double> > orders);

        /** 
         * @brief Get the order items.
         * @return A list of pairs containing a product and its quantity. 
         */
        const std::vector<std::pair<Product, double> > & getOrderItems() const;

        /**
         * @brief Read orders data from file
         * @param file The file stream object. 
         */
        static std::vector<Order> readOrdersData(ifstream &file);
    
};
