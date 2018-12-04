#ifndef ORDER_H
#define ORDER_H

#include<iostream>
#include<ctime>
#include<vector>
#include<utility>
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
    
        Client client;                            //The amount of data needed in this object will depend of
        
    public:
        Order() {
        
        }
    
        Order(const  Order &order){
            this->dateDeadline = other.dateDeadline;
            this->client = other.Client;
            
            for(unsigned int i=0; i< order.orderItens.size(); i++){
                this->orderItens.push_back(order.orderItens[i]);
            }
        }
    
        Order(vector< pair<Product, double> >, Date dataDeadline, Time hourDeadline, Client client);
    
    
        void setorderItens(int i, Product &product, double quantity) {
            if(i >=0 && i< this->orderItens.size())
                this->orderItens[i] = make_pair(product, quantity);
        }
    
    
        void removeorderItens(int i){
                if(i>=0 && i<this->orderItens.size())
                    this->orderItens.erase(i);
        }
    
    
        void addorderItens(Product &product, double quantity){
            this->orderItens.push_back(make_pair(product,quantity));
        }
    
    
        void setOrders(vector<Product, double> orders){
            this->orderItens.clear();
            
            for(unsigned int i= 0; i< orders.size; i++)
                this->orderItens.push_back(make_pair(orders[i].first, orders[i].second));
        }
    
    
        vector<pair<Product, double> > getOrders(){
            return this->orderItens;
        }
    
    
        void setDateDeadline(Date &date){
            this->deadline.Date = date;
        }
    
    
        void setTimeDeadline(Time &time){
            this->deadline.Time = time;
        }
    
};

#endif
