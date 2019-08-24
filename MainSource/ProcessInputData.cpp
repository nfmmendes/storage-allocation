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
ProcessInputData::ProcessInputData(InputData *input){
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
	WarehouseToGraphConverter converter(input->getWarehouse());
	cout<<"Starting conversion of warehouse to graph\n";
	converter.generateGraph();
}

/**
 * 
 */
void ProcessInputData::CalculateMatrixDistances(){
	Graph graph = converter->getGraph();
	map<string, set<Vertex> > vertexesByType = graph.getVertexesByType();
	
	vector<AbstractVertex> desirableVertexes; 
	for(map<string, set<Vertex> >::iterator it = vertexesByType.begin(); it!= vertexesByType.end();it++){
		string key = it->first; 
		//Verificar se key é um valor interessante
		
		set<Vertex> values = it->second;
		for(set<Vertex>::iterator vt= values.begin(); vt!= values.end();vt++)
			desirableVertexes.push_back((AbstractVertex)(*vt)); 
	}
		
	if(desirableVertexes.size()>0){
		DijkstraDistanceMatrixCalculator<Graph, DistanceMatrix<Vertex> > dijkstra; 
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
	this->CalculateMatrixDistances();
}


/**
 *
 */
DistanceMatrix<Vertex> * ProcessInputData::getDistanceMatrix(){
	
}

/**
 *
 */
WarehouseToGraphConverter * ProcessInputData::getWarehouseToGraphConverter(){
	
}
