#EXE NAME
BIN_NAME = StorageAllocation

OBJECT_DIR := obj

#COMPILER 
CC = g++ -g

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -O2 -std=c++1z -Wall -Wextra


all: $(OBJECT_DIR) $(addprefix $(OBJECT_DIR)/, GraphPack.o Input.o Parameter.o WarehousePack.o Evaluator.o HeuristicPack.o \
	ProductAllocationProhibition.o QuickTSP.o GeneralClasses.o)
	$(CC) $(COMPILE_FLAGS) -o run main.cpp *.o 
	$(clean)

$(OBJECT_DIR)/Input.o: ProcessInputData.h InputData.h ABCAnalysis.h  OptimizationConstraints.h
	$(CC) $(COMPILE_FLAGS) -c InputData.cpp ProcessInputData.cpp ABCAnalysis.cpp OptimizationConstraints.cpp

#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
$(OBJECT_DIR)/GeneralClasses.o: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Util.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
$(OBJECT_DIR)/QuickTSP.o : PathUnity.h TSP.h QuickTSP.h State.h WarehouseToGraphConverter.h $(OBJECT_DIR)/Order GraphPack 
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp QuickTSP.cpp State.cpp WarehouseToGraphConverter.cpp $(OBJECT_DIR)/*.o

$(OBJECT_DIR)/Order.o : Order.h Product.h InputData.h 
	$(CC) $(COMPILE_FLAGS) -c Order.cpp

$(OBJECT_DIR)/ProductAllocationProhibition.o: $(OBJECT_DIR)/WarehousePack.o Product.h Cell.h Shelf.h ProductAllocationProhibition.h  \
	IsolatedFamily.h 
	$(CC) $(COMPILE_FLAGS) -c ProductAllocationProhibition.cpp IsolatedFamily.cpp

$(OBJECT_DIR)/HeuristicPack.o: $(OBJECT_DIR)/WarehousePack.o $(OBJECT_DIR)/Evaluator.o AbstractSolution.h NeighborhoodStructure.h Heuristic.h StorageILS.h \
	StorageConstructiveHeuristic.h  VND.h
	$(CC) $(COMPILE_FLAGS) -c AbstractSolution.h  StorageConstructiveHeuristic.cpp NeighborhoodStructure.h \
	StorageILS.cpp VND.cpp

$(OBJECT_DIR)/Evaluator.o: StorageSolutionEvaluator.h  $(OBJECT_DIR)/WarehousePack.o StorageAllocationSolution.h
	$(CC) $(COMPILE_FLAGS) -c  StorageSolutionEvaluator.cpp  StorageAllocationSolution.cpp

$(OBJECT_DIR)/GraphPack.o: AbstractVertex.h DistanceMatrix.h Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h \
	Transition.h DistanceMatrixCalculator.h DijkstraDistanceMatrixCalculator.h 
	$(CC) $(COMPILE_FLAGS) -c AbstractVertex.h DistanceMatrix.h Point.cpp Vertex.cpp Arc.cpp Graph.cpp HananGraph.cpp \
	 DijkstraDistanceMatrixCalculator.h Line.cpp Transition.cpp

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
$(OBJECT_DIR)/WarehousePack.o: ExpeditionPoint.h Cell.h Shelf.h  Warehouse.h BlockExit.h Curve.h Client.h Product.h \
	Order.h Corridor.h Block.h Warehouse.h
	$(CC) $(COMPILE_FLAGS) -c ExpeditionPoint.cpp Cell.cpp Shelf.cpp  BlockExit.cpp  Curve.cpp Client.cpp Product.cpp \
	Corridor.cpp Block.cpp Warehouse.cpp

$(OBJECT_DIR)/Parameter.o: Parameter.h OptimizationParameters.h
	$(CC) $(COMPILE_FLAGS) -c Parameter.cpp OptimizationParameters.cpp

$(OBJECT_DIR)/Client.o: Client.h
	$(CC) $(COMPILE_FLAGS) -c Client.cpp

clean: 
	rm -f *.o *.hgc

$(OBJECT_DIR):
	mkdir $(OBJECT_DIR)