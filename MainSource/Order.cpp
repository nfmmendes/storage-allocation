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
#include "Order.h"
#include "InputData.h"
using namespace std;


Order::Order() {
    
}

Order::Order(const  Order &other){
    this->deadline = other.deadline;
    this->client = other.client;
    
    for(unsigned int i=0; i< other.orderItens.size(); i++){
        this->orderItens.push_back(other.orderItens[i]);
    }
}

Order::Order(vector< pair<Product, double> > items, Date dataDeadline, Time hourDeadline, string client){
    this->deadline = make_pair(dataDeadline, hourDeadline);
    this->client = client;
    
    for(unsigned int i=0; i<items.size();i++)
        this->orderItens.push_back(make_pair(items[i].first, items[i].second));
}


void Order::setOrderItens(int i, Product &product, double quantity) {
    if(i >=0 && i<(int)this->orderItens.size())
        this->orderItens[i] = make_pair(product, quantity);
}


void Order::removeOrderItens(int i){
    if(i>=0 && i<(int)this->orderItens.size())
        this->orderItens.erase(this->orderItens.begin()+i);
}


void Order::addOrderItens(Product &product, double quantity){
    this->orderItens.push_back(make_pair(product,quantity));
}


void Order::setOrders(vector<pair<Product, double> > orders){
    this->orderItens.clear();
    
    for(unsigned int i= 0; i< orders.size(); i++)
        this->orderItens.push_back(make_pair(orders[i].first, orders[i].second));
}


/**
 *  Return all the items of an order with their respective quantities
 */
vector<pair<Product, double> > & Order::getOrderItems(){
    return this->orderItens;
}


void Order::setDateDeadline(Date &date){
    this->deadline.first = date;
}


void Order::setTimeDeadline(Time &time){
    this->deadline.second = time;
}

vector<Order> Order::readOrdersData(ifstream &file){
    vector<Order> orders;
    
    int numOrders;
    int numItems;
    string productName;
    string clientCode;
    double quantity;
    Product product;
    string date, time;
    file>>numOrders;
    cout<<numOrders<<endl;
	
    InputData input;
    vector<pair<Product, double> > items;
    vector<Product> products = input.getProducts();
    vector<Client> clients = input.getClients();
    
    map<string,Product> productByName;    
    
    for(int i=0; i<(int)products.size(); i++)
        productByName[products[i].getName()] = products[i];
	
    for(int i=0; i<numOrders; i++){
        file>>numItems;
        file>>clientCode;
        file>>date>>time;
      //  cout<<"\t" <<clientCode<<" "<<date<<" "<<time<<endl;
		
        
        for(int j=0;j<numItems;j++){
            file>>productName>>quantity;
            product = productByName[productName];
			//cout<<productCode<<" "<<quantity<<endl;
            items.push_back(make_pair(product,quantity));
        }

		Date parsedDate; 
		Time parsedTime;
		
		if(date.find('-') != std::string::npos)
			parsedDate = Date::Parse(date, "yyyy-MM-dd");
		else if(date.find('/') != std::string::npos)
			parsedDate = Date::Parse(date, "yyyy/MM/dd");


		
		if(time.find('/') != std::string::npos)
			parsedTime=Time::Parse(time,"HH:MM:SS AM/PM");
		else
			parsedTime=Time::Parse(time, "HH:MM:SS"); 
		

		orders.push_back(Order(items,parsedDate,parsedTime,clientCode));
		items.clear();
		
		
    }
    
    return orders;
}
