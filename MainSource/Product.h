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

/**
 * @brief Class <c> Product </c> holds information about a product. 
 */
class Product{
    
    private:
        long int ID;
        string name;
        string family;
        
    public:
        /**
         * @brief Constructor.
         */
        Product() {}

        /**
         * @brief Copy constructor.
         * @param other The object to be copied. 
         */
        Product(const Product & other);
        
        /**
         * @brief Constructor.
         * @param ID The product id.
         * @param name The product name.
         * @param family The product family
         */
        Product(long int ID, const string& name, const string& family);

        /**
		 * @brief The product assignment operator override. 
		 * @param other The product to be copied. 
		 * @return A reference to the modified product. 
         */
		Product & operator=(const Product &other);
    
        /**
         * @brief Get the product Id.
         * @return The product id. 
         */
        long int getID()const; 

        /**
         * @brief Get the product name.
         * @return The product name. 
         */
        const string& getName()const; 

        /**
         * @brief Get the product family. 
         * @return The product family. 
         */
        const string& getFamily()const; 
    
        /**
         * @brief Set the product name. 
         * @param name The product name. 
         */
        void setName(const string& name); 

        /**
		 * @brief Product operator less than override. 
		 * @param other The right hand side object. 
		 * @return True if the left hand side object is lower than the right hand side object. 
         */
		bool operator<(const Product &other) const; 

        /**
         * @brief Read the product data from a file. 
         * @param file The file with product information.
         * @return A vector of products that were read. 
         */
        static vector<Product> readProductsData(std::ifstream &file);

        /**
		 * @brief Print product information. 
         */
		void print()const; 
};
