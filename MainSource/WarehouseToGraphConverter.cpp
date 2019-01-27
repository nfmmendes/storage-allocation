#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include<cmath>
#include "Graph.h"
#include "Warehouse.h"
#include "Point.h"
#include "WarehouseToGraphConverter.h"
using namespace QuickTSP;
using namespace std;

#define MIN_DIFF 0.000001

WarehouseToGraphConverter::WarehouseToGraphConverter(){
    
}

/**
 *  Copy constructor
 */
WarehouseToGraphConverter::WarehouseToGraphConverter(WarehouseToGraphConverter & other){
    this->warehouse = *(new Warehouse(other.warehouse));
    this->graph = *(new Graph(other.graph));
}

/**
 *  Constructor. It receaves a warehouse that will be used to create the converted graph
 */
WarehouseToGraphConverter::WarehouseToGraphConverter(Warehouse &warehouse){
    this->warehouse = *(new Warehouse(warehouse));
}

void WarehouseToGraphConverter::generateGraph(){
    
    map<const string, Vertex> vertexByCode;
    set<Arc> arcs;                                      //Store the arcs of the resulting graph
    vector<Vertex> firstLevelVertexes;                  //Store the vertexes corresponding to cell first levels. We need
                                                        // it because this vertexes will be connected after in the graph
    map<long int, vector<Curve> > curvesByCorridor;     //Stores all curves from or to a corridor
    map<long int, vector<Point> > pointsByCorridor;     //Stores all points where a curve starts or finishes, divided by corridor
    
    vector<Block> blocks = this->warehouse.getBlocks(); //Get the list of warehouse blocks
    map<Point, Vertex> vertexByPoint;
    
    //This loop creates a subgraph of the final graph to each block. These blocks will be connected by block exits in
    //second loop
    for(int i= 0; i<(int) blocks.size(); i++){
        vector<Shelf> shelves = blocks[i].getShelves();
        vector<Corridor> corridors = blocks[i].getCorridors();
        vector<Curve> curves = blocks[i].getCurves();
        
        //Create a subgraph for each shelf in the blocks. These subgraphs will be connected through the corridors in a
        //second part of the algorithm
        for(int j = 0; j < (int) shelves.size(); j++){
            
            vector<Cell> cells = shelves[j].getCells();
            vector<vector<string> > cellPositions;      //It stores each vertex in its line and row at cell
                                                        //respective shelf
            vector<Corridor> adjacentCorridors = getAdjacentCorridors(corridors, shelves[j]);
            
            double cellWidth = shelves[j].getCellWidth();
            double cellLenght = shelves[j].getCellLength();
            int numRows = shelves[j].getNumRows();
            int numColumns = shelves[j].getNumColumns();
            
            cellPositions.resize(shelves[j].getNumRows()+1);
            for(int k=0; k < (int) numRows+1; k++)
                cellPositions[k].resize(numColumns+1);
            
            for(int k=0; k < (int) cells.size(); k++)
                connectCellLevels(cells[k], firstLevelVertexes, cellPositions, vertexByCode, arcs);
            
            //Connects cells with corridors and internal nodes with border nodes in a shelf.
            for(int k=1; k< (int) numRows+1; k++){
                for(int l=1; l< (int) numColumns+1;l++){
                    //It should verify if the matrix position stores a valid
                    Vertex vertex = vertexByCode[cellPositions[k][l]];
                    
                    //There are nodes that have not direct contact with a corridor (internal nodes)
                    //In this case, we define that the cell is accessible by the closest corridor
                    // (in terms of number of cells)
                    if(numRows > 2 && numColumns > 2)
                        connectInternalNode(vertex, vertexByCode, arcs, numRows, numColumns,cellWidth, cellLenght, cellPositions);
                }
            }
            
            connectShelfToCorridor(shelves[j], adjacentCorridors, numRows, numColumns, pointsByCorridor,vertexByCode,vertexByPoint, arcs);
        }
        
        //This will allow to create arcs in the interior of corridors
        for(int j = 0; j<(int)curves.size(); j++)
            splitCorridorByCurves(curves[j], curvesByCorridor, pointsByCorridor);
        
        for(int j=0; j< (int)corridors.size(); j++)
            createArcsOnCorridors(corridors[i], pointsByCorridor, vertexByCode,vertexByPoint,arcs);
        
        connectCorridorsByCurves(curves, vertexByPoint,arcs);
        
    }
}

