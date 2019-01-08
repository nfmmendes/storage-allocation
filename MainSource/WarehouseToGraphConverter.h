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
            void initiliazeCellFirstLevel(map<string, Vertex> &, vector<Vertex> &,
                                          map<string, pair<int,int> > &, Vertex , Cell);
        
        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(WarehouseToGraphConverter & other);
            WarehouseToGraphConverter(Warehouse &warehouse);
            void generateGraph(); 
        
    }; 
}
