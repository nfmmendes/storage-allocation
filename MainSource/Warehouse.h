#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
#include "Block.h"
#include "Product.h"
#include "Cell.h"
using namespace std; 



class Warehouse{
        private:
            string name;
            vector<Block> blocks;
            vector<pair<Product, Cell> > productAllocation;
        public:
            Warehouse();
            Warehouse(Warehouse &other);
            void ReadWarehouseData(string fileName);
            void WriteWarehouseData(string fileName);
            void InsertNewBlock(Block &b);
            
            void RemoveBlock(Block &b);
            void RemoveBlock(int i);
            void SetProductAllocation(pair<Product, Cell> & productionAllocation); 
            void AddProductAllocation(pair<Product, Cell> & productionAllocation);
            void RemoveProductAllocation(Cell &cell); 
            void RemoveProductAllocation(int i); 
            
            string GetName(string &name);
            vector<Block &> GetBlocks(); 
            vector<pair<Product, Cell> > GetProductAllocation();
            
            void SetName(string &name); 
            void SetBlocks(vector<Block &> blocks);
            void SetProductAllocation(vector<pair<Product, Cell> > & productAllocation); 
            
            
};

#endif