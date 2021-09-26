#pragma once

#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
using namespace std; 
    
class Product{
    
    private:
        long int ID;
        std::string name;
        std::string family;
        
    public:
        Product(){}
        Product(const Product & other){
			this->ID = other.ID;
            this->name = other.name;
            this->family = other.family;
        }
        
        Product(long int ID, std::string name, std::string family){
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
        std::string getName()const{ return name; }
        std::string getFamily()const{ return family; }
    
        void setID(long int Id){ if(Id >= 0 ) this->ID = Id; }
        void setName(std::string name){ this->name = name;}
        void setFamily(std::string family){ this->family = family;}
		bool operator<(const Product &other) const{ return this->ID < other.ID; }
        static std::vector<Product> readProductsData(std::ifstream &file);
		void print()const{ std::cout<<ID<<" "<<name<<" "<<family<<std::endl; }
    
};
