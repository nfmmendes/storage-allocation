#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include <stdio.h>
#include "Product.h"
using namespace std;



vector<Product> Product::readProductsData(string fileName){
    
    vector<Product> products;
    ifstream file;
    string _name, _type;
    long int ID;
    
    file.open(fileName,ios::in);
    
    int numProducts;
    file>>numProducts;

    for(int i=0; i<numProducts; i++){
        file>>ID>>_name>>_type;
        products.push_back(Product(ID, _name,_type));
    }
        
    return products;
}
