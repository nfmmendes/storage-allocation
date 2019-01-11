#include<iostream>
#include<string>
#include<cmath>
#include<ctime>
using namespace std; 


namespace QuickTSP{

    class WarehouseToGraphConverter{
       
        private:
            Warehouse warehouse; 
            Graph graph;
            map<Cell, Vertex> vertexes;
            void initiliazeCellFirstLevel(map<const string, Vertex> &, vector<Vertex> &,
                                          vector<vector<string> > &, Vertex , Cell);
            void connectInternalNode(Vertex ,map<const string,Vertex> &, set<Arc> &arcs,
                                    const int numRows, const int numColumns,const int k,const int l, double width, double height,
                                     const vector<vector<string> > cellPositions);
            void connectVertexesByTwoArcs(Vertex & first, string second,map<const string, Vertex> & vertexByCode,
                                          set<Arc> &arcs, double size);
            vector<Corridor> getAdjacentCorridors(const vector<Corridor> & corridor, Shelf shelf);
            bool doCorridorTranverse(const Corridor &corridor,const Shelf &shelf);
            void splitCorridorByCurves(const Curve &, map<long int, vector<Curve> > &,map<long int, vector<Point> >&);
        
        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(WarehouseToGraphConverter & other);
            WarehouseToGraphConverter(Warehouse &warehouse);
            void generateGraph(); 
        
    }; 
}
