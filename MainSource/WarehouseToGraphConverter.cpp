#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include<cmath>
#include<utility>
#include "Graph.h"
#include "Warehouse.h"
#include "Point.h"
#include "Corridor.h"
#include "WarehouseToGraphConverter.h"
#include "Point.h"
#include "Arc.h"
#include "Point.h"
using namespace QuickTSP;
using namespace std;

#define DEBUG_LEVEL -1
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
    
    
    set<Arc> arcs;                                      //Store the arcs of the resulting graph
    map<long int, vector<Curve> > curvesByCorridor;     //Stores all curves from or to a corridor
    
    vector<Block> blocks = this->warehouse.getBlocks(); //Get the list of warehouse blocks  
    map<string, Block> blocksByName;
    vector<ExpeditionPoint> expeditionPoints = this->warehouse.getExpeditionPoints();
    
	for(int i= 0; i<(int) blocks.size(); i++){
        blocksByName[blocks[i].getName()] = blocks[i];
	}
	
	
    //This loop creates a subgraph of the final graph to each block. These blocks will be connected by block exits in
    //second loop
    for(int i= 0; i<(int) blocks.size(); i++){

		vector<Shelf> shelves = blocks[i].getShelves();
        vector<Corridor> corridors = blocks[i].getCorridors();
        vector<Curve> curves = blocks[i].getCurves();        
		
        //Create a subgraph for each shelf in the blocks. These subgraphs will be connected through the corridors in a
        //second part of the algorithm
        for(int j = 0; j < (int) shelves.size(); j++){
            
			//cout<<"Working on shelf: "<<shelves[j].getId()<<endl;
            vector<Cell> cells = shelves[j].getCells();
            vector<vector<string> > cellPositions;      //It stores each vertex in its line and row at cell
                                                        //respective shelf. You should verify if it is updated anytime
														// the current shelf changes
            vector<Corridor> adjacentCorridors = getAdjacentCorridors(corridors, shelves[j]);
            
			//The width and length of each cell is relevant to define cells coordinates 
            double cellWidth = shelves[j].getCellWidth();
            double cellLenght = shelves[j].getCellLength();
            int numRows = shelves[j].getNumRows();
            int numColumns = shelves[j].getNumColumns();
			
            cellPositions.resize(shelves[j].getNumRows()+1);
            for(int k=1; k < (int) numRows+1; k++)
                cellPositions[k].resize(numColumns+1);
        
			//cout<<"Connecting cells"<<endl;
            for(int k=0; k < (int) cells.size(); k++)
                connectCellLevels(cells[k], cellPositions, arcs);
        
            //Connects cells with corridors and internal nodes with border nodes in a shelf.
            for(int k=1; k< (int) numRows+1; k++){
                for(int l=1; l< (int) numColumns+1;l++){
                    //It should verify if the matrix position stores a valid cell
                    Vertex vertex = vertexByCode[cellPositions[k][l]];
                    
                    //There are nodes that have not direct contact with a corridor (internal nodes)
                    //In this case, we define that the cell is accessible by the closest corridor
                    // (in terms of number of cells)
                    if(numRows > 2 && numColumns > 2)
                        connectInternalNode(vertex, arcs, numRows, numColumns,k,l,cellWidth, cellLenght, cellPositions);
                }
            }
		
            //cout<<"Connecting shelf to corridor"<<endl;
            connectShelvesToCorridor(shelves[j], adjacentCorridors,cellPositions, numRows, numColumns, arcs);
			
        }
       
		
		//cout<<"Splitting corridors\n";
        //This will allow to create arcs in the interior of corridors
        for(int j = 0; j<(int)curves.size(); j++)
            splitCorridorByCurves(curves[j], curvesByCorridor);
        
		//cout<<"Creating arcs on corridors\n"; 
        for(int j=0; j< (int)corridors.size(); j++)
            createArcsOnCorridors(corridors[j],arcs);
        
        connectCorridorsByCurves(curves,arcs);
        
    }
	
	for(int i= 0; i<(int) blocks.size(); i++){
		vector<BlockExit> blockExits = blocks[i].getExits(); 
		for(int j=0; j<(int) blockExits.size();j++)
			connectBlockExits(blockExits[j], arcs, blocksByName);
	}
		
    
    for(unsigned int i=0; i<expeditionPoints.size();i++)
        connectExpeditionPoint(expeditionPoints[i], arcs, blocksByName);

    this->graph = Graph::convertArcsToGraph(arcs);
	cout<<"Conversion finished:\nNumber of arcs: \t"<<arcs.size()<<endl;
}

