#ifndef BLOCK_H
#define BLOCK_H

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
#include "Curve.h"
using namespace std; 


class Block{

    private: 
        vector<Shelf> shelves;						///< Stores all shelves
        vector<BlockExit> exits;					///< Store all the exists
        vector<Corridor> corridors;					///< Store all the corridors 
        vector<Curve> curves;						///< Store all the curves that conects two corridors 
        string name; 								///< Name of block
        double length;								///< Block length 
        double width; 								///< Block width 
        pair<double,double> bottomLeftCoords;		///< Bottom left extremety of the block 
        
    public:
        Block();
        Block(const Block &other);
        Block(string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double lenght);
        
        bool hasValidConfiguration();
    
    
        string getName();
		double getWidth(){ return this->width;}
		double getLenght(){ return this->length;}
        vector<Shelf> getShelves();
        vector<BlockExit> getExits();
        vector<Corridor> getCorridors();
        vector<Curve> getCurves();
        pair<double,double> getBottomLeftCoords();
    
        bool isInBlock(const Point &point)const;

		void setName(const string &name);

        //Set corridors
        void setCorridors(vector<Corridor> & others);
    
        //Set all the shelves of a block
        void setShelves(vector<Shelf > & other);
    
        void setCurves(vector<Curve> &other);
    
        ///Add a exit in a block (if it was not inserted a exit with same Id yet)
        void addExit(BlockExit & other);
    
        /// Removes the exit with id equals to Id in the block of exits
        void removeExitWithId(long int Id);
    
        /// Removes the exit with the index i in the block list of exits
        void removeExit(int index);
    
        //TODO: Improve this
        bool operator==(const Block &other);
		
		void printBlockInformation();
};

#endif
