#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include "Product.h"
using namespace std;



vector<Product> Product::readProductsData(ifstream &file){
    
    vector<Product> products;
    string _name, _type;
    long int ID;
    
    
    int numProducts;
    file>>numProducts;
	cout<<numProducts<<endl;
    for(int i=0; i<numProducts; i++){
        file>>ID>>_name>>_type;
        products.push_back(Product(ID, _name,_type));
    }
        
    return products;
}
