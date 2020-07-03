#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++ -g

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -O3 -std=c++1z -Wall -Wextra


all: GraphPack Input Parameter Evaluator WarehousePack Block Warehouse ProductAllocationProhibition QuickTSP GeneralClasses HeuristicPack
	$(CC) $(COMPILE_FLAGS) -o run main.cpp *.o
	

Input: ProcessInputData.h InputData.h ABCAnalysis.h  OptimizationConstraints.h
	$(CC) $(COMPILE_FLAGS) -c InputData.cpp ProcessInputData.cpp ABCAnalysis.cpp OptimizationConstraints.h

#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Util.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
QuickTSP : PathUnity.h TSP.h QuickTSP.h State.h WarehouseToGraphConverter.h Layer.h Parameter.h Transition.o Order.o Vertex.o 
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp QuickTSP.cpp State.cpp WarehouseToGraphConverter.cpp Layer.cpp Parameter.cpp


Order : Order.h Product.o InputData.o 
	$(CC) $(COMPILE_FLAGS) -c Order.cpp


ProductAllocationProhibition: Product.o Cell.o Shelf.o Block.o ProductAllocationProhibition.h  IsolatedFamily.h
	$(CC) $(COMPILE_FLAGS) -c ProductAllocationProhibition.cpp IsolatedFamily.cpp


HeuristicPack: Warehouse Evaluator Parameter AbstractSolution.h NeighborhoodStructure.h Heuristic.h StorageILS.h StorageConstructiveHeuristic.h  VND.h
	$(CC) $(COMPILE_FLAGS) -c AbstractSolution.h  StorageConstructiveHeuristic.cpp NeighborhoodStructure.h StorageILS.cpp VND.cpp

Evaluator: Parameter StorageSolutionEvaluator.h  Warehouse StorageAllocationSolution.h
	$(CC) $(COMPILE_FLAGS) -c StorageSolutionEvaluator.cpp  StorageAllocationSolution.cpp

Warehouse : Block.o Cell.o Shelf.o BlockExit.o
	$(CC) $(COMPILE_FLAGS) -c Warehouse.cpp

Block : WarehousePack Block.h 
	$(CC) $(COMPILE_FLAGS) -c Block.cpp 

GraphPack: AbstractVertex.h DistanceMatrix.h Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h Transition.h DistanceMatrixCalculator.h DijkstraDistanceMatrixCalculator.h
	$(CC) $(COMPILE_FLAGS) -c AbstractVertex.h DistanceMatrix.h Point.cpp Vertex.cpp Arc.cpp Graph.cpp HananGraph.cpp DijkstraDistanceMatrixCalculator.h Line.cpp Transition.cpp


#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack : ExpeditionPoint.h Cell.h Shelf.h  Warehouse.h BlockExit.h Corridor.h Curve.h Client.h Product.h Order.h 
	$(CC) $(COMPILE_FLAGS) -c ExpeditionPoint.cpp Corridor.h Cell.cpp Shelf.cpp  BlockExit.cpp  Curve.cpp Client.cpp Product.cpp

Parameter: Parameter.h OptimizationParameters.h
	$(CC) $(COMPILE_FLAGS) -c Parameter.cpp OptimizationParameters.h

Client: Client.h
	$(CC) $(COMPILE_FLAGS) -c Client.cpp

clean: 
	rm -f *.o *.hgc