/**
 * This functions connects the levels inside a cell in order to have a path between any pair of divisions of a cell.
 * For now it is supposed that all cells divisions are on vertical
 */
void WarehouseToGraphConverter::connectCellLevels(Cell cell, vector<Vertex> &firstLevelVertexes,vector<vector<string>> &cellPositions,
                                                  map<const string, Vertex> & vertexByCode, set<Arc> &arcs){
    
    int numLevels = cell.getLevels();
    
    if(numLevels == 1){
        Vertex firstLevel = * (new Vertex( cell.getCode(), "UniqueLevelCell"));
        initiliazeCellFirstLevel(vertexByCode, firstLevelVertexes, cellPositions, firstLevel, cell);
        
    }else if(numLevels > 0){
        Vertex firstLevel = * (new Vertex( cell.getCode()+"_L1", "FirstLevelCell"));
        initiliazeCellFirstLevel(vertexByCode, firstLevelVertexes, cellPositions, firstLevel, cell);
        
        //Create the vertexes to represent the higher levels and the arcs to connect them
        for(int l=1; l< (int) numLevels; l++){
            Vertex vertex = * (new Vertex( cell.getCode()+"L"+to_string(l) , "UniqueLevelCell"));
            vertexByCode[vertex.getLabel()] = vertex;
            
            //We suppose that the pickers came from the lower level, take a product on the first or upper leves
            // and then come back (or stay) into the first level before go away. In this sense, all the inter-level
            // connections should be done in both senses (up-down and bottom-up)
            Arc oneSense( "arc_"+firstLevel.getLabel()+"_"+vertex.getLabel(), 1.5 ,firstLevel,vertex );
            Arc otherSense( "arc_"+vertex.getLabel()+"_"+firstLevel.getLabel(), 1.5 ,vertex,firstLevel );
            
            arcs.insert(oneSense);
            arcs.insert(otherSense);
            firstLevel = vertex;
        }
    }
}


/**
 *
 */
