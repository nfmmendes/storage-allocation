#pragma once

#include<iostream>
#include "InputData.h"
#include "DistanceMatrix.h"
#include "WarehouseToGraphConverter.h"
#include "DijkstraDistanceMatrixCalculator.h"
#include "Vertex.h"
#include "AbstractVertex.h"
using namespace QuickTSP; 


/// This class will be responsible for all data input process before start the optimization
/// The reading input data process will be executed in other place 
class ProcessInputData {
	
	private:
		InputData *input;
		DistanceMatrix<Vertex> *distanceMatrix;
		WarehouseToGraphConverter warehouseToGraphConverter;
		void CreateGraph();
		void CalculateMatrixDistances();
		
		/**
		 * Create and initialize auxiliar structures needed to process input data
		 */
		void CreateOptimizationAuxiliarStructures();
	public:
		ProcessInputData();
		ProcessInputData(InputData *input);
		ProcessInputData(ProcessInputData & other);
		void ExecuteProcessData();
		
		/**
		 * 
		 */
		ProcessInputData & operator=(const ProcessInputData &other);
		
		/**
		 *	Return a pointe to the distance matrix		
		 */
		const DistanceMatrix<Vertex> *getDistanceMatrix();
		
		/**
		 * Return a pointer to the warehouse converter
		 */
		WarehouseToGraphConverter *getWarehouseToGraphConverter();
};
