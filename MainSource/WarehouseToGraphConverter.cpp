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
#include "Arc.h"
using namespace QuickTSP;
using std::to_string;
using std::make_pair;
using std::make_shared;

#define DEBUG_LEVEL -1
#define MIN_DIFF 0.000001

const string WarehouseToGraphConverter::BLOCK_EXIT_VERTEX = "BlockExitVertex";
const string WarehouseToGraphConverter::CORRIDOR_CURVE_POINT  = "CorridorCurvePoint";
const string WarehouseToGraphConverter::EXPEDITION_POINT_VERTEX = "ExpeditionPointVertex";
const string WarehouseToGraphConverter::FIRST_LEVEL_CELL = "FirstLevelCell";
const string WarehouseToGraphConverter::PICK_VERTEX = "PickVertex";
const string WarehouseToGraphConverter::UNIQUE_LEVEL_CELL = "UniqueLevelCell";
const string WarehouseToGraphConverter::UPPER_LEVEL_CELL = "UpperLevelCell";

WarehouseToGraphConverter::WarehouseToGraphConverter(){
    
}

/**
 *  Copy constructor
 */
WarehouseToGraphConverter::WarehouseToGraphConverter(WarehouseToGraphConverter & other){
    warehouse = Warehouse(other.warehouse);
    graph = Graph(other.graph);
}

/**
 *  Constructor. It receaves a warehouse that will be used to create the converted graph
 */
WarehouseToGraphConverter::WarehouseToGraphConverter(const Warehouse &warehouse){
    this->warehouse = warehouse;
}

/**
 *	This is the main function of the class. From this function all the other functions
 *  used on the convertion process will be called and the user does not need to do anything else
 */
void WarehouseToGraphConverter::generateGraph(){
    
    set<Arc> arcs;                                      //Store the arcs of the resulting graph
    map<long int, vector<Curve> > curvesByCorridor;     //Stores all curves from or to a corridor
    
    const auto& blocks { this->warehouse.getBlocks() }; //Get the list of warehouse blocks  
    const auto& expeditionPoints { this->warehouse.getExpeditionPoints() };
    map<string, Block> blocksByName;
    
	for(int i= 0; i<(int) blocks.size(); i++){
        blocksByName[blocks[i].getName()] = blocks[i];
	}

    //This loop creates a subgraph of the final graph to each block. These blocks will be connected by block exits in
    //second loop
    for(const auto& block : blocks){
	
		const auto& shelves = block.getShelves();
        const auto& corridors = block.getCorridors();
        const auto& curves = block.getCurves();        
        //Create a subgraph for each shelf in the blocks. These subgraphs will be connected through the corridors in a
        //second part of the algorithm
        for(const auto &shelf : shelves){
            
            const auto& cells { shelf.getCells() };
            const auto& adjacentCorridors { getAdjacentCorridors(corridors, shelf) };
            //The width and length of each cell is relevant to define cells coordinates 
            double cellWidth = shelf.getCellWidth();
            double cellLenght = shelf.getCellLength();
            int numRows = shelf.getNumRows();
            int numColumns = shelf.getNumColumns();


             //It stores each vertex in its line and row at cell respective shelf. You should verify if it is 
             // updated anytime the current shelf changes
            vector<vector<string> > cellPositions;     
            cellPositions.resize(shelf.getNumRows()+1);
            for(int k=1; k < (int) numRows+1; k++)
                cellPositions[k].resize(numColumns+1);

            for(int k=0; k < (int) cells.size(); k++)
                connectCellLevels(cells[k], cellPositions, arcs);
			
			//// FILL VERTEX BY CELL
        
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
		
            connectShelvesToCorridor(shelf, adjacentCorridors,cellPositions, numRows, numColumns, arcs);
        }
	
        //This will allow to create arcs in the interior of corridors
        for(const auto& curve : curves)
            splitCorridorByCurves(curve, curvesByCorridor);
	
        for(const auto& corridor : corridors)
            createArcsOnCorridors(corridor,arcs);
        connectCorridorsByCurves(curves,arcs);
    }
	
	//Connect the block exits to the rest of the graph. It reduntant to connect
	// block exits that goes to the extern part of the the warehouse, but we do it anyway
	// It is important to remember that block exits does not belongs exclusivelly to one block
	// We will consider here (and other parts of code) that the exit belongs to only one block (blockA) for 
	// simplicity, but if it is needed this can be changed 
	for(const auto& block : blocks){
		vector<BlockExit> blockExits = block.getExits(); 
		for(const auto& blockExit : blockExits)
			connectBlockExits(blockExit, arcs, blocksByName);
	}
	
    // The expedition points need to be inside a block. In this code, we does not consider cases where the products
	// are transported to a extern part of the warehouse 
    for(unsigned int i=0; i<expeditionPoints.size();i++)
        connectExpeditionPoint(expeditionPoints[i], arcs, blocksByName);
	
	// All the conversion process is done to construct arcs. Obviously that to have arcs we need vertexes, but as 
	// the adjacence matrix is very sparse we prefer to use a list of arcs representation 
    this->graph = Graph::convertArcsToGraph(arcs);
	
	//this->graph.print();
}

