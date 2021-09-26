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


/////////////////////////////////////////////////////////////////////////////////////////
///     Class to describe the orders that arrives to a warehouse. It's independent of 
///       the warehouse configuration or delivery policy (and MUST BE maintened in 
///       this way). To create specific behavior or elements use a derived class
/////////////////////////////////////////////////////////////////////////////////////////
class Order{
    
    private:
        std::vector<std::pair<Product, double> > orderItens; //!< The first element describe the product and
                                                             //!  the second the quantity
        std::pair<Date, Time> deadline;                      //!< It can be initialized or not. If it is not
                                                             //!  its default value will be 2001/01/01
    
        std::string client;                                  //The amount of data needed in this object will depend of
        
    public:
        Order();
    
        Order(const  Order &other);
    
        Order(std::vector<std::pair<Product, double> >items, Date dataDeadline, Time hourDeadline, std::string client);
    
    
        void setOrderItens(int i, Product &product, double quantity);
        void removeOrderItens(int i);
        void addOrderItens(Product &product, double quantity);
        void setOrders(std::vector<std::pair<Product, double> > orders);
    
        void setDateDeadline(Date &date);
        void setTimeDeadline(Time &time);
    
        const std::vector<std::pair<Product, double> > & getOrderItems() const;
        static std::vector<Order> readOrdersData(ifstream &file);
    
};