void WarehouseToGraphConverter::connectShelfToCorridor(const Shelf shelf,const vector<Corridor>& adjacentCorridor, int numRows,
                                                       int numColumns,map<long int, vector<Point> > & pointsByCorridor,
                                                       map<const string, Vertex> &vertexByCorridor,
                                                       map<Point, Vertex> vertexByPoint,set<Arc> &arcs ){
    int numRows = shelf.getNumRows();
    int numColumns = shelf.getNumColumns();
    double cellWidth = shelf.getCellWidth();
    double cellLength = shelf.getCellLength();
    
    
    Corridor *corridorUp;
    Corridor *corridorDown;
    Corridor *corridorLeft;
    Corridor *corridorRight;
    
    //Search and identify the adjacent corridors
    for(int i=0;i<adjacentCorridor.size();i++)
        if(adjacentCorridor[i].getDirection() == Direction::VERTICAL &&
           adjacentCorridor[i].getBeginCoords().first < shelf.getBottomLeftCoordX())
                corridorLeft =  new Corridor(adjacentCorridor[i]);
    
    for(int i=0;i<adjacentCorridor.size();i++)
        if(adjacentCorridor[i].getDirection() == Direction::VERTICAL &&
           adjacentCorridor[i].getBeginCoords().first >= shelf.getBottomLeftCoordX())
            corridorRight =  new Corridor(adjacentCorridor[i]);
    
    for(int i=0;i<adjacentCorridor.size();i++)
        if(adjacentCorridor[i].getDirection() == Direction::HORIZONTAL &&
           adjacentCorridor[i].getBeginCoords().second >= shelf.getBottomLeftCoordY())
            corridorUp =  new Corridor(adjacentCorridor[i]);
    
    for(int i=0;i<adjacentCorridor.size();i++)
        if(adjacentCorridor[i].getDirection() == Direction::HORIZONTAL &&
           adjacentCorridor[i].getBeginCoords().second <= shelf.getBottomLeftCoordY())
            corridorDown =  new Corridor(adjacentCorridor[i]);
    
    //=====================     Vertical shelf   ================================
    if(numColumns < numRows){
    
        for(int k=1; k< (int) numRows+1; k++){
            //First column
            if(corridorLeft != null){
                double coordX = shelf.getBottomLeftCoords().first + 0.5*cellWidth;
                double coordY = shelf.getBottomLeftCoords().second + cellLength*(k-1) + 0.5*cellLength;
                
                Vertex cell;
                Vertex corridor; 

            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
            }
            
            //Last column
            if(corridorRight != null){
                double coordX = shelf.getBottomLeftCoords().first+ cellWidth*(numColumns -1) + 0.5*cellWidth;
                double coordY = shelf.getBottomLeftCoords().second + cellLength*(k-1) + 0.5*cellLength;
                
                Vertex cell;
                Vertex corridor;

            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
            }
        }
               
    }
    
    //=======================   Horizontal shelf ==============================
    else if(numRows < numColumns){
        for(int k=1; k< (int) numColumns+1; k++){
            //First row
            if(corridorUp != null){
                double coordX = shelf.getBottomLeftCoords().first+ cellWidth*(k-1) + 0.5*cellWidth;
                double coordY = shelf.getBottomLeftCoords().second + 0.5*cellLength;
                
                Vertex cell;
                Vertex corridor;

            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
            }
            
            //Last row
            if(corridorDown != null){
                double coordX = shelf.getBottomLeftCoords().first+ cellWidth*(k-1) + 0.5*cellWidth;
                double coordY = shelf.getBottomLeftCoords().second + cellLength*(numRows - 1) + 0.5*cellLength;
                
                Vertex cell;
                Vertex corridor;

            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
            }
        }
    }
    
    //=======================   Squared shelf ==============================
    if(numRows == numColumns){
        
    }
    
}


/**
 *
 */
void WarehouseToGraphConverter::connectCorridorsByCurves(vector<Curve> curves, map<Point,Vertex> & vertexByPoint, set<Arc> &arcs){
    for(int i=0; i< (int)curves.size();i++){
        Vertex begin = vertexByPoint[curves[i].getStartingPoint()];
        Vertex end = vertexByPoint[curves[i].getEndingPoint()];
        
        double distance = curves[i].getStartingPoint().getDistance(curves[i].getEndingPoint());
        
        arcs.insert(Arc("arc_"+begin.getLabel()+ "_"+end.getLabel(),distance,begin, end));
    }
}

/**
 *  It create arcs in the corridor based on curve points and corridor extremities
 */