/**
 * This functions connects the levels inside a cell in order to have a path between any pair of divisions of a cell.
 * For now it is supposed that all cells divisions are on vertical
 */
void WarehouseToGraphConverter::connectCellLevels(Cell cell,vector<vector<string> > &cellPositions,set<Arc> &arcs){
    
    auto numLevels { cell.getLevels() };
    
    if(numLevels == 1){
		#if DEBUG_LEVEL > 0
			cout<<"Connecting cell: \t"<<cell.getCode()<<" which has a single level\n";
		#endif 
        Vertex firstLevel(cell.getCode(), UNIQUE_LEVEL_CELL);	/// All the vertexes created based on cell position have 
		vertexByCell[make_pair(cell,1)] = make_shared<Vertex>(firstLevel);
		
		/// the world "Cell" in their type name
        initializeCellFirstLevel(firstLevelVertexes, cellPositions, firstLevel, cell);
		
    } else if(numLevels > 1){
        Vertex firstLevel(cell.getCode()+"_L_1", FIRST_LEVEL_CELL);

        initializeCellFirstLevel(firstLevelVertexes, cellPositions, firstLevel, cell);
		vertexByCell[make_pair(cell,1)] = make_shared<Vertex>(firstLevel);

		#if DEBUG_LEVEL > 0
			cout<<"Connecting cell levels of cell "<<cell.getCode()<<" which has " <<numLevels<<" levels\n";
		#endif
		
        //Create the vertexes to represent the higher levels and the arcs to connect them
        for(int l=2; l<= (int) numLevels; l++){
            Vertex vertex( cell.getCode()+"_L_"+to_string(l) , UPPER_LEVEL_CELL);		/// To the graph is irrelevant if a vertex
																						/// can not connect directly with each other 
            vertexByCode[vertex.getLabel()] = vertex;
            vertexByCell[make_pair(cell,l)] = make_shared<Vertex>(vertex);
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
 * This function creates a connection between a shelf and a corridor. The connection is not done with the shelf itself, but with the
 * cells in it. Although it looks the same, it don't, because a direct connection between a shelf and a corridor could indicate the
 * existence of a shelf "entrance" that does not exist to the cases that we analyse 
 */
void WarehouseToGraphConverter::connectShelvesToCorridor(const Shelf &shelf,const vector<Corridor>& adjacentCorridor,
                                                       const StringMatrix &cellPositions, int numRows,int numColumns,set<Arc> &arcs ){
    auto cellWidth { shelf.getCellWidth() };
    auto cellLength { shelf.getCellLength() };
    
    Corridor *corridorUp= nullptr;
    Corridor *corridorDown= nullptr;
    Corridor *corridorLeft= nullptr;
    Corridor *corridorRight= nullptr;
    
	// Look for the shelf closest corridor. If it is a horizontal corridor we look for the closest horizontal corridors (one above and other 
	// bellow). If it is a vertical shelf we pick one vertex on the left and other in the left 
	InitializeAdjacentCorridors(corridorUp,corridorDown, corridorLeft, corridorRight, adjacentCorridor, shelf); 

	#if DEBUG_LEVEL > 0
		if(corridorUp == corridorLeft && corridorRight == corridorDown && corridorLeft == corridorRight)
			cout<<"There is a problem with adjacent corridors\t" << shelf.getId()<<" "<<shelf.getNumRows()<<" "<<shelf.getNumColumns() <<endl; 
	#endif
	
	//Brutto pezzo di codice
	//Comunque...
	// The way that a shelf is connected to the corridors is different according to the format of the shelf
	// A vertical shelf has more lines than columns  	while 		A horizontal shelf has more columns that lines 
	//			**	|	***  |											******
	//			**	|	***	 |											******
	//			**	|	***  |											------------
	//			**	|	***	 |											*********
	//			**	|--------|											*********
	// Considering the star blocks as shelf and the lines as corridors, is evident that vertical corridors should be connected 
	// with vertical shelves and horizontal corridors with horizontal shelves. In case where we have squared shelves we do both.
	// A vertical shelf can be connected by a corridor in its left or in its right (or both). 
	
	//=====================     Vertical or squared shelf   ================================
	if(numColumns <= numRows){
		
		for(int k=1; k< (int) numRows+1; k++){
			//First column
			if(corridorLeft != NULL){
				connectSingleCellToSingleCorridor(shelf, corridorLeft, arcs,   cellPositions[k][1], "LEFT", k, 1);
			}else{
				//The cell is considered an internal cell thus it will be connected with its neighbors (a column to the rigth)
				if(numColumns > 1){
					pair<Vertex, Vertex> extremes = getInternalAndExternalCellsVertexes(cellPositions[k][1], cellPositions[k][2]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellWidth, arcs); 
				}
			}
			
			//Last column
			if(corridorRight != NULL){
				connectSingleCellToSingleCorridor(shelf, corridorRight, arcs,  cellPositions[k][numColumns], "RIGHT", k, numColumns);
			}else{
				//The cell is considered an internal cell thus it will be connected with its neighbors (one column to right)
				if(numColumns > 1){
					auto extremes = getInternalAndExternalCellsVertexes(cellPositions[k][numColumns], cellPositions[k][numColumns-1]);
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
					auto extremes = getInternalAndExternalCellsVertexes(cellPositions[numRows][k], cellPositions[numRows-1][k]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellLength, arcs);
				}				
			}
			
			//Last row
			if(corridorDown != NULL){
				connectSingleCellToSingleCorridor(shelf, corridorDown, arcs,  cellPositions[1][k], "DOWN", 1, k);
			}else{
				//The cell is considered an internal cell thus it will be connected with its neighbors
				if(shelf.getNumRows() > 1){
					auto extremes = getInternalAndExternalCellsVertexes(cellPositions[1][k], cellPositions[2][k]);
					createArcsCellToCorridor(extremes.first, extremes.second, cellLength, arcs); 
				}
			}
		}
	}
}


/**
 * This function connects a cell (of a given shelf) to a corridor. The position parameter indicate the corridor position 
 * relative to the shelf. To calculate the position of the cell and consequently the position of the vertex we consider the 
 * cell central point, and to do it we need to know in which row and column the cell is, as its size and the shelf. 
 * The arc will receave as value its length. 
 */
void WarehouseToGraphConverter::connectSingleCellToSingleCorridor(const Shelf &shelf,Corridor * corridor, set<Arc> &arcs, 
                                                               string cellName, string position,int row, int column){

    auto coordX { 0.0 };
    auto coordY { 0.0 }; 
    auto cellWidth { shelf.getCellWidth() } ;
    auto cellLength { shelf.getCellLength() };
    
    if(position == "LEFT" || position == "RIGHT"){
        coordX = corridor->getBeginCoords().first;
        coordY = shelf.getBottomLeftCoords().second + cellLength*(row-1) + 0.5*cellLength;
    }else if(position == "UP" || position == "DOWN"){
		coordX = shelf.getBottomLeftCoords().first+ cellWidth*(column-1) + 0.5*cellWidth;
        coordY = corridor->getBeginCoords().second; 
    }
                    
    const auto& extremes { createCellAndCorridorVertexes(corridor, make_pair(coordX, coordY), cellName, position) };
    const auto corridorCoordX { shelf.getBottomLeftCoords().first+ cellWidth*(column-1) + 0.5*cellWidth };
    const auto corridorCoordY { shelf.getBottomLeftCoords().second + cellLength*(row-1) + 0.5*cellLength };

    if(position == "LEFT" || position == "RIGHT"){
        createArcsCellToCorridor(extremes.first, extremes.second, fabs(corridorCoordX-coordX), arcs);
    }else if(position == "UP" || position == "DOWN"){
        createArcsCellToCorridor(extremes.first, extremes.second, fabs(corridorCoordY-coordY), arcs);
    }
}


/**
 * Create or recover the  
 */
pair<Vertex, Vertex> WarehouseToGraphConverter::getInternalAndExternalCellsVertexes(string cellNameA, string cellNameB){

	Vertex vertexCell(cellNameA, "CellVertex");
	
	if(vertexByCode.find(cellNameA) != vertexByCode.end())
		vertexCell = vertexByCode[cellNameA];
    
	Vertex cellOther;
    if(vertexByCode.find(cellNameB) != vertexByCode.end()){
        cellOther = vertexByCode[cellNameB];
    } else {
        cellOther.setLabel(cellNameB); 
        cellOther.setType("CellVertex"); 
    }

    return make_pair(vertexCell, cellOther);				
}

pair<Vertex, Vertex> WarehouseToGraphConverter::createCellAndCorridorVertexes(const Corridor *corridor, const pair<double,double>& coords, 
                                                                              const string& cellName, const string& position){

    const auto corridorCoordX { corridor->getBeginCoords().first };
    const auto corridorCoordY { corridor->getBeginCoords().second };

    bool horizontal = (position == "LEFT" || position == "RIGHT");
    Point corridorPoint("", ( horizontal ? corridorCoordX :  coords.first) , (horizontal ?  coords.second : corridorCoordY ),0);
    
    pointsByCorridor[corridor->getId()].push_back(corridorPoint);
    
    Vertex vertexCell(cellName, "CellVertex");
	 
	if(vertexByCode.find(cellName) != vertexByCode.end())
		vertexCell = vertexByCode[cellName]; 
	else
		vertexByCode[vertexCell.getLabel()] = vertexCell;
	
    Vertex vertexCorridor("corridor_"+to_string(corridor->getId())+"_cell_"+ cellName, PICK_VERTEX);

	
    vertexByCode[vertexCorridor.getLabel()] = vertexCorridor;
	
	if(vertexByPoint.find(corridorPoint) == vertexByPoint.end())
		vertexByPoint[corridorPoint] = vertexCorridor;
	else
		vertexCorridor = vertexByPoint[corridorPoint]; 

    return make_pair(vertexCell, vertexCorridor); 
}

void WarehouseToGraphConverter::InitializeAdjacentCorridors(Corridor *&up,Corridor *&down,Corridor *& left,Corridor *&right,
															const vector<Corridor>& adjacents, const Shelf& shelf){
	
	up = down = right = left = NULL;
	
	auto shelfWidth { shelf.getCellWidth()*shelf.getNumColumns() };
	auto shelfLength { shelf.getCellLength()*shelf.getNumRows() }; 
	
	double extremeLeft = -1e100, extremeRight = 1e100, extremeUp = 1e100, extremeDown = -1e100; 

	if(up == down){ //Just to remove a warning 
		//Search and identify the adjacent corridors
		//Get the most to the right left-corridor (so the closest corridor on left side)
		for(auto i=0;i< adjacents.size();i++){
			auto xValue { adjacents[i].getBeginCoords().first }; 
			if(adjacents[i].getDirection() == VERTICAL && xValue < shelf.getBottomLeftCoordX() && xValue > extremeLeft){
				left =  new Corridor(adjacents[i]);
				extremeLeft = xValue; 
			}
		}

		//Get the most to the left right-corridor (so the closest corridor on right side)
		for(auto i=0;i< adjacents.size();i++){
			auto xValue { adjacents[i].getBeginCoords().first }; 
			if(adjacents[i].getDirection() == VERTICAL && xValue > shelf.getBottomLeftCoordX() + shelfWidth && xValue < extremeRight){
				right =  new Corridor(adjacents[i]);
				extremeRight = xValue; 
			}
		}
		
		//Get the most to down up-corridor (so the closest corridor on up side)
		for(size_t i=0; i<adjacents.size(); i++){
			double yValue = adjacents[i].getBeginCoords().second;
    
			if(adjacents[i].getDirection() == HORIZONTAL && yValue > shelf.getBottomLeftCoordY() + shelfLength && yValue < extremeUp ){
				if(extremeUp < 1e99)
                    delete up; 
                up =  new Corridor(adjacents[i]);
				extremeUp = yValue; 
			}
		}
		
		//Get the most to the up down-corridor (so the closest corridor on down side)
		for(size_t i=0; i< adjacents.size(); i++){
			double yValue = adjacents[i].getBeginCoords().second;
    
			if(adjacents[i].getDirection() == HORIZONTAL && yValue < shelf.getBottomLeftCoordY() && yValue > extremeDown){
    
                if(extremeDown > -1e99)
                    delete down; 
				down =  new Corridor(adjacents[i]);
				extremeDown = yValue;
			}
		}
	}
}

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
	
    for(auto& curve : curves){
        // Todo: test if the points exist as vertices
        Vertex begin = vertexByPoint[curve.getStartingPoint()];
        Vertex end = vertexByPoint[curve.getEndingPoint()];
		
        double distance = curve.getStartingPoint().getDistance(curve.getEndingPoint());
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
    
	string vertexName = "corridor_"+to_string(id)+"_point_0"; 
	Vertex first(vertexName, CORRIDOR_CURVE_POINT);
	
	//Transform this if in a function
	if(vertexByPoint.find(processedPoints[0]) != vertexByPoint.end())
		first = vertexByPoint[processedPoints[0] ];
	else 
		vertexByPoint[processedPoints[0] ] = first; 
	
	vertexByCode[first.getLabel()] = first;
	
	for(int k=1; k<(int)processedPoints.size(); k++){

		Vertex second("corridor_"+to_string(id)+"_point_"+to_string(k), CORRIDOR_CURVE_POINT);
		
		if(vertexByPoint.find(processedPoints[k]) != vertexByPoint.end())
			second = vertexByPoint[processedPoints[k] ];
		else 
			vertexByPoint[processedPoints[k] ] = second; 
		
		vertexByCode[second.getLabel()] = second;
		
		
		auto distance = sqrt(pow(processedPoints[k].getCoordX()-processedPoints[k-1].getCoordX(),2)+
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
                     fabs(curveStartPoint.getCoordY() - b.getCoordY()) < MIN_DIFF && 
					 curveStartPoint.getLabel() ==  b.getLabel();
          })){
           pointsByCorridor[start].push_back(curveStartPoint);
       }

	
    //Find condition
    points = pointsByCorridor[end];
    if(!any_of(points.begin(), points.end(),[&curveEndingPoint](const Point &b){
                 return fabs(curveEndingPoint.getCoordX() - b.getCoordX()) < MIN_DIFF &&
                        fabs(curveEndingPoint.getCoordY() - b.getCoordY()) < MIN_DIFF &&
						curveEndingPoint.getLabel() ==  b.getLabel();
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
    double minDistanceLeft=1e10, minDistanceRight=1e10, minDistanceOver=1e10, minDistanceDown=1e10;

    vector<Corridor> closestAtAll;
    bool left, right, up, down=false;
    left = right = up = down;	
    
    auto& shelfCoords { shelf.getBottomLeftCoords() };
    
    //This first if looks for the closest corridors in vertical direction, if the shelf is also in this same position
    //If numColumns == numRows the two ifs will be executed
    if(numColumns <= numLines){
        for(const auto& corridor : corridors){
            if(corridor.getDirection() !=  VERTICAL || !doCorridorTranverse(corridor, shelf))
                continue;
            
            double xCoordCorridor = corridor.getBeginCoords().first;
            
            //If the corridor has a lower x coordinate so it is in the shelf left
            if(xCoordCorridor - shelfCoords.first < -1*MIN_DIFF  && shelfCoords.first - xCoordCorridor < minDistanceLeft){
                minDistanceLeft = shelfCoords.first - xCoordCorridor;
                closestAtLeft = corridor;
                left = true;
            }else if(xCoordCorridor - shelfCoords.first > MIN_DIFF && xCoordCorridor - shelfCoords.first  < minDistanceRight){
                minDistanceRight = xCoordCorridor - shelfCoords.first ;
                closestAtRight = corridor;
                right = true;
            }else if(fabs(xCoordCorridor - shelfCoords.first) > MIN_DIFF){
                //   closestAtLeft = corridors[i];
                //   left = true;
            }
            
        }
    }
    
    //This first if looks for the closest corridors in horizontal direction, if the shelf is also in this same position
    //If numColumns == numRows the two ifs will be executed
    if(numLines <= numColumns){
        for(int i=0; i<(int)corridors.size();i++){
            if(corridors[i].getDirection() != HORIZONTAL || !doCorridorTranverse(corridors[i], shelf))
                continue;
            
            double yCoordCorridor = corridors[i].getBeginCoords().second;
            
            //If the corridor has a lower x coordinate so it is in the shelf left
            if(yCoordCorridor - shelfCoords.second < -1*MIN_DIFF  && shelfCoords.second - yCoordCorridor < minDistanceDown){
                minDistanceDown = shelfCoords.second - yCoordCorridor;
                closestBellow = corridors[i];
                down = true;
            }else if(yCoordCorridor - shelfCoords.second > MIN_DIFF &&  yCoordCorridor - shelfCoords.second < minDistanceOver){
                minDistanceOver =  yCoordCorridor - shelfCoords.second;
                closestOver = corridors[i];
                up = true;
            }else if(fabs(yCoordCorridor - shelfCoords.second) < MIN_DIFF){
                //  closestOver = corridors[i];
                //  down = true;
            }
        }
    }
    
    //Eventually a shelf does not have a corridor to access their products from a size (as in case of close to wall shelves)
    //It also prevents no initialized corridors be inserted in the solutions
    if(left)
        closestAtAll.push_back(closestAtLeft); 
    if(right) 
        closestAtAll.push_back(closestAtRight);
    if(up) 
        closestAtAll.push_back(closestOver);
    if(down) 
        closestAtAll.push_back(closestBellow);
    
    return closestAtAll;
}

/**
 *  This function verify if a corridor tranverse a shelf, in other words, if a corridor starts at begining (or before)
 *  a shelf and finish at the end (or after) of a shelf
 */
bool WarehouseToGraphConverter::doCorridorTranverse(const Corridor &corridor,const Shelf &shelf){
    auto numLines { shelf.getNumRows() };
    auto numColumns {shelf.getNumColumns() };
    const auto& coordCorridor { corridor.getBeginCoords() };
    const auto& shelfCoords { shelf.getBottomLeftCoords() };
    auto len { corridor.getLength() };
	auto shelfLen { numLines*shelf.getCellLength() };
	auto shelfWidth { numLines*shelf.getCellWidth() };
    
    if(numColumns < numLines && corridor.getDirection() == VERTICAL){
		if(corridor.getSense() == BOTTOM_UP || corridor.getSense()== BOTH)
			return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second + shelfLen;
		
		return coordCorridor.second >= shelfCoords.second + shelfLen && coordCorridor.second - len <= shelfCoords.second;
    }else if(numColumns > numLines && corridor.getDirection() == HORIZONTAL){
		if(corridor.getSense() == LEFT_TO_RIGHT || corridor.getSense() == BOTH)
			return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first + shelfWidth; 
		
        return coordCorridor.first >= shelfCoords.first + shelfWidth && coordCorridor.first - len >= shelfCoords.first ;
    }else if(numColumns == numLines){
        if(corridor.getDirection() == HORIZONTAL)
            return coordCorridor.first <= shelfCoords.first && coordCorridor.first + len >= shelfCoords.first + shelfWidth;
        if(corridor.getDirection() == VERTICAL)
            return coordCorridor.second <= shelfCoords.second && coordCorridor.second + len >= shelfCoords.second + shelfLen;
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
void WarehouseToGraphConverter::initializeCellFirstLevel(vector<Vertex> & vertexes,vector<vector<string> > &cellPositions,
                                                         Vertex firstLevel, Cell cell){

	vertexByCode[firstLevel.getLabel()] =  firstLevel;				//Dictionary to a quick recovery of vertexes 
	vertexes.push_back(firstLevel);						            //This structure save all the first level vertex
																	//Why is it important? Because this vertexes will 
																	//connect corridors with higher level cells

	int row = cell.getRow();
	int column = cell.getColumn();

    //This structure saves the position of all first level cells. Why is it important? 
    // Because these cells will be connected with corridors then it is very important to know where they are. 
	if(row > 0 && row <= (int)cellPositions.size())
		if(column > 0 && column <= (int)cellPositions[row].size())
			cellPositions[row][column] = firstLevel.getLabel();
}

void WarehouseToGraphConverter::connectExpeditionPoint(const ExpeditionPoint &expeditionPoint, set<Arc> & arcs, map<string, Block> &blocksByName){
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

    if(minDistance > 1e19)
        return;

    //create arc here
    Vertex expeditionVertex("expedition_"+expeditionPoint.getCode(), EXPEDITION_POINT_VERTEX,0);
    vertexByPoint[referencePoint] = expeditionVertex; 
    vertexByCode[expeditionVertex.getLabel()] = expeditionVertex; 

    arcs.emplace("expedition_"+expeditionPoint.getCode()+"_toVertex_"+closestVertex.getLabel(), minDistance, expeditionVertex, closestVertex);
    arcs.emplace("Vertex_"+closestVertex.getLabel()+"toExpedition_"+expeditionPoint.getCode(), minDistance, closestVertex, expeditionVertex);
    
}

void WarehouseToGraphConverter::connectBlockExits(const BlockExit &exit, set<Arc> & arcs, map<string, Block> &blocksByName){
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

    const auto reference { exit.getCoords() }; 
    Point referencePoint("blockExit_"+to_string(exit.getId()), reference.first, reference.second, 0); 
    
    auto twoPointsDistance = [](const Point& a, const pair<double, double>& b){
        return sqrt( pow(a.getCoordX()-b.first,2)+pow(a.getCoordY()-b.second,2));
    };

    for(auto it : vertexByPoint){
        if(blockA.isInBlock(it.first)){
			distance = twoPointsDistance(it.first, reference); 
			if(distance< minDistanceA && distance > 1e-08){
				minDistanceA = distance;
				closestVertexA = it.second;
			}
		}
		
		if(exit.getBlockBName() != "#_#_#" && blockB.isInBlock(it.first)){
			distance = twoPointsDistance(it.first, reference);
			if(distance< minDistanceB && distance > 1e-08 ){
				minDistanceB = distance;
				closestVertexB = it.second;
			}
		}
    }

	Vertex exitVertex("exit"+to_string(exit.getId()), BLOCK_EXIT_VERTEX,0);

    auto buildExitToVertexName = [](const Vertex & exit, const Vertex& vertex)  { 
        return "exitVertex_"+exit.getLabel()+"_toVertex_"+ vertex.getLabel();
    };

    auto buildVertexToExitName = [](const Vertex & vertex, const Vertex& exit){
        return "Vertex_"+vertex.getLabel()+"_toExitVertex_" + exit.getLabel();
    };

    if(minDistanceA <= 1e19){
        vertexByPoint[referencePoint] = exitVertex; 
        vertexByCode[exitVertex.getLabel()] = exitVertex; 

        arcs.emplace(buildExitToVertexName(exitVertex, closestVertexA), minDistanceA, exitVertex, closestVertexA);
        arcs.emplace(buildVertexToExitName(closestVertexA, exitVertex), minDistanceA, closestVertexA, exitVertex);
    }
    
	if(minDistanceB <= 1e19){
		vertexByPoint[referencePoint] = exitVertex; 
        vertexByCode[exitVertex.getLabel()] = exitVertex; 

        arcs.emplace(buildExitToVertexName(exitVertex, closestVertexB), minDistanceB, exitVertex, closestVertexB);
        arcs.emplace(buildVertexToExitName(closestVertexB, exitVertex), minDistanceB, closestVertexB, exitVertex);
	}
}

const Graph & WarehouseToGraphConverter::getGraph() const {
    return graph;
}

const Warehouse & WarehouseToGraphConverter::getWarehouse() const{
    return warehouse;
}

map<pair<Cell,int>, shared_ptr<Vertex>>& WarehouseToGraphConverter::getVertexByCell(){
    return vertexByCell;
}