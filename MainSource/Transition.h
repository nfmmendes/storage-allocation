namespace QuickTSP{

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
    
 }