void WarehouseToGraphConverter::createArcsOnCorridors(const Corridor corridor, map<long int, vector<Point>>& pointsByCorridor,map<const string,Vertex>& vertexByCode, map<Point, Vertex> &vertexByPoint, set<Arc> &arcs){
    
    long int id = corridor.getId();
    
    vector<Point> points = pointsByCorridor[id];
    corridor.orderCorridorPoints(points);
    
    int count = 1;
    Vertex first("corridor_"+to_string(id)+"point_begin", "CorridorCurvePoint");
    pair<double,double> beginCorridor = corridor.getBeginCoords();
    vertexByCode[first.getLabel()] = first;
    vertexByPoint[Point("corridorBegin_"+to_string(id),beginCorridor.first, beginCorridor.second, 0)] = first;
    
    //If the initial point of a corridor is not a curve pointe, we do it
    if(fabs(beginCorridor.first - points[0].getCoordX()) > MIN_DIFF ||
       fabs(beginCorridor.second - points[0].getCoordY()) > MIN_DIFF){
        
        Vertex second("corridor_"+to_string(id)+"point_begin", "CorridorCurvePoint");
        vertexByCode[second.getLabel()] = second;
        
        double distance = sqrt(pow(beginCorridor.first-points[0].getCoordX(),2) +
                               pow(beginCorridor.second-points[0].getCoordY(),2));
        
        arcs.insert(Arc("arc_"+first.getLabel()+ "_"+second.getLabel(),distance,first, second));
        
        count++;
        if(corridor.getSense() == Sense::BOTH)
            arcs.insert(Arc("arc_"+second.getLabel()+ "_"+first.getLabel(), distance, second, first));
        
        
        first = second;
        
    }
    
    //After define the first arc we do the orders links
    for(int k=0; k<(int)points.size()-1; k++){
        Vertex second = * (new Vertex("corridor_"+to_string(id)+"point_"+to_string(count), "CorridorCurvePoint"));
        vertexByCode[second.getLabel()] = second;
        
        double distance = sqrt(pow(points[k+1].getCoordX()-points[k].getCoordX(),2)+
                               pow(points[k+1].getCoordY()-points[k].getCoordY(),2));
        
        arcs.insert(Arc("arc_"+first.getLabel()+ "_"+second.getLabel(),distance,first, second));
        
        count++;
        if(corridor.getSense() == Sense::BOTH)
            arcs.insert(Arc("arc_"+second.getLabel()+ "_"+first.getLabel(), distance, second, first));
        first = second;
    }
}



/**
 *  Auxiliary function. It gets all the curve points in a corridor. These points will be used in other function
 *  to generate new vertexes and arcs.
 */
void WarehouseToGraphConverter::splitCorridorByCurves(const Curve &curve, map<long int, vector<Curve> > &curvesByCorridor,
                           map<long int, vector<Point> >&pointsByCorridor){
    
    long int start = curve.getStartCorridor();
    long int end = curve.getEndCorridor();
    
    Point curveStartPoint = curve.getStartingPoint();
    Point curveEndingPoint = curve.getEndingPoint();
    
    curvesByCorridor[start].push_back(curve);
    curvesByCorridor[end].push_back(curve);
    
    //Almost a javascript code, but it works!!
    
    //Find condition
    vector<Point> points = pointsByCorridor[start];
    if(!any_of(points.begin(), points.end(),[&curveStartPoint](const Point &b){
              return fabs(curveStartPoint.getCoordX() - b.getCoordX()) < MIN_DIFF &&
                     fabs(curveStartPoint.getCoordY() - b.getCoordY()) < MIN_DIFF;
          })){
           pointsByCorridor[start].push_back(curveStartPoint);
       }
       
    //Find condition
    points = pointsByCorridor[end];
    if(!any_of(pointsByCorridor[end].begin(), pointsByCorridor[end].end(),[&curveStartPoint](const Point &b){
                 return fabs(curveStartPoint.getCoordX() - b.getCoordX()) < MIN_DIFF &&
                        fabs(curveStartPoint.getCoordY() - b.getCoordY()) < MIN_DIFF;
           })){
            pointsByCorridor[end].push_back(curveStartPoint);
        }
}


/**
 *  Auxiliary function. Connects two internal cells in a shelf (cells that have just other cells around).
 *  Internal cells in vertical shelves should be connected their left and right neighbors (cells closer to a corridor)
 *  Internal cells in horizontal shelves should be connected with their up and down neighbors (cells closer to a corridor)
 */
