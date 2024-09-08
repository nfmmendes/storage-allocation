#pragma once

#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
using std::string; 
using std::vector;
using std::cout;
using std::endl;
using std::ifstream;

class Product{
    
    private:
        long int ID;
        string name;
        string family;
        
    public:
        Product() {}
        Product(const Product & other);
        
        Product(long int ID, const string& name, const string& family);
		Product & operator=(const Product &other);
    
        long int getID()const; 
        string getName()const; 
        string getFamily()const; 
    
        void setID(long int Id);
        void setName(const string& name); 
        void setFamily(const string& family); 
		bool operator<(const Product &other) const; 
        static vector<Product> readProductsData(std::ifstream &file);
		void print()const; 
    
};
