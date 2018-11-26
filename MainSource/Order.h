#include<iostream>
#include<ctime>
#include<vector>
#include<utility>
#include "Product.h"
#include "Date.h"
#include "Time.h"
#include "Client.h"
using namespace std;


/////////////////////////////////////////////////////////////////////////////////////////
///     Class to describe the orders that arrives to a warehouse. It's independent of 
///       the warehouse configuration or delivery policy (and MUST BE maintened in 
///       this way). To create specific behavior or elements use a derived class
/////////////////////////////////////////////////////////////////////////////////////////
class Order{
    
    private:
        vector<pair<Product, double> > orderItem; //!< The first element describe the product and 
                                                  //!  the second the quantity
        pair<Date, Time> deadline;                //!< It can be initialized or not. If it is not
                                                  //!  its default value will be 2001/01/01
        Date dateDeadline;                        
        Time hourDeadline;      //
        Client client;          //The amount of data needed in this object will depend of  
        
    public:
        Order();
        Order(Order &order);
        Order(vector< pair<Product, double> , Data dataDeadline, Time hourDeadline, Client client);
        
        void setOrderItem(int i, Product &product, double quantity);
        void removeOrderItem(int i);
        void addOrderItem(Product &product, double quantity);
        void setOrders(vector<Product, double> orders);
        vector<pair<Product, double> > getOrders();
        
        void setDateDeadline(Date &date);
        void setTimeDeadline(Time &time); 
        
        
        
    
}