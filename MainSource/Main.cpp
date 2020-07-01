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
#include "ProcessInputData.h"
#include "ABCAnalysis.h"
#include "OptimizationConstraints.h"
#include "StorageAllocationSolution.h"
#include "StorageConstructiveHeuristic.h"
#include "StorageILS.h"
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
	
	//random_shuffle(products.begin(), products.end());
	
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


ABCAnalysis * createABCAnalysis(InputData &input){
	
	vector<Order> orders = input.getOrders();
	const int numClasses = 3; 
	vector<double> thresholds;
	
	thresholds.push_back(30);	thresholds.push_back(70);
	ABCAnalysis *analysis = new ABCAnalysis(orders,numClasses, thresholds); 
	
	return analysis;
}


int main(int argc, char **argv){
    
    if(argc > 1){
        //Main input file name. This file will say which input files will be used
        string indexFileName = argv[1];
        InputData input(indexFileName);
		
		ABCAnalysis * abc = createABCAnalysis(input); 
		abc->execute(); 

		printRandomSolution();
        cout<<"Converting algorithm to graph\n";
			
		ProcessInputData processInput(&input);
		processInput.ExecuteProcessData();
		
		Graph graph = processInput.getWarehouseToGraphConverter()->getGraph();
		OptimizationConstraints cons(input.getParameters(), input.getAllocationProhibitions(), input.getIsolatedFamily());
		Warehouse warehouse =  input.getWarehouse();
		map<pair<Cell, int>, Vertex> vertexByCell = processInput.getWarehouseToGraphConverter()->getVertexByCell();
		
		cout<<"Initializing metaheuristic \n";
	//	StorageConstructiveHeuristic constr(input.getProducts(),warehouse,*processInput.getDistanceMatrix(),vertexByCell, input.getOrders(),cons); 
	//	StorageAllocationSolution constructiveSolution = constr.Execute();
		
		//VND vnd(input.getProducts(),warehouse, *processInput.getDistanceMatrix(), vertexByCell , input.getOrders(),cons); 
		StorageILS ils(input.getProducts(),warehouse, *processInput.getDistanceMatrix(), vertexByCell, input.getOrders(),cons);
		//vnd.run();
		ils.Execute();
        
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}

