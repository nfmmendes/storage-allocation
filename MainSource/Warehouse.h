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

class Warehouse{
        private:
            std::string name;
            std::vector<Block> blocks;  
            std::vector<pair<Product, Cell> > productAllocation;
            std::vector<ExpeditionPoint> expeditionPoints;   /// Points where the products must be delivered after be picked on shelves
        public:
            Warehouse(){}
            Warehouse(const Warehouse &other);
            void ReadWarehouseData(ifstream & fileName);
            void WriteWarehouseData(string fileName);
            void InsertNewBlock(Block &b);
            
            void RemoveBlock(Block &b);
            void RemoveBlock(int i);
            void SetProductAllocation(std::pair<Product, Cell> & productionAllocation); 
            void AddProductAllocation(std::pair<Product, Cell> & productionAllocation);
            void RemoveProductAllocation(Cell &cell); 
            void RemoveProductAllocation(int i); 
            
            std::string getName() const ;
			std::map<std::string, Block> getBlocksByName();  
            std::vector<Block> &getBlocks();
			std::vector<ExpeditionPoint> getExpeditionPoints();
            std::vector<std::pair<Product, Cell> > getProductAllocation() const;
			Warehouse &operator= (const Warehouse &other);
            
            void setName(std::string &name);
            void setBlocks(std::vector<Block>& blocks);
            void setProductAllocation(std::vector<std::pair<Product, Cell> > & productAllocation);
			void setExpeditionPoints(std::vector<ExpeditionPoint> &points);
			void printWarehouseInformation();
            
            
};
