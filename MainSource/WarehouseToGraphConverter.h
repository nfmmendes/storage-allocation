#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<memory>
#include<set>
#include "Warehouse.h"
#include "Arc.h"
#include "Cell.h"
#include "Corridor.h"
#include "Curve.h"
#include "Point.h"
#include "Graph.h"
#include "Arc.h"
using std::map;
using std::string;
using std::shared_ptr;
using std::vector;

typedef std::vector< std::vector<std::string> > StringMatrix;

namespace QuickTSP{

    class WarehouseToGraphConverter{
       
        private:
            Warehouse warehouse; 
            Graph graph;
            map<pair<Cell, int>, shared_ptr<Vertex>> vertexByCell;
            vector<Vertex> firstLevelVertexes;                  //Store the vertexes corresponding to cell first levels. We need
                                                                // it because this vertexes will be connected after in the graph
            map<const string, Vertex> vertexByCode;             //!< Stores all vertex, indexed by code
            map<const string, Vertex> vertexByCorridor;
            map<long int, vector<Point> > pointsByCorridor;   //!<Stores all points where a curve starts or finishes, divided by corridor
            map<Point, Vertex> vertexByPoint;
        
            void initializeCellFirstLevel(vector<Vertex> & ,StringMatrix &,Vertex , Cell );
            void connectInternalNode(Vertex , set<Arc> &,const int , const int ,const int ,const int , double , double ,
                                     const vector<vector<string> > );
            void connectVertexesByTwoArcs(Vertex & first, string second, set<Arc> &arcs, double size);
            vector<Corridor> getAdjacentCorridors(const vector<Corridor> & corridor, Shelf shelf);
            bool doCorridorTranverse(const Corridor &corridor,const Shelf &shelf);
            void splitCorridorByCurves(const Curve &, map<long int, vector<Curve> > &);
            void createArcsOnCorridors(const Corridor , set<Arc> &);
            void connectCorridorsByCurves(vector<Curve> curves, set<Arc> &arcs);
            void connectShelvesToCorridor(const Shelf &, const vector<Corridor>&, const StringMatrix &, int , int , set<Arc> & );
            void connectCellLevels(Cell , StringMatrix &, set<Arc> &);
			void createArcsCellToCorridor(Vertex vertexCell, Vertex vertexCorridor,double value, set<Arc> &arcs);
			void InitializeAdjacentCorridors(Corridor *&up,Corridor *& down, Corridor *& left,Corridor *& right,const vector<Corridor>& adjacents, const Shelf& shelf);
            pair<Vertex, Vertex> createCellAndCorridorVertexes( const Corridor *corridor, const pair<double,double> &coords, const string &cellName, const string& position);
            void connectSingleCellToSingleCorridor(const Shelf &shelf, Corridor * corridor,set<Arc> &arcs, string cellName, string position,int row, int column);
            pair<Vertex, Vertex> getInternalAndExternalCellsVertexes(string cellNameA, string cellNameB);
            void connectExpeditionPoint(const ExpeditionPoint &expedition, set<Arc> &arcs, map<string, Block> &blocksByName);
            void connectBlockExits(const BlockExit &exit, set<Arc> & arcs, map<string, Block> &blocksByName);

        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(const Warehouse &warehouse);
            void generateGraph(); 
            const Graph & getGraph() const;
            const Warehouse & getWarehouse() const;
            map<pair<Cell,int>, shared_ptr<Vertex>>& getVertexByCell();
		
			//Vertex types 
			const static string BLOCK_EXIT_VERTEX;
			const static string CORRIDOR_CURVE_POINT;
			const static string EXPEDITION_POINT_VERTEX;
			const static string FIRST_LEVEL_CELL;
			const static string PICK_VERTEX;
			const static string UNIQUE_LEVEL_CELL;
			const static string UPPER_LEVEL_CELL;

    }; 
}
