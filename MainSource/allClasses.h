#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 



namespace QuickTSP{


    //Class to represent a geometrical point in a 3D space
    class Point {
        private: 
            string label;
            double coordX; 
            double coordY;
            double coordZ; 
            
        public:
            Point();
            
            //Full constructor
            //Null values are not allowed
            Point(string &label, double &coordX, double &coordY, double & coordZ){
            
                if(label == null || coordX == null || coordY == null || coordZ == null)
                    throw("Error"); 
            
                this->label = label;
                this->coordX = coordX;
                this->coordY = coordY; 
                this->coordZ = coordZ; 
            }
            
            //Copy constructor
            //Null values are not allowed  
            Point(Point &point){
                if(point == null)
                    throw("Error"); 
            
                this->label = point.getLabel();
                this->coordX = point.getCoordX();
                this->coordY = point.getCoordY();
                this->coordZ = point.getCoordZ(); 
            }
            
            //Set the value of X coordinate 
            void setCoordX(double value){
                this->CoordX = value;
            }
            
            //Set the value of the Y coordinate
            void setCoordY(double value){
                this->coordY = value;
            }
            
            //Set the value of the Z coordinate
            void setCoordZ(double value){
                this->coordZ = value;
            }
            
            void setPoint(Point &point){
                this->label = point.label;
                this->coordX = point.coordX;
                this->coordY = point.coordY;
                this->coordZ = point.coordZ;
            }
            
            double getCoordX(){ return coordX;}
            double getCoordY(){ return coordY; }
            double getCoordZ(){ return coordZ; }
            string getLabel() { return label; }
            
        
    };


    class Vertex{
        
        private:
            string label;
            string type;
            double value;
        
        public:
            Vertex();
            Vertex(Vertex &other){
                this->label = other.label;
                this->type = other.type;
                this->value = other.value; 
            }
            Vertex(string label, string Type, string value = 0);
       
            void setLabel(string value){ this->label = value; }
            void setType(string value) { this->label = value; }
            void setValue(string value) { this->label = value; } 
        
        
        
    }

    //Class to represent a vertex in a graph
    class Arc{
        
        private:
            string label;
            double value; 
            Vertex &beginVertex;
            Vertex &endVertex; 
        
        public:
            Arc();
            Arc(Arc &arc){
                this->label = arc.getLabel();
                this->value = arc.getValue(); 
                this->beginVertex = arc.getBeginVertex();
                this->endVertex = arc.getEndVertex();
            }
            
            Arc(string label, double value, Vertex &begin, Vertex &end){
                this->label = label;
                this->value = value; 
                this->beginVertex = begin;
                this->endVertex= endVertex;
            }
        
            void setLabel(string label){
                this->label = value;
            }
            
            
            void setValue(double value){
                this->value = value; 
            }
            
            void setBeginVertex(Vertex& vertex){
                this->beginVertex = vertex;
                
            }
            
            void setEndVertex(Vertex& vertex){
                this->endVertex = vertex; 
            }
            
            
            string getLabel() { return label; }
            double getValue() { return value; }
            Vertex getBeginVertex() { return beginVertex; }
            Vertex endVertex() {return endVertex; }
            
            
            
    };

    class Line{
        private: 
            Point &startPoint;
            Point &slope;
            
        public:
            Line();
            Line(){
                Line & line;
            }
            Line(Point &pointA, Point &pointB){
                this->slope = Point(pointA.coordX - pointB.coordX,pointB.coordY - pointB.coordY,pointC.coordZ - pointC.coordZ);
                this->startPoint = Point(pointA);  
            }
    };


    class Graph{
        private:
            vector<Vertex&> vertexes; 
            vector<Arc&> arcs; 
            string name; 
        public:
            Graph();
            
            Graph(Graph &graph){
                this->name = graph.name;
                
                for(int i=0;i<graph.vertexes.size();i++)
                    this->vertexes.push_back(Vertex(graph.vertexes[i]));
                for(int i=0;i<graph.arcs.size();i++)
                    this->arcs.push_back(Arc(graph.arcs[i]));
            }
            
           Graph(vector<Vertex &> vertexes, vector<Arc&> arcs, string name){
                this->name = name;
                
                for(int i=0;i<graph.vertexes.size();i++)
                    this->vertexes.push_back(Vertex(vertexes[i]));
                for(int i=0;i<graph.arcs.size();i++)
                    this->arcs.push_back(Arc(arcs[i]));
           }
            
    }

