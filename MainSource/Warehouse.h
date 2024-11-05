#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include "Block.h"
#include "Product.h"
#include "Cell.h"
#include "Curve.h"
#include "ExpeditionPoint.h"
using std::vector;
using std::pair;
using std::string;

/** 
 * @brief Warehouse class is used to represent the warehouse layout and hold the product allocations.
 */
class Warehouse{
        private:
            string name;
            vector<Block> blocks;  
            vector<ExpeditionPoint> expeditionPoints;    ///<! Points where the products must be delivered after be picked on shelves
        public:
            /**
             * @brief Constructor.
             */
            Warehouse(){}

            /**
             * @brief Copy constructor. 
             * @param other The object to be copied. 
             */
            Warehouse(const Warehouse &other);

            /**
             * @brief Read warehouse information from file. 
             * @param fileName The file name.
             */ 
            void readWarehouseData(ifstream & fileName);

            /**
             * @brief Write warehouse data to file. 
             * @param fileName The file name.
             */
            void writeWarehouseData(const string& fileName);

            /**
             * @brief Insert one block in the warehouse.
             * @param block The block to be inserted. 
             */
            void insertNewBlock(const Block &block);

            /**
             * @brief Add a product allocation.
             * @param productionAllocation A pair containing the product and its respective position.
             */
            void addProductAllocation(const pair<Product, Cell> & productionAllocation);
            
            /**
             * @brief Get the warehouse name. 
             * @return The warehouse name. 
             */
            const string& getName() const ;

            /**
			 * @brief Get blocks mapped by their names. 
			 * @return A map containing the block name as key and a pointer to a block as value. 
             */
			map<string, Block*> getBlocksByName();  

            /**
             * @brief Get the list of warehouse blocks. 
             * @return A list of blocks. 
             */
            const vector<Block>& getBlocks();

            /**
			 * @brief Get the warehouse expedition points. 
			 * @return Get a list with the expedition points. 
             */
			const vector<ExpeditionPoint>& getExpeditionPoints();

            /**
			 * @brief Warehouse assignment operator. 
			 * @param other The right hand operator object. 
			 * @return Return a reference to the modified object.
             */
			Warehouse &operator= (const Warehouse &other);

            /**
			 * @brief Print warehouse information.
             */
			void printWarehouseInformation();
};