void WarehouseToGraphConverter::connectInternalNode(Vertex vertex, map<const string,Vertex> & vertexByCode, set<Arc> &arcs,
                                                    const int numRows, const int numColumns,const int k,const int l,
                                                    double width, double length,const vector<vector<string> > cellPositions){
    
    if(numRows < numColumns){              // Horizontal shelf
        
        if(k > 1){
            string sUp = cellPositions[k-1][l];
            connectVertexesByTwoArcs(vertex,sUp, vertexByCode, arcs, length);
        }
        
        if(k<numRows){
            string sDown = cellPositions[k+1][l];
            connectVertexesByTwoArcs(vertex,sDown, vertexByCode, arcs, length);
        }
    }else if(numRows > numColumns){         // Vertical shelf
        
        if(l > 1){
            const string sLeft = cellPositions[k][l-1];
            connectVertexesByTwoArcs(vertex,sLeft, vertexByCode, arcs, width);
        }
        
        if(l < numColumns){
            const string sRight = cellPositions[k][l+1];
            connectVertexesByTwoArcs(vertex,sRight, vertexByCode, arcs, width);
        }
        
    }else if(numRows == numColumns){        // Squared shelf
        
        if(k > 1){
            string sUp = cellPositions[k-1][l];
            connectVertexesByTwoArcs(vertex,sUp, vertexByCode, arcs, length);
        }
        
        if(k<numRows){
            string sDown = cellPositions[k+1][l];
            connectVertexesByTwoArcs(vertex,sDown, vertexByCode, arcs, length);
        }
        
        if(l > 1){
            const string sLeft = cellPositions[k][l-1];
            connectVertexesByTwoArcs(vertex,sLeft, vertexByCode, arcs, width);
        }
        
        if(l < numColumns){
            const string sRight = cellPositions[k][l+1];
            connectVertexesByTwoArcs(vertex,sRight, vertexByCode, arcs, width);
        }
    }
}


/**
 *  Function to get the shelf adjacent corridors, in other words, the corridors from where the shelf can be
 *  accessed. It is supposed here (and in other points of the code) that only vertical corridors can access
 *  vertical shelves, the same for horizontal ones. Squared corridors can be accessed by corridors with any
 *  shelf (horizontal or vertical). It is supposed also that only the closest corridor can access the shelf
 *  If there are two corridors between two shelves (probably with inverse senses) we consider that you need
 *  to move from the farstest to the closest one.
 */
vector<Corridor> WarehouseToGraphConverter::getAdjacentCorridors(const vector<Corridor> & corridors, Shelf shelf){
    int numLines = shelf.getNumRows();
    int numColumns = shelf.getNumColumns();
    
    Corridor closestAtLeft, closestAtRight, closestOver, closestBellow;
    double minDistanceLeft, minDistanceRight, minDistanceOver, minDistanceDown=0;
    minDistanceLeft = minDistanceRight = minDistanceOver = minDistanceDown;
    vector<Corridor> closestAtAll;
    bool left, right, up, down=false;
    
    left = right = up = down;
    
    pair<double,double> shelfCoords = shelf.getBottomLeftCoords();
    
    //This first if looks for the closest corridors in vertical direction, if the shelf is also in this same position
    //If numColumns == numRows the two ifs will be executed
    if(numColumns <= numLines){
        for(int i=0;i<(int)corridors.size();i++){
            if(corridors[i].getDirection() ==  Direction::VERTICAL && doCorridorTranverse(corridors[i], shelf)){
                
                double xCoordCorridor = corridors[i].getBeginCoords().first;
                
                //If the corridor has a lower x coordinate so it is in the shelf left
                if(xCoordCorridor - shelfCoords.first < -1*MIN_DIFF  && fabs(shelfCoords.first - xCoordCorridor) < minDistanceLeft){
                    minDistanceLeft = fabs(shelfCoords.first - xCoordCorridor);
                    closestAtLeft = corridors[i];
                    left = true;
                }else if(xCoordCorridor - shelfCoords.first > MIN_DIFF && fabs(shelfCoords.first - xCoordCorridor) < minDistanceRight){
                    minDistanceRight = fabs(shelfCoords.first - xCoordCorridor);
                    closestAtRight = corridors[i];
                    right = true;
                }else if(fabs(xCoordCorridor - shelfCoords.first) < MIN_DIFF){
                    closestAtLeft = corridors[i];
                    left = true;
                }
            }
        }
    }
    
    //This first if looks for the closest corridors in horizontal direction, if the shelf is also in this same position
    //If numColumns == numRows the two ifs will be executed
    if(numColumns <= numLines){
        for(int i=0; i<(int)corridors.size();i++){
            if(corridors[i].getDirection() == Direction::HORIZONTAL && doCorridorTranverse(corridors[i], shelf)){
                double yCoordCorridor = corridors[i].getBeginCoords().second;
                
                //If the corridor has a lower x coordinate so it is in the shelf left
                if(yCoordCorridor - shelfCoords.second < -1*MIN_DIFF  && fabs(shelfCoords.second - yCoordCorridor) < minDistanceDown){
                    minDistanceDown = fabs(shelfCoords.second - yCoordCorridor);
                    closestBellow = corridors[i];
                    down = true;
                }else if(yCoordCorridor - shelfCoords.second > MIN_DIFF && fabs(shelfCoords.second - yCoordCorridor) < minDistanceOver){
                    minDistanceOver = fabs(shelfCoords.second - yCoordCorridor);
                    closestOver = corridors[i];
                    up = true;
                }else if(fabs(yCoordCorridor - shelfCoords.second) < MIN_DIFF){
                    closestOver = corridors[i];
                    down = true;
                }
            }
        }
    }
    
    //Eventually a shelf does not have a corridor to access their products from a size (as in case of close to wall shelves)
    //It also prevents no initialized corridors be inserted in the solutions
    if(left) closestAtAll.push_back(closestAtLeft);
    if(right) closestAtAll.push_back(closestAtRight);
    if(up) closestAtAll.push_back(closestOver);
    if(down) closestAtAll.push_back(closestBellow);
    
    return closestAtAll;
}

