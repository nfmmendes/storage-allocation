#include<iostream>
#include<string>
#include<vector>
#include<exception>
#include "ProcessInputData.h"
#include "InputData.h"
#include "DistanceMatrix.h"
#include "WarehouseToGraphConverter.h"
#include "Vertex.h"
#include "DijkstraDistanceMatrixCalculator.h"
#include "Graph.h"
#include "Arc.h"
#include "AbstractVertex.h"
using namespace QuickTSP; 
using namespace std;

/**
 *
 */
ProcessInputData::ProcessInputData(){
	this->input = NULL;
}

/**
 *
 */
ProcessInputData::ProcessInputData(InputData *input):warehouseToGraphConverter(input->getWarehouse()){
	this->input = input;
}

/**
 *
 */
ProcessInputData::ProcessInputData(ProcessInputData & other){
	this->input = other.input;
	this->distanceMatrix = other.distanceMatrix; 
}

/**
 *
 */
void ProcessInputData::CreateGraph(){
	cout<<"Starting conversion of warehouse to graph\n";
	warehouseToGraphConverter.generateGraph();
}

/**
 * 
 */
void ProcessInputData::CalculateMatrixDistances(){
	Graph graph = warehouseToGraphConverter.getGraph();
	map<string, set<Vertex> > vertexesByType = graph.getVertexesByType();

	vector<Vertex> desirableVertexes; 
	for(map<string, set<Vertex> >::iterator it = vertexesByType.begin(); it!= vertexesByType.end();it++){
		string key = it->first; 
		//Verificar se key é um valor interessante
		if(key == WarehouseToGraphConverter::UPPER_LEVEL_CELL  ||  key == WarehouseToGraphConverter::FIRST_LEVEL_CELL  || 
		   key == WarehouseToGraphConverter::UNIQUE_LEVEL_CELL ||  key == WarehouseToGraphConverter::EXPEDITION_POINT_VERTEX){
			set<Vertex> values = it->second;
			for(set<Vertex>::iterator vt= values.begin(); vt!= values.end();vt++)
				desirableVertexes.push_back((Vertex)(*vt)); 
		}
	}
	cout<<"DesirableVertexes : "<<desirableVertexes.size()<<endl;
	if(desirableVertexes.size()>0){
		DijkstraDistanceMatrixCalculator<Graph, Vertex > dijkstra; 
		this->distanceMatrix = new DistanceMatrix<Vertex>(dijkstra.calculateMatrixDistance(graph, desirableVertexes)); 
	}else{
		throw exception(); // Put some message here
	}
		
}

/**
 *
 */
void ProcessInputData::CreateOptimizationAuxiliarStructures(){
	
}

/**
 *
 */
void ProcessInputData::ExecuteProcessData(){
	this->CreateGraph(); 

	cout<<"Calculating distances \n"; 
	this->CalculateMatrixDistances();

	//Keep these lines here, they are useful to debug the code
	//this->warehouseToGraphConverter.getGraph().print();
	//this->distanceMatrix->print(); 
}


/**
 *
 */
DistanceMatrix<Vertex> * ProcessInputData::getDistanceMatrix(){
	return distanceMatrix; 
}

/**
 *
 */
WarehouseToGraphConverter * ProcessInputData::getWarehouseToGraphConverter(){
	return &warehouseToGraphConverter; 
}
