#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<cstdlib>
#include<string>
using namespace std; 



    
class Product{
    
    private:
        long int ID;
        string name;
        string type;
        
    public:
        Product();
        Product(const Product & other){
            this->name = other.name;
            this->type = other.type;
        }
        
        Product(string name, string type){
            this->name = name;
            this->type = type;
        }
        
    
};

#endif
