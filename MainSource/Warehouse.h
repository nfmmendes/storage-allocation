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
using namespace std; 



class Warehouse{
        private:
            string name;
            vector<Block> blocks;
            vector<pair<Product, Cell> > productAllocation;
            vector<Point> expeditionPoints;   /// Points where the products must be delivered after be picked on shelves
        public:
            Warehouse(){}
            Warehouse(Warehouse &other);
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
            vector<Block> getBlocks() const ;
			vector<Point> getExpeditionPoints();
            vector<pair<Product, Cell> > getProductAllocation() const;
            
            void setName(string &name);
            void setBlocks(vector<Block>& blocks);
            void setProductAllocation(vector<pair<Product, Cell> > & productAllocation);
			void setExpeditionPoints(vector<Point> &points);
			void printWarehouseInformation();
            
            
};

#endif
