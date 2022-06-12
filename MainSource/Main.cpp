#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>
#include<utility>
#include<chrono> 
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
    			
		ProcessInputData processInput(&input);
		cout<<"Converting warehouse to graph\n";
		processInput.ExecuteProcessData();
		
		Graph graph = processInput.getWarehouseToGraphConverter()->getGraph();
		OptimizationConstraints cons(input.getParameters(), input.getAllocationProhibitions(), input.getIsolatedFamily());
		Warehouse warehouse =  input.getWarehouse();
		map<pair<Cell, int>, Vertex> vertexByCell = processInput.getWarehouseToGraphConverter()->getVertexByCell();
		
		StorageAllocationSolution::setEvaluator(processInput.getDistanceMatrix(),vertexByCell, warehouse.getBlocks(), cons);
	
		cout<<"Initializing metaheuristic \n";
		
		//VND vnd(input.getProducts(),warehouse, *processInput.getDistanceMatrix(), vertexByCell , input.getOrders(),cons); 
		StorageILS ils(input.getProducts(),warehouse, processInput.getDistanceMatrix(), vertexByCell, input.getOrders(),cons);
	
		//vnd.run();
		
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		auto solution = ils.Execute();
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout<<"Final value : "<<((StorageAllocationSolution *) solution)->getSolutionValue()<< " penalty: "<<((StorageAllocationSolution *) solution)->getTotalPenalty()<<endl;
		std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milli_sec]" << std::endl;
		bool resultCheck = ((StorageAllocationSolution *) solution)->checkSolution();
		cout<<"Solution is :"<<(resultCheck? "consistent\n ": "inconsistent \n");
		((StorageAllocationSolution *) solution)->printSolution(); 
		
    }else
        cerr<<"Too few  arguments. Inform the index file name.";
    
    return 0; 
}

