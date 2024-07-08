#include<iostream>
#include<string>
#include<cstdlib>
#include<fstream>
#include<cmath>
#include<vector>
#include<chrono> 
#include "TSP.h"
#include "VND.h"
#include "InputData.h"
#include "WarehouseToGraphConverter.h"
#include "ProcessInputData.h"
#include "ABCAnalysis.h"
#include "OptimizationConstraints.h"
#include "OptimizationParameters.h"
#include "StorageAllocationSolution.h"
#include "StorageConstructiveHeuristic.h"
#include "StorageILS.h"
using namespace QuickTSP;

struct Allocation{
	
	std::string productCode; 
	std::string cellCode;
	int level; 
	
	Allocation(std::string prod, std::string _cell, int _level){ productCode = prod; cellCode = _cell; level = _level;}
	
};

ABCAnalysis * createABCAnalysis(InputData &input){
	
	std::vector<Order> orders = input.getOrders();
	const int numClasses = 3; 
	std::vector<double> thresholds;
	
	thresholds.push_back(30);	thresholds.push_back(70);
	ABCAnalysis *analysis = new ABCAnalysis(orders,numClasses, thresholds); 
	
	return analysis;
}

void initializeRuntimeParameters(map<std::string, char*> arguments) {
	int abcAClassThresshold = -1;
	int abcBClassThresshold = -1;
	int maxPertubations = -1;
	int iwsMax = -1;
	int bruteforce = -1;
	int insertion = -1;

	if(arguments.find("--athreshold") != arguments.end())
		abcAClassThresshold = atoi(arguments["--athreshold"]);
	
	if(arguments.find("--bthreshold") != arguments.end())
		abcBClassThresshold = atoi(arguments["--bthreshold"]);
	
	if(arguments.find("--IWImax") != arguments.end())
		iwsMax = atoi(arguments["--IWImax"]);

	if(arguments.find("--pertubations") != arguments.end())
		maxPertubations = atoi(arguments["--pertubations"]);

	if(arguments.find("--bruteforce") != arguments.end())
		bruteforce = atoi(arguments["--bruteforce"]);
	
	if(arguments.find("--insertion") != arguments.end())
		insertion = atoi(arguments["--insertion"]);

	OptimizationParameters::initialize(abcAClassThresshold, abcBClassThresshold, maxPertubations, iwsMax, bruteforce, insertion);
}

int main(int argc, char **argv){

	// Check the list of arguments. The unique mandatory argument is -f (file name). All the others 
	// are used to algorithm tunning and are then optional. 
	if(argc <= 1){
		std::cerr << "There are missing arguments. Set at least the input file name." << std::endl;
		return 1; 
	}

	map<std::string, char*> arguments; 
	for(auto i=1; i<argc; i+= 2){
		arguments[argv[i]] = argv[i+1];
	}

	initializeRuntimeParameters(arguments); 

	std::string fileName; 
	if(arguments.find("-f") != arguments.end())
	 	fileName = arguments["-f"];
	else {
		std::cerr << "File name does not specified.";
		return 1;
	}

	//Main input file name. This file will say which input files will be used
	InputData input(fileName);
	
	ProcessInputData processInput(&input);
	std::cout<<"Converting warehouse to graph\n";
	processInput.ExecuteProcessData();

	Graph graph = processInput.getWarehouseToGraphConverter()->getGraph();
	OptimizationConstraints cons(input.getParameters(), input.getAllocationProhibitions(), input.getIsolatedFamily());

	Warehouse warehouse =  input.getWarehouse();
	map<pair<Cell, int>, Vertex> vertexByCell = processInput.getWarehouseToGraphConverter()->getVertexByCell();

	StorageAllocationSolution::setEvaluator(processInput.getDistanceMatrix(),vertexByCell, warehouse.getBlocks(), cons);

	cout<<"Initializing metaheuristic \n";
	
	StorageILS ils(input.getProducts(),warehouse, processInput.getDistanceMatrix(), vertexByCell, input.getOrders(),cons);

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	auto solution = ils.Execute();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout<<"Final value : "<<((StorageAllocationSolution *) solution)->getSolutionValue()<< " penalty: "<<((StorageAllocationSolution *) solution)->getTotalPenalty()<<endl;
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[milli_sec]" << std::endl;
	bool resultCheck = ((StorageAllocationSolution *) solution)->checkSolution();
	cout<<"Solution is :"<<(resultCheck? "consistent\n ": "inconsistent \n");
	((StorageAllocationSolution *) solution)->printSolution(); 
		
    return 0; 
}

