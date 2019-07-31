#include<iostream>
#include<vector> 
#include<map>
#include<string>
#include<cstdlib>
#include<utility> 
using namespace std; 





template <class Graph, class DistanceMatrix>
class DistanceMatrixCalculator{

        
    public:
        DistanceMatrixCalculator();
        DistanceMatrixCalculator(DistanceMatrixCalculator &other);
        virtual DistanceMatrix calculateMatrixDistance(Graph &graph)=0;
     

}; 



