#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
using namespace std; 


class Block{

    private: 
        vector<Shelf> shelves;
        vector<BlockExit> exits;
        vector<Corridor> corridors;
        string name; 
        pair<double,double> bottomLeftCoords;
        
    public:
        Block();
        Block(const Block &other);
        Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY);
        
        bool hasValidConfiguration();
    
    
        string getName();
        vector<Shelf> getShelves();
        vector<BlockExit> getExits();
        vector<Corridor> getCorridors();
        pair<double,double> getBottomLeftCoords();
    
            //Set corridors
        void setCorridors(vector<Corridor> & others);
    
            //Set all the shelves of a block
        void setShelves(vector<Shelf > & other);
    
            ///Add a exit in a block (if it was not inserted a exit with same Id yet)
        void addExit(BlockExit & other);
    
            /// Removes the exit with id equals to Id in the block of exits
        void removeExitWithId(long int Id);
    
            /// Removes the exit with the index i in the block list of exits
        void removeExit(int index);
    
    
    
            //TODO: Improve this
        bool operator==(const Block &other);
};
