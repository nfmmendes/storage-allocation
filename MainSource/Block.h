#pragma once

#include<iostream>
#include<map>
#include<vector>
#include "Shelf.h"
#include "BlockExit.h"
#include "Corridor.h"
#include "Point.h"
#include "Curve.h"


class Block{

    private: 
        std::vector<Shelf> shelves;						///< Stores all shelves
		std::map<long int, Shelf> shelvesById;			///< Stores a map connecting a shelf id to the object
        std::vector<BlockExit> exits;					///< Store all the exists
        std::vector<Corridor> corridors;					///< Store all the corridors 
        std::vector<Curve> curves;						///< Store all the curves that conects two corridors 
        string name; 								///< Name of block
        double length;								///< Block length 
        double width; 								///< Block width 
        std::pair<double,double> bottomLeftCoords;		///< Bottom left extremety of the block 
        
    public:
        Block();
        Block(const Block &other);
        Block(std::string blockName, double bottomLeftCoordX , double bottomLeftCoordY, double width, double lenght);
        
        bool hasValidConfiguration();
    
		Block & addShelf(Shelf &shelf); 
		Block & addExit(BlockExit &exit);
		Block & addCorridor(Corridor &corridor); 
		Block & addCurve(Curve & curve); 
		
		Block & removeShelf(Shelf &shelf); 
		Block & removeExit(BlockExit &exit);
		Block & removeCorridor(Corridor &corridor); 
		Block & removeCuver(Curve & curve); 

        std::string getName() const;
		double getWidth();
		double getLenght();
        std::vector<Shelf> & getShelves();
		std::map<long int, Shelf> getShelvesById(); 
		
        std::vector<BlockExit> getExits();
        std::vector<Corridor> getCorridors();
        std::vector<Curve> getCurves();
        std::pair<double,double> getBottomLeftCoords();
    
        bool isInBlock(const Point &point)const;

		void setName(const std::string &name);

        ///Set corridors
        void setCorridors(std::vector<Corridor> & others);
    
        ///Set all the shelves of a block
        void setShelves(std::vector<Shelf > & other);
    
        void setCurves(std::vector<Curve> &other);
    
        //TODO: Improve this
        bool operator==(const Block &other);
		bool operator<(const Block &other)const ;
		Block & operator=(const Block &other);
		
		int getNumberOfAvailablePositions(); 
		void printBlockInformation();
};
