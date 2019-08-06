#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>
#include<utility>
#include<algorithm>
#include "TSP.h"
#include "VND.h"
#include "InputData.h"
#include "WarehouseToGraphConverter.h"
using namespace std;
using namespace QuickTSP;


struct Allocation{
	
	string productCode; 
	string cellCode;
	int level; 
	
	Allocation(string prod, string _cell, int _level){ productCode = prod; cellCode = _cell; level = _level;}
	
};


void printRandomSolution(){
	
	vector<Allocation> allocations; 
	
	bool allocated = true; 
	int countLevel = 1; 
	int productIndex = 0;
	
	InputData input;
	vector<Block> blocks = input.getWarehouse().getBlocks();
	vector<Product> products = input.getProducts(); 
	
	random_shuffle(products.begin(), products.end());
	
	while(allocated == true && productIndex < (int)products.size()){
			allocated = false; 
			vector<Cell> possibleCells;
			for(unsigned int i = 0; i<blocks.size(); i++){
				vector<Shelf> shelves = blocks[i].getShelves();
				//cout<<"\t"<<shelves.size()<<endl;
				for(unsigned int j=0;j<shelves.size(); j++){
					vector<Cell> cells = shelves[j].getCells();
					for(unsigned int k=0;k<cells.size();k++)
						if(cells[k].getLevels() >= countLevel){
							possibleCells.push_back(cells[k]); 
						}
				}
			}
			
			if(possibleCells.size()> 0){
				allocated = true;
				
				for(unsigned int i = 0;i<possibleCells.size() && productIndex < (int) products.size();i++, productIndex++)
					allocations.push_back(Allocation(products[productIndex].getName(), possibleCells[i].getCode(), countLevel));
			}
		countLevel++;
	}
	
	ofstream file("results\\solutions.txt");
	file<<allocations.size()<<endl;
	for(unsigned int i=0;i<allocations.size();i++)
		file<<allocations[i].productCode<<" "<<allocations[i].cellCode<<" "<<allocations[i].level<<endl;
	file<<flush;
	file.close();
}




int main(int argc, char **argv){
    
    if(argc > 1){
        //Main input file name. This file will say which input files will be used
        string indexFileName = argv[1];
        InputData input(indexFileName);

        cout<<"Converting algorithm to graph\n";
        //TSP *router=NULL;
        //VND *vnd=NULL;
        
		printRandomSolution();
		
		WarehouseToGraphConverter converter(input.getWarehouse());
		cout<<"Starting conversion of warehouse to graph\n";
		converter.generateGraph();
		
        
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}

