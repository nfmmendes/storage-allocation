#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
using namespace std; 



namespace QuickTSP{



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
}