#EXE NAME
BIN_NAME = StorageAllocation

#COMPILER 
CC = g++

#FLAGS TO THE COMPILER
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g

all: GeneralClasses.o WarehousePack.o GraphPack.o


#BASIC CLASSES (CAN BE USED IN ANY SOFTWARE. IT'S NOT ALGORITHM RELATED
GeneralClasses.o: Point.h Date.h Time.h
	$(CC) $(COMPILE_FLAGS) -o GeneralClasses.o  Point.h Date.h Time.h


#DAO CLASSES (DIRECTLY RELATED WITH THE DESCRIPTION OF DATA)
WarehousePack.o: Cell.h Shelf.h Block.h Warehouse.h
	$(CC) $(COMPILE_FLAGS) -o WarehousePack.o Cell.h Shelf.h Block.h Warehouse.h

GraphPack.o: Point.h Vertex.h Arc.h Graph.h HanahGraph.h
	$(CC) $(COMPILE_FLAGS) -o GraphPack.o Point.h Vertex.h Arc.h HanahGraph.h

clean: 
	$(RM) *.o *~