#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include "Product.h"
using std::string;
using std::ifstream;

Product::Product(const Product & other){
    this->ID = other.ID;
    this->name = other.name;
    this->family = other.family;
}

Product::Product(long int ID, const string& name, const string& family){
    this->ID = ID;
    this->name = name;
    this->family = family;
}

Product & Product::operator=(const Product &other){
    this->ID = other.ID;
    this->name = other.name;
    this->family = other.family;
    
    return *this;
}

long int Product::getID()const { return ID; }
const string& Product::getName() const { return name; }
const string& Product::getFamily() const { return family; }

void Product::setID(long int Id){ 
    if(Id >= 0 ) 
        this->ID = Id; 
}

void Product::setName(const string& name){ 
    this->name = name;
}

void Product::setFamily(const string& family){ 
    this->family = family;
}

bool Product::operator<(const Product &other) const { 
    return this->ID < other.ID; 
}

vector<Product> Product::readProductsData(ifstream &file){
    
    vector<Product> products;
    string _name, _type;
    long int ID;
    
    
    int numProducts;
    file>>numProducts;
	//cout<<numProducts<<endl;
    for(int i=0; i<numProducts; i++){
        file>>ID>>_name>>_type;
        products.push_back(Product(ID, _name,_type));
    }
        
    return products;
}

void Product::print()const{ 
    std::cout<<ID<<" "<<name<<" "<<family<<std::endl; 
}