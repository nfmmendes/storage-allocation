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

Order::Order(vector< pair<Product, double> > items, Date dataDeadline, Time hourDeadline, Client client){
    this->deadline = make_pair(dataDeadline, hourDeadline);
    this->client = client;
    
    for(unsigned int i=0; i<items.size();i++)
        this->orderItens.push_back(make_pair(items[i].first, items[i].second));
}


void Order::setorderItens(int i, Product &product, double quantity) {
    if(i >=0 && i<(int)this->orderItens.size())
        this->orderItens[i] = make_pair(product, quantity);
}


void Order::removeorderItens(int i){
    if(i>=0 && i<(int)this->orderItens.size())
        this->orderItens.erase(this->orderItens.begin()+i);
}


void Order::addorderItens(Product &product, double quantity){
    this->orderItens.push_back(make_pair(product,quantity));
}


void Order::setOrders(vector<pair<Product, double>> orders){
    this->orderItens.clear();
    
    for(unsigned int i= 0; i< orders.size(); i++)
        this->orderItens.push_back(make_pair(orders[i].first, orders[i].second));
}


vector<pair<Product, double> > Order::getOrders(){
    return this->orderItens;
}


void Order::setDateDeadline(Date &date){
    this->deadline.first = date;
}


void Order::setTimeDeadline(Time &time){
    this->deadline.second = time;
}

vector<Order> Order::readOrdersData(string fileName){
    vector<Order> input;
    ifstream file;
    
    file.open(fileName,ios::in);
    
    
    return input;
}
