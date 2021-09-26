#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<set>
#include "Warehouse.h"
#include "Arc.h"
#include "Cell.h"
#include "Corridor.h"
#include "Curve.h"
#include "Point.h"
#include "Graph.h"
#include "Arc.h"

typedef std::vector< std::vector<std::string> > StringMatrix;

namespace QuickTSP{

    class WarehouseToGraphConverter{
       
        private:
            Warehouse warehouse; 
            Graph graph;
            std::map<std::pair<Cell, int>, Vertex> vertexByCell;
            std::vector<Vertex> firstLevelVertexes;                  //Store the vertexes corresponding to cell first levels. We need
                                                                // it because this vertexes will be connected after in the graph
            std::map<const std::string, Vertex> vertexByCode;             //!< Stores all vertex, indexed by code
            std::map<const std::string, Vertex> vertexByCorridor;
            std::map<long int, vector<Point> > pointsByCorridor;   //!<Stores all points where a curve starts or finishes, divided by corridor
            std::map<Point, Vertex> vertexByPoint;
        
            void initializeCellFirstLevel(std::vector<Vertex> & ,StringMatrix &,Vertex , Cell );
            void connectInternalNode(Vertex , std::set<Arc> &,const int , const int ,const int ,const int , double , double ,
                                     const std::vector<std::vector<std::string> > );
            void connectVertexesByTwoArcs(Vertex & first, std::string second, std::set<Arc> &arcs, double size);
            std::vector<Corridor> getAdjacentCorridors(const std::vector<Corridor> & corridor, Shelf shelf);
            bool doCorridorTranverse(const Corridor &corridor,const Shelf &shelf);
            void splitCorridorByCurves(const Curve &, std::map<long int, std::vector<Curve> > &);
            void createArcsOnCorridors(const Corridor , std::set<Arc> &);
            void connectCorridorsByCurves(std::vector<Curve> curves, std::set<Arc> &arcs);
            void connectShelvesToCorridor(const Shelf &, const std::vector<Corridor>&, const StringMatrix &, int , int , std::set<Arc> & );
            void connectCellLevels(Cell , StringMatrix &, std::set<Arc> &);
			void createArcsCellToCorridor(Vertex vertexCell, Vertex vertexCorridor,double value, std::set<Arc> &arcs);
			void InitializeAdjacentCorridors(Corridor *&up,Corridor *& down, Corridor *& left,Corridor *& right,const std::vector<Corridor>& adjacents, Shelf shelf);
            std::pair<Vertex, Vertex> createCellAndCorridorVertexes( const Corridor *corridor, std::pair<double,double> coords, std::string cellName, std::string position);
            void connectSingleCellToSingleCorridor(const Shelf &shelf, Corridor * corridor,set<Arc> &arcs, string cellName, string position,int row, int column);
            pair<Vertex, Vertex> getInternalAndExternalCellsVertexes(std::string cellNameA, std::string cellNameB);
            void connectExpeditionPoint(ExpeditionPoint &expedition, std::set<Arc> &arcs, map<std::string, Block> &blocksByName);
            void connectBlockExits(BlockExit &exit, std::set<Arc> & arcs, std::map<std::string, Block> &blocksByName);

        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(WarehouseToGraphConverter & other);
            WarehouseToGraphConverter(Warehouse &warehouse);
            void generateGraph(); 
            Graph & getGraph();
            Warehouse & getWarehouse();
            std::map<std::pair<Cell,int>, Vertex> getVertexByCell();
		
			//Vertex types 
			const static std::string BLOCK_EXIT_VERTEX;
			const static std::string CORRIDOR_CURVE_POINT;
			const static std::string EXPEDITION_POINT_VERTEX;
			const static std::string FIRST_LEVEL_CELL;
			const static std::string PICK_VERTEX;
			const static std::string UNIQUE_LEVEL_CELL;
			const static std::string UPPER_LEVEL_CELL;

    }; 
}
