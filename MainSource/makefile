#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++ -g

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -O2 -std=c++1z -Wall -Wextra


all: GraphPack Input Parameter Evaluator HeuristicPack WarehousePack Warehouse ProductAllocationProhibition QuickTSP GeneralClasses
	$(CC) $(COMPILE_FLAGS) -o run main.cpp *.o
	

Input: ProcessInputData.h InputData.h ABCAnalysis.h  OptimizationConstraints.h
	$(CC) $(COMPILE_FLAGS) -c InputData.cpp ProcessInputData.cpp ABCAnalysis.cpp OptimizationConstraints.cpp

#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Util.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
QuickTSP : PathUnity.h TSP.h QuickTSP.h State.h WarehouseToGraphConverter.h Order GraphPack
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp QuickTSP.cpp State.cpp WarehouseToGraphConverter.cpp

Order : Order.h Product.h InputData.h 
	$(CC) $(COMPILE_FLAGS) -c Order.cpp

ProductAllocationProhibition: WarehousePack Product.h Cell.h Shelf.h ProductAllocationProhibition.h  IsolatedFamily.h
	$(CC) $(COMPILE_FLAGS) -c ProductAllocationProhibition.cpp IsolatedFamily.cpp

HeuristicPack: Warehouse Evaluator AbstractSolution.h NeighborhoodStructure.h Heuristic.h StorageILS.h StorageConstructiveHeuristic.h  VND.h
	$(CC) $(COMPILE_FLAGS) -c AbstractSolution.h  StorageConstructiveHeuristic.cpp NeighborhoodStructure.h StorageILS.cpp VND.cpp

Evaluator: StorageSolutionEvaluator.h  Warehouse StorageAllocationSolution.h
	$(CC) $(COMPILE_FLAGS) -c  StorageSolutionEvaluator.cpp  StorageAllocationSolution.cpp

Warehouse:
	$(CC) $(COMPILE_FLAGS) -c Warehouse.cpp

GraphPack: AbstractVertex.h DistanceMatrix.h Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h Transition.h DistanceMatrixCalculator.h DijkstraDistanceMatrixCalculator.h
	$(CC) $(COMPILE_FLAGS) -c AbstractVertex.h DistanceMatrix.h Point.cpp Vertex.cpp Arc.cpp Graph.cpp HananGraph.cpp DijkstraDistanceMatrixCalculator.h Line.cpp Transition.cpp

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack : ExpeditionPoint.h Cell.h Shelf.h  Warehouse.h BlockExit.h Curve.h Client.h Product.h Order.h Corridor.h Block.h
	$(CC) $(COMPILE_FLAGS) -c ExpeditionPoint.cpp Cell.cpp Shelf.cpp  BlockExit.cpp  Curve.cpp Client.cpp Product.cpp Corridor.cpp Block.cpp

Parameter: Parameter.h OptimizationParameters.h
	$(CC) $(COMPILE_FLAGS) -c Parameter.cpp OptimizationParameters.cpp

Client: Client.h
	$(CC) $(COMPILE_FLAGS) -c Client.cpp

clean: 
	rm -f *.o *.hgc
