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
    
        long int getID(){ return ID; }
        string getName(){ return name; }
        string getType(){ return type; }
    
        void setID(long int Id){ if(Id >= 0 ) this->ID = Id; }
        void setName(string name){ this->name = name;}
        void setType(string type){ this->type = type;}
    
    
};

#endif
