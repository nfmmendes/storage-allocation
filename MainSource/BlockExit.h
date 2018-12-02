#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<utility>
using namespace std;


class BlockExit{
    
    private:
        long int Id;
        double coordX;
        double coordY;
        string blockAName; 
        string blockBName;
    public:
        BlockExit();
        BlockExit(const BlockExit &other){
            this->Id = other.Id;
            this->coordX = other.coordX;
            this->coordY = other.coordY;
            this->blockAName = other.blockAName;
            this->blockBName = other.blockBName; 
        } 
        
        BlockExit(long int id, double coordX, double coordY, string blockA, string blockB=""){
            this->Id = id;
            this->coordX = coordX;
            this->coordY = coordY;
            this->blockAName = blockA;
            this->blockBName = blockB; 
        }
        
        long int getId() { return Id; }
        double getCoordX() {return coordX; }
        double getCoordY() {return coordY; }
        string getBlockAName() { return blockAName; }
        string getBlockBName() { return blockBName; }
        pair<double, double> getCoords(){ return make_pair(coordX, coordY); }
        
        
        
        void setId(long int value) { Id = value; }  //There is no Id value validation
        void setCoordX(double value) { coordX = value; }
        void setCoordY(double value) { coordY = value; }
        void setBlockAName(double value) { blockAName = value; }
        void setBlockBName(double value) { blockBName = value; }
        
        bool operator==(const BlockExit &other) { return this->Id == other.Id; }
        bool operator!=(const BlockExit &other) { return this->Id != other.Id; }

};
