#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g

all: run.exe GeneralClasses.o QuickTSP.o WarehousePack.o GraphPack.o 


run.exe: GeneralClasses.o QuickTSP.o WarehousePack.o GraphPack.o main.cpp
	$(CC) $(COMPILE_FLAGS) -c main.cpp warehouse.cpp Order.cpp


#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses.o: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS)  -c Point.cpp Date.cpp Time.cpp

#Classes to proceed the TSP algorithm
QuickTSP.o : PathUnity.h TSP.h State.h Layer.h
	$(CC) $(COMPILE_FLAGS) -c PathUnity.cpp TSP.cpp State.cpp Layer.cpp

#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack.o: Cell.h Shelf.h Block.h Warehouse.h BlockExit.h Corridor.h Curve.h
	$(CC) $(COMPILE_FLAGS) -c Cell.cpp Shelf.cpp Block.cpp Warehouse.cpp BlockExit.cpp Corridor.h Curve.cpp


GraphPack.o: Point.h Vertex.h Arc.h Graph.h HananGraph.h Line.h
	$(CC) $(COMPILE_FLAGS) -c Point.cpp Vertex.cpp Arc.cpp Graph.cpp HananGraph.cpp Line.cpp 


clean: 
	rm -f *.o *.hgc