/**
 * This functions connects the levels inside a cell in order to have a path between any pair of divisions of a cell.
 * For now it is supposed that all cells divisions are on vertical
 */
void WarehouseToGraphConverter::connectCellLevels(Cell cell,vector<vector<string> > &cellPositions,set<Arc> &arcs){
    
    int numLevels = cell.getLevels();
    
    if(numLevels == 1){
		#if DEBUG_LEVEL > 0
			cout<<"Connecting cell: \t"<<cell.getCode()<<" which has a single level\n";
		#endif 
        Vertex firstLevel = * (new Vertex( cell.getCode(), "UniqueLevelCell"));
        initiliazeCellFirstLevel(firstLevelVertexes, cellPositions, firstLevel, cell);
        
    }else if(numLevels > 0){
        Vertex firstLevel(cell.getCode()+"_L1", "FirstLevelCell");
        initiliazeCellFirstLevel(firstLevelVertexes, cellPositions, firstLevel, cell);
        
		#if DEBUG_LEVEL > 0
			cout<<"Connecting cell levels of cell "<<cell.getCode()<<" which has " <<numLevels<<" levels\n";
		#endif
		
		
        //Create the vertexes to represent the higher levels and the arcs to connect them
        for(int l=1; l< (int) numLevels; l++){
            Vertex vertex( cell.getCode()+"L"+to_string(l) , "UniqueLevelCell");
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
void WarehouseToGraphConverter::connectShelvesToCorridor(const Shelf &shelf,const vector<Corridor>& adjacentCorridor,
                                                       const StringMatrix &cellPositions, int numRows,int numColumns,set<Arc> &arcs ){
    double cellWidth = shelf.getCellWidth();
    double cellLength = shelf.getCellLength();
    
    Corridor *corridorUp= NULL;
    Corridor *corridorDown=NULL;
    Corridor *corridorLeft=NULL;
    Corridor *corridorRight=NULL;
    
	InitializeAdjacentCorridors(corridorUp, corridorDown, corridorLeft, corridorRight, adjacentCorridor, shelf); 
	
	#if DEBUG_LEVEL > 0
		if(corridorUp == corridorLeft && corridorRight == corridorDown && corridorLeft == corridorRight)
			cout<<"There is a problem with adjacent corridors\t" << shelf.getId()<<" "<<shelf.getNumRows()<<" "<<shelf.getNumColumns() <<endl; 
	#endif
	
    //=====================     Vertical or squared shelf   ================================
    if(numColumns <= numRows){
		
        for(int k=1; k< (int) numRows+1; k++){
            //First column
            if(corridorLeft != NULL){
                connectSingleCellToSingleCorridor(shelf, corridorLeft, arcs,   cellPositions[k][1], "LEFT", k, 1);
            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors (a column to the rigth)
				if(numColumns > 1){
                    
					pair<Vertex, Vertex> extremes = createCellAndCorridorVertexes(cellPositions[k][1], cellPositions[k][2]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellWidth, arcs); 
				}
            }
            
            //Last column
            if(corridorRight != NULL){
                connectSingleCellToSingleCorridor(shelf, corridorRight, arcs,  cellPositions[k][numColumns], "RIGHT", k, numColumns);
            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors (one column to right)
				if(numColumns > 1){
					pair<Vertex, Vertex> extremes = createCellAndCorridorVertexes(cellPositions[k][numColumns], cellPositions[k][numColumns-1]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellWidth, arcs); 
				}
            }
        }       
    }
    
    //=======================   Horizontal or squared shelf ==============================
    if(numRows <= numColumns){
        for(int k=1; k< (int) numColumns+1; k++){
            //First row
            if(corridorUp != NULL){
                connectSingleCellToSingleCorridor(shelf, corridorUp, arcs, cellPositions[numRows][k], "UP", numRows, k);
            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
				if(shelf.getNumRows() > 1){
					pair<Vertex, Vertex> extremes = createCellAndCorridorVertexes(cellPositions[numRows][k], cellPositions[numRows-1][k]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellLength, arcs);
				}				
            }
            
            //Last row
            if(corridorDown != NULL){
                connectSingleCellToSingleCorridor(shelf, corridorDown, arcs,  cellPositions[1][k], "DOWN", 1, k);
            }else{
                //The cell is considered an internal cell thus it will be connected with its neighbors
				if(shelf.getNumRows() > 1){
					pair<Vertex, Vertex> extremes = createCellAndCorridorVertexes(cellPositions[1][k], cellPositions[2][k]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellLength, arcs); 
				}
            }
        }
    }
}


/**
 * 
 * 
 */
void WarehouseToGraphConverter::connectSingleCellToSingleCorridor(const Shelf &shelf,Corridor * corridor, set<Arc> &arcs, 
                                                               string cellName, string position,int row, int column){

    double coordX=0, coordY=0; 
    double cellWidth = shelf.getCellWidth();
    double cellLength = shelf.getCellLength();
    
    if(position == "LEFT"){
        coordX = shelf.getBottomLeftCoords().first + 0.5*cellWidth;
        coordY = shelf.getBottomLeftCoords().second + cellLength*(row-1) + 0.5*cellLength;
    }else if(position == "RIGHT"){
        coordX = shelf.getBottomLeftCoords().first+ cellWidth*(column -1) + 0.5*cellWidth;
        coordY = shelf.getBottomLeftCoords().second + cellLength*(row-1) + 0.5*cellLength;
    }else if(position == "UP"){
        coordX = shelf.getBottomLeftCoords().first+ cellWidth*(column-1) + 0.5*cellWidth;
        coordY = shelf.getBottomLeftCoords().second + 0.5*cellLength;
    }else if(position == "DOWN"){
        coordX = shelf.getBottomLeftCoords().first+ cellWidth*(column-1) + 0.5*cellWidth;
        coordY = shelf.getBottomLeftCoords().second + cellLength*(row - 1) + 0.5*cellLength;
    }
                    
    pair<Vertex,Vertex> extremes = createCellAndCorridorVertexes(corridor, make_pair(coordX, coordY), cellName, position);
    double corridorCoordX = corridor->getBeginCoords().first;
    double corridorCoordY = corridor->getBeginCoords().second;
				
    if(position == "LEFT" || position == "RIGHT"){
        createArcsCellToCorridor(extremes.first, extremes.second, fabs(corridorCoordX-coordX), arcs);
    }else if(position == "UP" || position == "DOWN"){
        createArcsCellToCorridor(extremes.first, extremes.second, fabs(corridorCoordY-coordY), arcs);
    }
}


/**
 * 
 * 
 */
pair<Vertex, Vertex> WarehouseToGraphConverter::createCellAndCorridorVertexes(string cellNameA, string cellNameB){

    Vertex vertexCell(cellNameA, "CellVertex");
    Vertex cellOther;
    if(vertexByCode.find(cellNameB) != vertexByCode.end())
        cellOther = vertexByCode[cellNameB];
    else{
        cellOther.setLabel(cellNameB); 
        cellOther.setType("CellVertex"); 
    }

    return make_pair(vertexCell, cellOther);				

}

/**
 * 
 * 
 */
pair<Vertex, Vertex> WarehouseToGraphConverter::createCellAndCorridorVertexes(const Corridor *corridor, pair<double,double> coords, 
                                                                              string cellName, string position){

    double corridorCoordX = corridor->getBeginCoords().first;
    double corridorCoordY = corridor->getBeginCoords().second;

    bool horizontal = (position == "LEFT" || position == "RIGHT");
    Point corridorPoint("", ( horizontal ? corridorCoordX :  coords.first) , (horizontal ?  coords.second : corridorCoordY ),0);
    
    pointsByCorridor[corridor->getId()].push_back(corridorPoint);
    
    Vertex vertexCell(cellName, "CellVertex");
    Vertex vertexCorridor("corridor_"+to_string(corridor->getId())+"_cell_"+cellName,"PickVertex");
    vertexByCode[vertexCell.getLabel()] = vertexCell;
    vertexByCode[vertexCorridor.getLabel()] = vertexCorridor;


    return make_pair(vertexCell, vertexCorridor); 
}





/**
 *
 *
 **/
void WarehouseToGraphConverter::InitializeAdjacentCorridors(Corridor *up,Corridor * down,Corridor * left,Corridor * right,
															const vector<Corridor>& adjacents,Shelf shelf){
	
	up = down = right = left = NULL;
	
	//Search and identify the adjacent corridors
    for(unsigned int i=0;i< adjacents.size();i++)
        if(adjacents[i].getDirection() == VERTICAL && adjacents[i].getBeginCoords().first < shelf.getBottomLeftCoordX())
            left =  new Corridor(adjacents[i]);
    
    for(unsigned int i=0;i< adjacents.size();i++)
        if(adjacents[i].getDirection() == VERTICAL && adjacents[i].getBeginCoords().first > shelf.getBottomLeftCoordX())
            right =  new Corridor(adjacents[i]);
    
    for(unsigned int i=0;i<adjacents.size();i++)
        if(adjacents[i].getDirection() == HORIZONTAL && adjacents[i].getBeginCoords().second > shelf.getBottomLeftCoordY())
            up =  new Corridor(adjacents[i]);
    
    for(unsigned int i=0;i<adjacents.size();i++)
        if(adjacents[i].getDirection() == HORIZONTAL && adjacents[i].getBeginCoords().second < shelf.getBottomLeftCoordY())
            down =  new Corridor(adjacents[i]);
}

/**
 *
 *
 */
void WarehouseToGraphConverter::createArcsCellToCorridor(Vertex vertexCell, Vertex vertexCorridor,double value, set<Arc> &arcs){	
	
	Arc leaving("arc("+ vertexCell.getLabel() + ","+ vertexCorridor.getLabel() +")", value, vertexCell, vertexCorridor);
	Arc picking("arc("+ vertexCorridor.getLabel() + ","+ vertexCell.getLabel() +")", value, vertexCorridor, vertexCell);
	arcs.insert(leaving);
	arcs.insert(picking);
}



/**
 * Connect two corridors using one curve. This curve 
 */
void WarehouseToGraphConverter::connectCorridorsByCurves(vector<Curve> curves, set<Arc> &arcs){
	//cout<<"Curves size: \n"<<curves.size()<<endl; 
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
void WarehouseToGraphConverter::createArcsOnCorridors(const Corridor corridor, set<Arc> &arcs){
    
	
    long int id = corridor.getId();
	Point beginCorridor("beginCorridor_"+to_string(id), corridor.getBeginCoords().first, corridor.getBeginCoords().second, 0); 
	Point endCorridor("endCorridor_"+to_string(id), corridor.getEndCoords().first, corridor.getEndCoords().second,0); 
    
	vector<Point> points = pointsByCorridor[id];
	points.push_back(beginCorridor);
	points.push_back(endCorridor);
	
	vector<Point> processedPoints = Point::removeDuplicates(points); 
    
	corridor.orderCorridorPoints(processedPoints);
    
	Vertex first("corridor_"+to_string(id)+"_point_0", "CorridorCurvePoint");
	vertexByCode[first.getLabel()] = first;
	
	for(int k=1; k<(int)processedPoints.size(); k++){
		Vertex second("corridor_"+to_string(id)+"_point_"+to_string(k), "CorridorCurvePoint");
		vertexByCode[second.getLabel()] = second;
		
		double distance = sqrt(pow(processedPoints[k].getCoordX()-processedPoints[k-1].getCoordX(),2)+
							   pow(processedPoints[k].getCoordY()-processedPoints[k-1].getCoordY(),2));
		
		arcs.insert(Arc("arc_"+first.getLabel()+ "_"+second.getLabel(),distance,first, second));
		
		if(corridor.getSense() == BOTH)
			arcs.insert(Arc("arc_"+second.getLabel()+ "_"+first.getLabel(), distance, second, first));
		first = second;
	}
}



/**
 *  Auxiliary function. It gets all the curve points in a corridor. These points will be used in other function
 *  to generate new vertexes and arcs.
 */
void WarehouseToGraphConverter::splitCorridorByCurves(const Curve &curve, map<long int, vector<Curve> > &curvesByCorridor){
    
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
    if(!any_of(points.begin(), points.end(),[&curveEndingPoint](const Point &b){
                 return fabs(curveEndingPoint.getCoordX() - b.getCoordX()) < MIN_DIFF &&
                        fabs(curveEndingPoint.getCoordY() - b.getCoordY()) < MIN_DIFF;
           })){
            pointsByCorridor[end].push_back(curveEndingPoint);
        }
}


/**
 *  Auxiliary function. Connects two internal cells in a shelf (cells that have just other cells around).
 *  Internal cells in vertical shelves should be connected their left and right neighbors (cells closer to a corridor)
 *  Internal cells in horizontal shelves should be connected with their up and down neighbors (cells closer to a corridor)
 */
void WarehouseToGraphConverter::connectInternalNode(Vertex vertex, set<Arc> &arcs, const int numRows, const int numColumns,
                                                    const int k,const int l,double width, double length,
                                                    const vector<vector<string> > cellPositions){
    
    if(numRows < numColumns){              // Horizontal shelf
        
        if(k > 1){
            string sUp = cellPositions[k-1][l];
            connectVertexesByTwoArcs(vertex,sUp, arcs, length);
        }
        
        if(k<numRows){
            string sDown = cellPositions[k+1][l];
            connectVertexesByTwoArcs(vertex,sDown, arcs, length);
        }
    }else if(numRows > numColumns){         // Vertical shelf
        
        if(l > 1){
            const string sLeft = cellPositions[k][l-1];
            connectVertexesByTwoArcs(vertex,sLeft, arcs, width);
        }
        
        if(l < numColumns){
            const string sRight = cellPositions[k][l+1];
            connectVertexesByTwoArcs(vertex,sRight, arcs, width);
        }
        
    }else if(numRows == numColumns){        // Squared shelf
        
        if(k > 1){
            string sUp = cellPositions[k-1][l];
            connectVertexesByTwoArcs(vertex,sUp, arcs, length);
        }
        
        if(k<numRows){
            string sDown = cellPositions[k+1][l];
            connectVertexesByTwoArcs(vertex,sDown, arcs, length);
        }
        
        if(l > 1){
            const string sLeft = cellPositions[k][l-1];
            connectVertexesByTwoArcs(vertex,sLeft, arcs, width);
        }
        
        if(l < numColumns){
            const string sRight = cellPositions[k][l+1];
            connectVertexesByTwoArcs(vertex,sRight, arcs, width);
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
 *  Here is also considered that there is always a corridor between two shelves. All validations to check if 
 *  it is true are done before. 
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
            if(corridors[i].getDirection() ==  VERTICAL && doCorridorTranverse(corridors[i], shelf)){
                
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
            if(corridors[i].getDirection() == HORIZONTAL && doCorridorTranverse(corridors[i], shelf)){
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
    
    if(numColumns < numLines && corridor.getDirection() == VERTICAL){
        return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second;
    }else if(numColumns > numLines && corridor.getDirection() == HORIZONTAL){
        return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first;
    }else if(numColumns == numLines){
        if(corridor.getDirection() == HORIZONTAL)
            return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first;
        if(corridor.getDirection() == VERTICAL)
            return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second;
    }
    return false;
    
}

/**
 *  Auxiliar function to connect a two vertex between them by two arcs (in opposite senses).
 */
void WarehouseToGraphConverter::connectVertexesByTwoArcs(Vertex & first, string second,set<Arc> &arcs, double size){
    
    Vertex secondVertex = vertexByCode[second];
    
    //Two arcs (in opposite senses) to each adjacent cell
    arcs.insert(Arc("arc_"+first.getLabel()+"_"+secondVertex.getLabel(), size, first, secondVertex));
    arcs.insert(Arc("arc_"+secondVertex.getLabel()+"_"+first.getLabel(), size, secondVertex, first));
}


/**
 *   Auxiliary function to fill the vertexByCode, firstLevelVertex and cellPositions Structure
 *	 Those structures are very important to assure the connection between shelves, cells and corridors
 */
void WarehouseToGraphConverter::initiliazeCellFirstLevel(vector<Vertex> & firstLevelVertexes,vector<vector<string> > &cellPositions,
                                                         Vertex firstLevel, Cell cell){

                vertexByCode[firstLevel.getLabel()] =  firstLevel;				//Dictionary to a quick recovery of vertexes 
                firstLevelVertexes.push_back(firstLevel);						//This structure save all the first level vertex
																				//Why is it important? Because this vertexes will 
                                                                                //connect corridors with higher level cells
    
                int row = cell.getRow();
                int column = cell.getColumn();
    
                if(row > 0 && row <= (int)cellPositions.size())
                    if(column > 0 && column <= (int)cellPositions[row].size())
                        cellPositions[row][column] = firstLevel.getLabel();		//This structure saves the position of all first level cells
																				// Why is it important? Because these cells will be connected 
                                                                                // with corridors then it is very important to know where they are. 
}


/**
 * 
 * 
 */
void WarehouseToGraphConverter::connectExpeditionPoint(ExpeditionPoint &expeditionPoint, set<Arc> & arcs, map<string, Block> &blocksByName){
    Vertex closestVertex; 
    double minDistance = 1e20;
    double distance = 0;
    
    
    if(blocksByName.find(expeditionPoint.getBlockCode()) == blocksByName.end())
        return;

    Block block = blocksByName[expeditionPoint.getBlockCode()];
	pair<double,double> reference = expeditionPoint.getCoordinates(); 
    Point referencePoint("expeditionPoint_"+expeditionPoint.getCode(), reference.first, reference.second, 0); 
    

    for(map<Point, Vertex>::iterator it=vertexByPoint.begin(); it!= vertexByPoint.end(); it++){
        if(!block.isInBlock(it->first))
            continue;

        distance = sqrt( pow(it->first.getCoordX()-reference.first,2)+pow(it->first.getCoordY()-reference.second,2));
        if(distance< minDistance){
            minDistance = distance;
            closestVertex = it->second;
        }
    }
    cout<<minDistance<<endl;
    if(minDistance <= 1e19){
        //create arc here
        Vertex expeditionVertex("expedition_"+expeditionPoint.getCode(), "ExpeditionPointVertex",0);
        vertexByPoint[referencePoint] = expeditionVertex; 
        vertexByCode[expeditionVertex.getLabel()] = expeditionVertex; 

        Arc one("expedition_"+expeditionPoint.getCode()+"_toVertex_"+closestVertex.getLabel(), minDistance, expeditionVertex, closestVertex);
        Arc other("Vertex_"+closestVertex.getLabel()+"toExpedition_"+expeditionPoint.getCode(), minDistance, closestVertex, expeditionVertex);

        arcs.insert(one);
        arcs.insert(other);
    }
}




/**
 * 
 * 
 */
void WarehouseToGraphConverter::connectBlockExits(BlockExit &exit, set<Arc> & arcs, map<string, Block> &blocksByName){
    Vertex closestVertexA, closestVertexB; 
    double minDistanceA = 1e20;
	double minDistanceB = 1e20;
    
    double distance = 0;
    
    if(blocksByName.find(exit.getBlockAName()) == blocksByName.end())
        return;
	
    if(exit.getBlockBName() != "#_#_#" && blocksByName.find(exit.getBlockAName()) == blocksByName.end())
        return; 
	
    Block blockA = blocksByName[exit.getBlockAName()];
    Block blockB = blocksByName[exit.getBlockBName()];

    pair<double,double> reference = exit.getCoords(); 
    Point referencePoint("expeditionPoint_"+to_string(exit.getId()), reference.first, reference.second, 0); 
    
    for(map<Point, Vertex>::iterator it=vertexByPoint.begin(); it!= vertexByPoint.end(); it++){
	
        if(blockA.isInBlock(it->first)){
			distance = sqrt( pow(it->first.getCoordX()-reference.first,2)+pow(it->first.getCoordY()-reference.second,2));
			if(distance< minDistanceA){
				minDistanceA = distance;
				closestVertexA = it->second;
			}
		}
		
		if(exit.getBlockBName() != "#_#_#" && blockB.isInBlock(it->first)){
			distance = sqrt( pow(it->first.getCoordX()-reference.first,2)+pow(it->first.getCoordY()-reference.second,2));
			if(distance< minDistanceB){
				minDistanceB = distance;
				closestVertexB = it->second;
			}
		}
    }
    // cout<<minDistance<<endl;
	
	Vertex exitVertex("exit"+to_string(exit.getId()), "BlockExitVertex",0);
    if(minDistanceA <= 1e19){
        
        vertexByPoint[referencePoint] = exitVertex; 
        vertexByCode[to_string(exit.getId())] = exitVertex; 
		
        Arc one("expedition_"+exitVertex.getLabel()+"_toVertex_"+closestVertexA.getLabel(), minDistanceA, exitVertex, closestVertexA);
        Arc other("Vertex_"+closestVertexA.getLabel()+"toExpedition_"+exitVertex.getLabel(), minDistanceA, closestVertexA, exitVertex);

        arcs.insert(one);
        arcs.insert(other);
    }
    
	if(minDistanceB <= 1e19){
		vertexByPoint[referencePoint] = exitVertex; 
        vertexByCode[to_string(exit.getId())] = exitVertex; 

        Arc one("expedition_"+exitVertex.getLabel()+"_toVertex_"+closestVertexB.getLabel(), minDistanceB, exitVertex, closestVertexB);
        Arc other("Vertex_"+closestVertexB.getLabel()+"toExpedition_"+exitVertex.getLabel(), minDistanceB, closestVertexB, exitVertex);

        arcs.insert(one);
        arcs.insert(other);
	}
}