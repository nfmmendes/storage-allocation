#ifndef BLOCK_H
#define BLOCK_H

#include<iostream>
#include<cmath>
#include<ctime>
#include<map>
#include<vector>
#include<algorithm>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
#include "Curve.h"
using namespace std; 


class Block{

    private: 
        vector<Shelf> shelves;						///< Stores all shelves
		map<long int, Shelf> shelvesById;			///< Stores a map connecting a shelf id to the object
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
    
    
		Block & addShelf(Shelf &shelf); 
		Block & addExit(BlockExit &exit);
		Block & addCorridor(Corridor &corridor); 
		Block & addCurve(Curve & curve); 
		
		Block & removeShelf(Shelf &shelf); 
		Block & removeExit(BlockExit &exit);
		Block & removeCorridor(Corridor &corridor); 
		Block & removeCuver(Curve & curve); 
		
	
	
	
        string getName() const;
		double getWidth();
		double getLenght();
        vector<Shelf> getShelves();
		map<long int, Shelf> getShelvesById(); 
		
        vector<BlockExit> getExits();
        vector<Corridor> getCorridors();
        vector<Curve> getCurves();
        pair<double,double> getBottomLeftCoords();
    
        bool isInBlock(const Point &point)const;

		void setName(const string &name);

        ///Set corridors
        void setCorridors(vector<Corridor> & others);
    
        ///Set all the shelves of a block
        void setShelves(vector<Shelf > & other);
    
        void setCurves(vector<Curve> &other);
    
        //TODO: Improve this
        bool operator==(const Block &other);
		bool operator<(const Block &other)const ;
		Block & operator=(const Block &other);
		
		int getNumberOfAvailablePositions(); 
		void printBlockInformation();
};

#endif
