#ifndef PRODUCT_H
#define PRODUCT_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<vector>
#include<fstream>
using namespace std; 



    
class Product{
    
    private:
        long int ID;
        string name;
        string type;
        
    public:
        Product(){}
        Product(const Product & other){
			this->ID = other.ID;
            this->name = other.name;
            this->type = other.type;
        }
        
        Product(long int ID, string name, string type){
            this->ID = ID;
            this->name = name;
            this->type = type;
        }
		
		Product & operator=(const Product &other){
			this->ID = other.ID;
            this->name = other.name;
            this->type = other.type;
			
			return *this;
		}
    
        long int getID()const { return ID; }
        string getName()const{ return name; }
        string getType()const{ return type; }
    
        void setID(long int Id){ if(Id >= 0 ) this->ID = Id; }
        void setName(string name){ this->name = name;}
        void setType(string type){ this->type = type;}
		bool operator<(const Product &other) const{ return this->ID < other.ID; }
        static vector<Product> readProductsData(ifstream &file);
		void print()const{ cout<<ID<<" "<<name<<" "<<type<<endl;}
    
};

#endif
