#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++ -g

#DIRECTORIES
OBJ_DIR = ./obj

SRCS = $(shell find src/* -name \*.c)
OBJS = $(addprefix obj/, $(SRCS:.c=.o))

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -O3 -std=c++1z -Wall -Wextra


all: $(OBJ_DIR)/HananGraph.o $(OBJ_DIR)/GraphPack.o Input $(OBJ_DIR)/Parameter.o Evaluator $(OBJ_DIR)/WarehousePack.o Block Warehouse ProductAllocationProhibition QuickTSP GeneralClasses HeuristicPack
	$(CC) $(COMPILE_FLAGS) -o run Line.cpp main.cpp *.o
	

Input: ProcessInputData.h InputData.h ABCAnalysis.h  OptimizationConstraints.h
	$(CC) $(COMPILE_FLAGS) -c InputData.cpp ProcessInputData.cpp ABCAnalysis.cpp OptimizationConstraints.cpp

#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses: $(OBJ_DIR)/GraphPack.o Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Util.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
QuickTSP : PathUnity.h TSP.h QuickTSP.h State.h WarehouseToGraphConverter.h Layer.h Point.h Arc.h Graph.h $(OBJ_DIR)/Parameter.o Transition.o Order.o Vertex.o $(OBJ_DIR)/GraphPack.o
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp QuickTSP.cpp State.cpp WarehouseToGraphConverter.cpp Layer.cpp Point.cpp Arc.cpp Graph.cpp

Order : Order.h Product.o InputData.o 
	$(CC) $(COMPILE_FLAGS) -c Order.cpp


ProductAllocationProhibition: Product.o Cell.o Shelf.o Block.o ProductAllocationProhibition.h  IsolatedFamily.h
	$(CC) $(COMPILE_FLAGS) -c ProductAllocationProhibition.cpp IsolatedFamily.cpp


HeuristicPack: Warehouse Evaluator $(OBJ_DIR)/Parameter.o AbstractSolution.h NeighborhoodStructure.h Heuristic.h StorageILS.h StorageConstructiveHeuristic.h  VND.h
	$(CC) $(COMPILE_FLAGS) -c AbstractSolution.h  StorageConstructiveHeuristic.cpp NeighborhoodStructure.h StorageILS.cpp VND.cpp

Evaluator: $(OBJ_DIR)/Parameter.o StorageSolutionEvaluator.h  Warehouse StorageAllocationSolution.h
	$(CC) $(COMPILE_FLAGS) -c StorageSolutionEvaluator.cpp  StorageAllocationSolution.cpp

Warehouse : Block.o Cell.o Shelf.o BlockExit.o $(OBJ_DIR)/Corridor.o
	$(CC) $(COMPILE_FLAGS) -c Warehouse.cpp

Block : $(OBJ_DIR)/WarehousePack.o Block.h 
	$(CC) $(COMPILE_FLAGS) -c Block.cpp 

$(OBJ_DIR)/GraphPack.o: AbstractVertex.h DistanceMatrix.h Point.h Vertex.h Arc.h Graph.h Transition.h DistanceMatrixCalculator.h DijkstraDistanceMatrixCalculator.h
	$(CC) $(COMPILE_FLAGS) -c $< -o $@ 

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
$(OBJ_DIR)/WarehousePack.o : ExpeditionPoint.h Cell.h Shelf.h  Warehouse.h BlockExit.h Curve.h $(OBJ_DIR)/Client.o Product.h Order.h 
	$(CC) $(COMPILE_FLAGS) -c $< -o $@ 

$(OBJ_DIR)/HananGraph.o: $(OBJ_DIR)/GraphPack.o Vertex.h $(OBJ_DIR)/Line.o HananGraph.h
	$(CC) $(COMPILE_FLAGS) -c HananGraph.cpp -o $(OBJ_DIR)/HananGraph.o

$(OBJ_DIR)/Line.o: Line.h 
	$(CC) $(COMPILE_FLAGS) -c Line.cpp -o $(OBJ_DIR)/Line.o

$(OBJ_DIR)/Parameter.o: Parameter.h OptimizationParameters.h
	$(CC) $(COMPILE_FLAGS) -c Parameter.cpp -o $(OBJ_DIR)/Parameter.o 

$(OBJ_DIR)/Corridor.o: Corridor.h
	$(CC) $(COMPILE_FLAGS) -c Corridor.h -o $(OBJ_DIR)/Corridor.o

$(OBJ_DIR)/Client.o: Client.h
	$(CC) $(COMPILE_FLAGS) -c Client.cpp -o $(OBJ_DIR)/Client.o

clean: 
	rm -f *.o *.hgc
