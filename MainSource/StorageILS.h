//
//  ILS.hpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//  In a future version of this code, the neighborhood structure classes must be put in a separated file
//

#ifndef ILS_h
#define ILS_h

#include "StorageAllocationSolution.h"
#include "StorageSolutionEvaluator.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "DistanceMatrix.h"
#include "OptimizationParameters.h"
#include "Warehouse.h"
#include "Cell.h"
#include "Block.h"
#include "Shelf.h"
#include "OptimizationConstraints.h"
#include "Vertex.h"
#include "Arc.h"
#include "ABCAnalysis.h"
#include "Order.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
using namespace std; 


/**
 * It create neighbors by swapping the position of two products stored in fhe same shelf. 
 * The list of products that can have their positions changed is given by the heuristic that is
 * using the neighborhood structure
 */
class InsideShelfSwap :public NeighborhoodStructure{

    private: 
        unsigned int numberOfNeighbors;     // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                 //The algorithm use random functions, but it can not be 100% random because
                                        //two consecutive runs of the same instance must have the same result due to
                                        // the hardness of a company accepts a random behavior of the algorithm. It
                                        // also helps to debug the code, as the bug can be reproduced several times 
                                        // until its cause be discovered
		Shelf shelf; 
        map<Position, Product> shelfAllocations; 
        
    public:
        InsideShelfSwap();
        ~InsideShelfSwap();
        InsideShelfSwap(AbstractSolution *initial, unsigned int numNeigh, int randomSeed, Shelf & shelf);
        AbstractSolution * getStartSolution() const {return this->startSolution; }
        vector<AbstractSolution *> createNeighbors();
        void setShelfAllocations(map<Position,Product> &value){ shelfAllocations = value; }
		
		void setShelf(Shelf & shelf) { this->shelf = shelf;} 
        void setRandomSeed(int seed){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }

};

/**
 * In create neighbors by swapping the position of two products stored in the same block.
 * The list of producs that can have their position changed is given by the heuristic that is using the
 * neighborhood structure
 */
class InsideBlockSwap:public NeighborhoodStructure{


    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
		Block block; 
		map<Position, Product> blockAllocations;

    public:
        InsideBlockSwap();
        ~InsideBlockSwap();
        InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh,  int randomSeed, Block &block);
        AbstractSolution * getStartSolution() const { return this->startSolution; }

        vector<AbstractSolution *> createNeighbors();

        void setRandomSeed(int seed){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        int getRandomSeed(){ return this->randomSeed; }
        void setBlock(Block &other){ this->block = other; }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }
};

/**
 * It creates neighbors by swapping the position of the most frequent products. The list of 
 * the most frequent products is given 
 */
class MostFrequentSwap :public NeighborhoodStructure{

    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        vector<Product> interchangeableProducts; 

    public:
        MostFrequentSwap();
        ~MostFrequentSwap();
        MostFrequentSwap(StorageAllocationSolution *initial, int numNeigh, int randomSeed, vector<Product> &products);
        AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();


        void setInterchangeableProducts(vector<Product> prods) {this->interchangeableProducts = prods; }
        void setRandomSeed(int seed){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        vector<Product> getInterchangeableProducts() {return this->interchangeableProducts; }
        int getRandomSeed(){ return this->randomSeed; srand(this->randomSeed); }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }
};



/**
 * It creates neighbors by swapping the position of the most frequent products. The list of 
 * the most frequent products is given 
 */
class IsolatedFamilySwap :public NeighborhoodStructure{

    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        vector<Product> interchangeableProducts;
    public:
        IsolatedFamilySwap();
        ~IsolatedFamilySwap();
        IsolatedFamilySwap(StorageAllocationSolution *initial, int numNeigh, int randomSeed, vector<Product> &products);
        AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();

        void setRandomSeed(int seed){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        int getRandomSeed(){ return this->randomSeed; srand(this->randomSeed); }
        void setInterchangeableProducts(vector<Product> prods) {this->interchangeableProducts = prods; }
        vector<Product> getInterchangeableProducts() { return this->interchangeableProducts; }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }
};



/**
 * Perturbates a solution by using one of these procedures
 *  1. Pertubate most frequent products
 *  2. Pertubate less frequent products
 *  3. Mix all the products
 */
class StorageAllocationPertubation :public NeighborhoodStructure {

    private: 
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        int numOfPertubationMoves; 
		vector<Product> interchangeableProducts; 
    public:
        AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();
        StorageAllocationPertubation(){}
        ~StorageAllocationPertubation(){}

        void setRandomSeed(int seed){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numOfPertubationMoves = val; }
        int getRandomSeed(){ return this->randomSeed; }
        void setInterchangeableProducts(vector<Product> prods) {this->interchangeableProducts = prods; }
        vector<Product> getInterchangeableProducts() { return this->interchangeableProducts; }
        unsigned int getNumberOfNeighbors(){ return this->numOfPertubationMoves; }
};

/**
 * 
 */
class StorageILS :public Heuristic{

    private:
		OptimizationConstraints constraints;
		vector<Product> products; 
        DistanceMatrix<Vertex> *distanceMatrix; 
		map<Position, Vertex> vertexByCell;
        Warehouse *warehouse; 
		vector<Order> orders; 
        vector<NeighborhoodStructure *> neighborhoodStructures;
        int numIterationsWithoutImprovement; 
        vector<string> neighborhoodType;
        map<Product, char> productClasses; 
		
        bool StopCriteriaReached();
        StorageAllocationSolution * ExecutePertubation(StorageAllocationSolution *);
        StorageAllocationSolution * CreateInitialSolution();
        void EvaluateSolution(AbstractSolution * solution); 
		void InitializeNeighborhoods();
        AbstractSolution * SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure,int randomSeed);
        AbstractSolution * SwapInsideBlockLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed);
        AbstractSolution * SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed);
        AbstractSolution * RunPerturbation(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure);
        map<Product, char> getProductABCClasses();
    public:
        StorageILS();
        StorageILS(StorageILS &other);
		StorageILS(vector<Product> & prods, Warehouse &wh,DistanceMatrix<Vertex> &distMatrix,
				   map<Position, Vertex> vertexByCell,vector<Order> &orders, OptimizationConstraints &cons);
        AbstractSolution * Execute(); 

};



#endif /* ILS_hpp */