    class HananGraph : Graph{
        
        private:
            vector<Line &> lines
            vector<Line &> columns; 
            vector<Point &> points; 
            vector<Vertex &> buildVertexes;
            map<Vertex &, pair<int,int> > vertexCoordinate; 
            
        public:
            HananGraph();
            HananGraph(vector<Point &>points, Graph & graph);
            
            vector<Vertex &> getBuildVertexes(){
                return buildVertex;
            }
            
            vector<Vertex &> getVertexCoordinate(Vertex &v){
                return 0; 
            }
            
        
    }


    class Transition{
        
        private:
            Vertex& beginVertex;
            Vertex& endVertex;
            HananGraph &graph;

        public:  
            Transition();
            Transition(Transition &transition);
            Transition(Vertex &beginVertex, Vertex& endVertex, HananGraph &graph){
                this->beginVertex = beginVertex;
                this->endVertex = endVertex;
                this->graph = graph; 
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            void setHananGraph(HananGraph &value) { this->HananGraph = value; } 
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; } 
            HananGraph & getGraph() { return this->HananGraph; } 
        
    };

    class PathUnity{
        
        private: 
            Vertex& beginVertex;
            Vertex& endVertex;
            Transition &Transition;  

        public:
            PathUnity();
            PathUnity(PathUnity &other);
            PathUnity(Vertex &begin, Vertex &end, Transition &transition(){
                this->beginVertex = begin;
                this->endVertex = end;
                this->Transition = transition; 
            }
            
            void setBeginVertex(Vertex &value) { this->beginVertex = value; }
            void setEndVertex(Vertex &value){ this->endVertex = value; }
            void setHananTransition(Transition &value) { this->Transition = value; } 
            
            Vertex & getBeginVertex() { return this->beginVertex; }
            Vertex & getEndVertex() { return this->endVertex; } 
            HananGraph & getGraph() { return this->Transition; } 
            
        
    };



    class State {

        

        public: 
            //Data
            vector<Vertex&> vertexParity;
            map<Vertex &, int> vertexComponent; 
            vector<Vertex&> vertexComponent;
            HananGraph<int> &graph; 
        
            State();
            State(vector<int> parity, vector<int> component, HananGraph &graph){
                this->vertexParity = parity;
                this->vertexComponent = component;
                this->graph = graph; 
            }
            
            void addTransition(Transition &t){
                //Verify the components of state 
            }
            

    };

    
    class Product{
        
        private:
            long int ID;
            string name;
            string type;
            
        public:
            Product();
            Product(Product & other){
                this->name = other.name;
                this->type = other.type;
            }
            
            Product(string name, string type){
                
            }
            
        
    };

    class Warehouse{
        private:
            string name;
            vector<Block> blocks;
            vector<pair<Product, Cell> > productAllocation;
        public:
            Warehouse();
            Warehouse(Warehouse &other);
            void ReadWarehouseData(string fileName);
            void WriteWarehouseData(string fileName);
            void InsertNewBlock(Block &b);
            
            void RemoveBlock(Block &b);
            void RemoveBlock(int i);
            void SetProductAllocation(pair<Product, Cell> & productionAllocation); 
            void AddProductAllocation(pair<Product, Cell> & productionAllocation);
            void RemoveProductAllocation(Cell &cell); 
            void RemoveProductAllocation(int i); 
            
            string GetName(string &name);
            vector<Block &> GetBlocks(); 
            vector<pair<Product, Cell> > GetProductAllocation();
            
            void SetName(string &name); 
            void SetBlocks(vector<Block &> blocks);
            void SetProductAllocation(vector<pair<Product, Cell> > & productAllocation); 
            
            
        
    }


    class WarehouseToGraphConverter{
       
        private:
            Warehouse warehouse; 
            Graph graph; 
        
        public:
            WarehouseToGraphConverter();
            WarehouseToGraphConverter(WarehouseToGraphConverter &other);
            void getResultingGraph(Graph &graph); 
        
    }; 

    
    class QuickTSP{
        private: 
            HananGraph graph;
            vector<PathUnity&> solution
        public:
            QuickTSP();
            QuickTSP(QuickTSP &other);
            QuickTSP(HananGraph &graph); 
            
            void setHananGraph(HananGraph &graph){ this->graph = graph;}
            HananGraph getHananGraph()           { return this->graph; }
            Vector<PathUnity &> getSolution()    {return this->solution; } 
            
            void Run(){
                
            }
    }

}

int main(){
    
    
    
    
}