/**
 *  This function verify if a corridor tranverse a shelf, in other words, if a corridor starts at begining (or before)
 *  a shelf and finish at the end (or after) of a shelf
 */
bool WarehouseToGraphConverter::doCorridorTranverse(const Corridor &corridor,const Shelf &shelf){
    int numLines = shelf.getNumRows();
    int numColumns = shelf.getNumColumns();
    pair<double,double> coordCorridor = corridor.getBeginCoords();
    pair<double, double> shelfCoords = shelf.getBottomLeftCoords();
    double len = corridor.getLength();
    
    if(numColumns < numLines && corridor.getDirection() == Direction::VERTICAL){
        return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second;
    }else if(numColumns > numLines && corridor.getDirection() == Direction::HORIZONTAL){
        return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first;
    }else if(numColumns == numLines){
        if(corridor.getDirection() == Direction::HORIZONTAL)
            return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first;
        if(corridor.getDirection() == Direction::VERTICAL)
            return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second;
    }
    return false;
    
    
    
    
    
}

/**
 *  Auxiliar function to connect a two vertex between them by two arcs (in opposite senses).
 */
void WarehouseToGraphConverter::connectVertexesByTwoArcs(Vertex & first, string second,map<const string, Vertex> & vertexByCode,
                                                       set<Arc> &arcs, double size){
    
    Vertex secondVertex = vertexByCode[second];
    
    //Two arcs (in opposite senses) to each adjacent cell
    arcs.insert(Arc("arc_"+first.getLabel()+"_"+secondVertex.getLabel(), size, first, secondVertex));
    arcs.insert(Arc("arc_"+secondVertex.getLabel()+"_"+first.getLabel(), size, secondVertex, first));
}


/**
 *   Auxiliary function to fill the vertexByCode, firstLevelVertex and cellPositionsStructure
 */
void WarehouseToGraphConverter::initiliazeCellFirstLevel(map<const string, Vertex> & vertexByCode,
                                                         vector<Vertex> &firstLevelVertexes, 
                                                         vector<vector<string> > &cellPositions,
                                                         Vertex firstLevel, Cell cell){

                vertexByCode[firstLevel.getLabel()] =  firstLevel;
                firstLevelVertexes.push_back(firstLevel);
    
                int row = cell.getRow();
                int column = cell.getColumn();
    
                if(row > 0 && row <= (int)cellPositions.size())
                    if(column > 0 && column <= (int)cellPositions[row].size())
                        cellPositions[row][column] = firstLevel.getLabel();
}
