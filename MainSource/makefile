#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -O3 -std=c++11 -Wall -Wextra -g


all: GraphPack Input WarehousePack Block Warehouse ProductAllocationProhibition QuickTSP GeneralClasses
	$(CC) $(COMPILE_FLAGS) -o run main.cpp *.o
	

Input: ProcessInputData.h InputData.h ABCAnalysis.h 
	$(CC) $(COMPILE_FLAGS) -c InputData.cpp ProcessInputData.cpp ABCAnalysis.cpp

#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Util.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
QuickTSP : PathUnity.h TSP.h State.h WarehouseToGraphConverter.h Layer.h Parameter.h Transition.o Order.o
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp State.cpp WarehouseToGraphConverter.cpp Layer.cpp Parameter.cpp


Order : Order.h Product.o InputData.o 
	$(CC) $(COMPILE_FLAGS) -c Order.cpp


ProductAllocationProhibition: Product.o Cell.o Shelf.o Block.o ProductAllocationProhibition.h  IsolatedFamily.h
	$(CC) $(COMPILE_FLAGS) -c ProductAllocationProhibition.cpp IsolatedFamily.cpp

Warehouse : Block.o Cell.o Shelf.o BlockExit.o
	$(CC) $(COMPILE_FLAGS) -c Warehouse.cpp

Block : Block.h Cell.o Shelf.o Curve.o BlockExit.o
	$(CC) $(COMPILE_FLAGS) -c Block.cpp

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack : ExpeditionPoint.h Cell.h Shelf.h  Warehouse.h BlockExit.h Corridor.h Curve.h Client.h Product.h Order.h 
	$(CC) $(COMPILE_FLAGS) -c ExpeditionPoint.cpp Corridor.h Cell.cpp Shelf.cpp  BlockExit.cpp  Curve.cpp Client.cpp Product.cpp 

GraphPack: AbstractVertex.h DistanceMatrix.h Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h Transition.h DistanceMatrixCalculator.h DijkstraDistanceMatrixCalculator.h
	$(CC) $(COMPILE_FLAGS) -c AbstractVertex.h DistanceMatrix.h Point.cpp Vertex.cpp Arc.cpp Graph.cpp HananGraph.cpp DijkstraDistanceMatrixCalculator.h Line.cpp Transition.cpp


HeuristicPack: AbstractSolution.h NeighborhoodStructure.h Heuristic.h StorageILS.h StorageAllocationSolution.h StorageSolutionEvaluator.h
	$(CC) $(COMPILE_FLAGS) -c AbstractSolution.h StorageAllocationSolution.cpp NeighborhoodStructure.h StorageILS.cpp StorageSolutionEvaluator.cpp

Parameter: Parameter.h
	$(CC) $(COMPILE_FLAGS) -c Parameter.cpp

Client: Client.h
	$(CC) $(COMPILE_FLAGS) -c Client.cpp

clean: 
	rm -f *.o *.hgc
