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
        
        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(WarehouseToGraphConverter & other){
            
            }
            void getResultingGraph(Graph &graph); 
        
    }; 
}
