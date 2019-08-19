#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<ctime>
#include<string>
#include<vector>
#include<fstream>
#include<utility>
#include<cstdlib>
#include "Product.h"
#include "Date.h"
#include "Time.h"
#include "Client.h"
#include "Time.h"
#include "Date.h"
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
///     Class to describe the orders that arrives to a warehouse. It's independent of 
///       the warehouse configuration or delivery policy (and MUST BE maintened in 
///       this way). To create specific behavior or elements use a derived class
/////////////////////////////////////////////////////////////////////////////////////////
class Order{
    
    private:
        vector<pair<Product, double> > orderItens; //!< The first element describe the product and
                                                  //!  the second the quantity
        pair<Date, Time> deadline;                //!< It can be initialized or not. If it is not
                                                  //!  its default value will be 2001/01/01
    
        string client;                            //The amount of data needed in this object will depend of
        
    public:
        Order();
    
        Order(const  Order &other);
    
        Order(vector< pair<Product, double> >items, Date dataDeadline, Time hourDeadline, string client);
    
    
        void setOrderItens(int i, Product &product, double quantity);
        void removeOrderItens(int i);
        void addOrderItens(Product &product, double quantity);
        void setOrders(vector<pair<Product, double> > orders);
    
        void setDateDeadline(Date &date);
        void setTimeDeadline(Time &time);
    
        vector<pair<Product, double> > & getOrderItems();
        static vector<Order> readOrdersData(ifstream &file);
    
};



#endif
