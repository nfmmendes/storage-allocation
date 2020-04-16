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
#include "Curve.h"
#include "ExpeditionPoint.h"
using namespace std; 



class Warehouse{
        private:
            string name;
            vector<Block> blocks;  
            vector<pair<Product, Cell> > productAllocation;
            vector<ExpeditionPoint> expeditionPoints;   /// Points where the products must be delivered after be picked on shelves
        public:
            Warehouse(){}
            Warehouse(const Warehouse &other);
            void ReadWarehouseData(ifstream & fileName);
            void WriteWarehouseData(string fileName);
            void InsertNewBlock(Block &b);
            
            void RemoveBlock(Block &b);
            void RemoveBlock(int i);
            void SetProductAllocation(pair<Product, Cell> & productionAllocation); 
            void AddProductAllocation(pair<Product, Cell> & productionAllocation);
            void RemoveProductAllocation(Cell &cell); 
            void RemoveProductAllocation(int i); 
            
            string getName() const ;
			map<string, Block> getBlocksByName();  
            vector<Block> getBlocks() const ;
			vector<ExpeditionPoint> getExpeditionPoints();
            vector<pair<Product, Cell> > getProductAllocation() const;
			Warehouse &operator= (const Warehouse &other);
            
            void setName(string &name);
            void setBlocks(vector<Block>& blocks);
            void setProductAllocation(vector<pair<Product, Cell> > & productAllocation);
			void setExpeditionPoints(vector<ExpeditionPoint> &points);
			void printWarehouseInformation();
            
            
};

#endif
