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
        Product(){}
        Product(const Product & other){
			this->ID = other.ID;
            this->name = other.name;
            this->family = other.family;
        }
        
        Product(long int ID, const string& name, const string& family){
            this->ID = ID;
            this->name = name;
            this->family = family;
        }
		
		Product & operator=(const Product &other){
			this->ID = other.ID;
            this->name = other.name;
            this->family = other.family;
			
			return *this;
		}
    
        long int getID()const { return ID; }
        string getName()const{ return name; }
        string getFamily()const{ return family; }
    
        void setID(long int Id){ if(Id >= 0 ) this->ID = Id; }
        void setName(const string& name){ this->name = name;}
        void setFamily(const string& family){ this->family = family;}
		bool operator<(const Product &other) const{ return this->ID < other.ID; }
        static vector<Product> readProductsData(std::ifstream &file);
		void print()const{ std::cout<<ID<<" "<<name<<" "<<family<<std::endl; }
    
};
