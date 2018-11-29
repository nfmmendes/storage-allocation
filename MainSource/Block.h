#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>
#include<utility>
#include "Shelf.h"
#include "BlockExit.h"
using namespace std; 


class Block{

    private: 
        vector<Shelf> shelves;
        vector<BlockExit> exits; 
        string name; 
        pair<double,double> bottomLeftCoords;
        
    public:
        Block();
        Block(Block &other);
        Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY);
        
        bool hasValidConfiguration(){
            bool isValid = true;
            for(unsigned int i = 0; i <exits.size();i++)
                if(exits[i].getCoordX() < bottomLeftCoords.first || exits[i].getCoordY() < bottomLeftCoords.second){
                    isValid = false; 
                    break;
                }
            
            for(unsigned int i = 0; i< shelves.size(); i++){
                if(shelves[i].getBottomLeftCoordX() < bottomLeftCoords.first || shelves[i].getBottomLeftCoordY() < bottomLeftCoords.second){
                    isValid = false; 
                    break;
                }
            }
            
            return isValid; 
        }
        
        
        string getName() { return name; }
        vector<Shelf> getShelves() {return shelves; }
        vector<BlockExit> getExits() {return exits; }
        pair<double,double> getBottomLeftCoords() {return bottomLeftCoords; }
        
        ///Add a exit in a block (if it was not inserted a exit with same Id yet)
        void addExit(BlockExit & other) { 
            if( find(exits.begin(), exits.end(), other) != exits.end())
                exits.push_back(other);
        }
        
        /// Removes the exit with id equals to Id in the block of exits 
        void removeExitWithId(long int Id){
            
        }
        
        /// Removes the exit with the index i in the block list of exits
        void removeExit(int index){
            
        }
};