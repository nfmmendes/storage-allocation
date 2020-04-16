#ifndef BLOCK_EXIT_H
#define BLOCK_EXIT_H

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
using namespace std;

/** 
 *  This class describes a block exit. These exits can connect one warehouse
 * to another or just to a warehouse exit. In this implementation, a exit can
 * not connect more than two blocks.
 */
class BlockExit{
    
    private:
        long int Id;
        double coordX;					///< X-coordinate of central exit point 
        double coordY;					///< Y-coordinate of central exit point  
        string blockAName; 				///< First block of exit 
        string blockBName;				///< Second block of exit. The second block can be empty if the exit goes out of warehouse
    public:
        BlockExit();
        BlockExit(const BlockExit &other);
        
        BlockExit(long int id, double coordX, double coordY, string blockA, string blockB="");
        
        long int getId();
        double getCoordX();
        double getCoordY();
        string getBlockAName();
        string getBlockBName();
        pair<double, double> getCoords();
    
        void setId(long int value);
        void setCoordX(double value);
        void setCoordY(double value);
        void setBlockAName(double value);
        void setBlockBName(double value);
    
        bool operator==(const BlockExit &other);
        bool operator!=(const BlockExit &other);
        bool operator<(const BlockExit & other) const;
		BlockExit & operator=(const BlockExit &other);
		
		void printExitInformation();
    
};

#endif
