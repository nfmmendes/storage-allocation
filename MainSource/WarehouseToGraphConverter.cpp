#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Graph.h"
#include "Warehouse.h"
#include "WarehouseToGraphConverter.h"
using namespace QuickTSP;
using namespace std;


WarehouseToGraphConverter::WarehouseToGraphConverter(){
    
}

WarehouseToGraphConverter::WarehouseToGraphConverter(WarehouseToGraphConverter & other){
    this->warehouse = *(new Warehouse(other.warehouse));
    this->graph = *(new Graph(other.graph));
}

WarehouseToGraphConverter::WarehouseToGraphConverter(Warehouse &warehouse){
    this->warehouse = *(new Warehouse(warehouse));
}

void WarehouseToGraphConverter::generateGraph(){
    
    map<string, Vertex> vertexByCode;
    vector<Arc> arcs;
    vector<Vertex> firstLevelVertexes;                  //Store the vertexes corresponding to cell first levels. We need
                                                        // it because this vertexes will be connected after in the graph
    
    vector<Block> blocks = this->warehouse.getBlocks();
    for(int i= 0; i<(int) blocks.size(); i++){
        vector<Shelf> shelves = blocks[i].getShelves();
        //Create a subgraph for each shelf in the blocks. These shelves will be connected through the corridors in a
        //second part of the algorithm
        for(int j = 0; j < (int) shelves.size(); j++){
            
            vector<Cell> cells = shelves[j].getCells();
            map<string, pair<int,int> > cellPositions;      //To each vertex, stores its line and row at cell
                                                           // respective shelf
            
            for(int k=0; k < (int) cells.size(); k++){
                int numLevels = cells[k].getLevels();
                
                if(numLevels == 1){
                    Vertex firstLevel = * (new Vertex( cells[k].getCode(), "UniqueLevelCell"));
                    initiliazeCellFirstLevel(vertexByCode, firstLevelVertexes, cellPositions, firstLevel, cells[k]);
                    
                }else if(numLevels > 0){
                    Vertex firstLevel = * (new Vertex( cells[k].getCode()+"_L1", "FirstLevelCell"));
                    initiliazeCellFirstLevel(vertexByCode, firstLevelVertexes, cellPositions, firstLevel, cells[k]);
                    
                    for(int l=1; k< (int) numLevels; k++){
                        Vertex vertex = * (new Vertex( cells[k].getCode()+"L"+to_string(l) , "UniqueLevelCell"));
                        vertexByCode[vertex.getLabel()] = vertex;
                        Arc oneSense( "arc_"+firstLevel.getLabel()+"_"+vertex.getLabel(), 1.5 ,firstLevel,vertex );
                        Arc otherSense( "arc_"+vertex.getLabel()+"_"+firstLevel.getLabel()
                                       , 1.5 ,vertex,firstLevel );
                        
                        firstLevel = vertex;
                    }
                }
            }
        }
    }
    
    
}

void WarehouseToGraphConverter::initiliazeCellFirstLevel(map<string, Vertex> & vertexByCode,
                                                         vector<Vertex> &firstLevelVertexes, 
                                                         map<string, pair<int,int> > &cellPositions,
                                                         Vertex firstLevel, Cell cell){

                vertexByCode[firstLevel.getLabel()] =  firstLevel;
                firstLevelVertexes.push_back(firstLevel);
                cellPositions[firstLevel.getLabel()] = make_pair(cell.getRow(), cell.getColumn());
}
