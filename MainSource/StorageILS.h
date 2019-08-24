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
#include "StorageAllocationSolution.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "DistanceMatrix.h";
#include "Warehouse.h"
#include "Cell.h"
#include "Block.h"
#include "Shelf.h"
#include "Graph.h"
#include "Vertex.h"
#include "Arc.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
using namespace std; 

#define MAX_ITERATIONS_WITHOUT_IMPROVEMENT 10
#define MAX_PERTUBATIONS 20

/**
 * It create neighbors by swapping the position of two products stored in fhe same shelf. 
 * The list of products that can have their positions changed is given by the heuristic that is
 * using the neighborhood structure
 */
class InsideShelfSwap : NeighborhoodStructure{

    private: 
        unsigned int numberOfNeighbors;     // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                 //The algorithm use random functions, but it can not be 100% random because
                                        //two consecutive runs of the same instance must have the same result due to
                                        // the hardness of a company accepts a random behavior of the algorithm. It
                                        // also helps to debug the code, as the bug can be reproduced several times 
                                        // until its cause be discovered
		Shelf & shelf; 
    public:
        InsideShelfSwap();
        InsideShelfSwap(AbstractSolution *initial, unsigned int numNeigh, 
                        int randomSeed, Shelf & shelf):base(initial);
        virtual void setStartSolution(AbstractSolution *) const;
        virtual AbstractSolution * getStartSolution() const {return this->startSolution; }
        virtual vector<AbstractSolution *> createNeighbors();
		
		void setShelf(Shelf & shelf) { this->shelf = shelf;} 
        void setRandomSeed(int seet){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }

};

/**
 * In create neighbors by swapping the position of two products stored in the same block.
 * The list of producs that can have their position changed is given by the heuristic that is using the
 * neighborhood structure
 */
class InsideBlockSwap: NeighborhoodStructure{


    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        vector<int> interchangeableProducts; 
		Block &block; 
    public:
        InsideBlockSwap();
        InsideBlockSwap(StorageAllocationSolution *initial, int numNeigh,  int randomSeed, Block &block):base(initial);
        virtual void setStartSolution(AbstractSolution *) const;
        virtual AbstractSolution * getStartSolution() const { return this->startSolution; }

        virtual vector<AbstractSolution *> createNeighbors();

        void setInterchangeableProducts(vector<int> prods) {this->interchageableProducts = products; }
        void setRandomSeed(int seet){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        vector<int> getInterchangeableProducts() {return this->interchageableProducts; }
        int getRandomSeed(){ return this->randomSeed; }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }
};

/**
 * It creates neighbors by swapping the position of the most frequent products. The list of 
 * the most frequent products is given 
 */
class MostFrequentSwap : NeighborhoodStructure{

    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        vector<int> interchangeableProducts; 

    public:
        MostFrequentSwap();
        MostFrequentSwap(StorageAllocation *initial, int numNeigh, 
                         int randomSeed, vector<int> &products):base(initial)
        virtual void setStartSolution(AbstractSolution *) const;
        virtual AbstractSolution * getStartSolution() const; 
        virtual vector<AbstractSolution *> createNeighbors();


        void setInterchangeableProducts(vector<int> prods) {this->interchageableProducts = products; }
        void setRandomSeed(int seet){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        vector<int> getInterchangeableProducts() {return this->interchageableProducts; }
        int getRandomSeed(){ return this->randomSeed; }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }
};


/**
 * Perturbates a solution by using one of these procedures
 *  1. Pertubate most frequent products
 *  2. Pertubate less frequent products
 *  3. Mix all the products
 */
class StorageAllocationPertubation : NeighborhoodStructure {

    private: 
        int strategy;
        int randomSeed;                     //The algorithm use random functions, but it can not be 100% random because
                                            //two consecutive runs of the same instance must have the same result due to
                                            // the hardness of a company accepts a random behavior of the algorithm. It
                                            // also helps to debug the code, as the bug can be reproduced several times 
                                            // until its cause be discovered
        int numOfPertubationMoves; 
    public:
        virtual void setStartSolution(AbstractSolution *) const;
        virtual AbstractSolution * getStartSolution() const; 
        virtual vector<AbstractSolution *> createNeighbors();

        void setInterchangeableProducts(vector<int> prods) {this->interchageableProducts = products; }
        void setRandomSeed(int seet){ this->randomSeed = seed; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        vector<int> getInterchangeableProducts() {return this->interchageableProducts; }
        int getRandomSeed(){ return this->randomSeed; }
        unsigned int getNumberOfNeighbors(){ return this->numberOfNeighbors; }s
};

/**
 * 
 */
class StorageILS : Heuristic{

    private: 
        DistanceMatrix *distanceMatrix; 
        Graph *graph;
        Warehouse *warehouse; 
        vector<NeighborhoodStructure> neighborhoodStructures;
        virtual bool StopCriteriaReached();
        StorageAllocationSolution * ExecutePertubation(StorageAllocationSolution *);
        StorageAllocationSolution * CreateInitialSolution();
        virtual void EvaluateSolution(AbstractSolution * solution); 
        int numPertubations; 
        int numIterationsWithoutImprovement; 

    public:
        StorageILS();
        StorageILS(StorageILS &other);
        StorageILS(DistanceMatrix *distances, Graph *graph, Warehouse *warehouse);
        virtual AbstractSolution * Execute(); 

};



#endif /* ILS_hpp */
