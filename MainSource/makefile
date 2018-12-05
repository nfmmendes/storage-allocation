#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g

all: run.exe GeneralClasses.o QuickTSP.o WarehousePack.o GraphPack.o 


run.exe: GeneralClasses.o QuickTSP.o WarehousePack.o GraphPack.o main.cpp
	$(CC) $(COMPILE_FLAGS) -c main.cpp warehouse.cpp Order.h


#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses.o: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  Point.h Date.h Time.h

QuickTSP.o : PathUnity.h TSP.h State.h 
	$(CC) $(COMPILE_FLAGS) PathUnity.h TSP.h State.h

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack.o: Cell.h Shelf.h Block.h Warehouse.h BlockExit.h Corridor.h
	$(CC) $(COMPILE_FLAGS)  Cell.h Shelf.h Block.h Warehouse.h BlockExit.h Corridor.h


GraphPack.o: Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h
	$(CC) $(COMPILE_FLAGS) Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h


clean: 
	rm -f *.o *.hgc
