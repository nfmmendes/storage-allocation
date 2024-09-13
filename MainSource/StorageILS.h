#pragma once 

#include "StorageAllocationSolution.h"
#include "Heuristic.h"
#include "NeighborhoodStructure.h"
#include "Cell.h"
#include "Block.h"
#include "Shelf.h"
#include "Vertex.h"
#include "Arc.h"
#include "Order.h"
#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cmath>
#include <set>
#include <map> 
using std::vector;
using std::map;
using std::pair;

class OptimizationConstrains;
class StorageAllocationEvaluator;
class Warehouse;


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
		Shelf shelf; 
        OptimizationConstraints *constraints;
        map<Position, Product> shelfAllocations; 
        bool isValidSwap(const Product &first, const Product &second, const MapAllocation &allocations);

    public:
        InsideShelfSwap();
        ~InsideShelfSwap();
        InsideShelfSwap(AbstractSolution *initial, OptimizationConstraints * constr, Shelf & shelf);
        const AbstractSolution * getStartSolution() const { return this->startSolution; }
        vector<AbstractSolution *> createNeighbors();
        void setShelfAllocations(map<Position,Product> &value){ shelfAllocations = value; }
		void setOptimizationConstraints(OptimizationConstraints * cons){ constraints = cons; }
        const OptimizationConstraints * getOptimizationConstraints()const { return constraints; }
		void setShelf(const Shelf & shelf) { this->shelf = shelf;} 
        
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
};

/**
 * In create neighbors by swapping the position of two products stored in the same block.
 * The list of producs that can have their position changed is given by the heuristic that is using the
 * neighborhood structure
 */
class InsideBlockSwap : public NeighborhoodStructure{

    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
		Block block; 
        OptimizationConstraints *constraints;
		map<Position, Product> blockAllocations;
        bool isValidSwap(const Product &first, const Product &second, MapAllocation &allocations); 
    public:
        InsideBlockSwap();
        ~InsideBlockSwap();
        InsideBlockSwap(const StorageAllocationSolution *initial, OptimizationConstraints * constr, const Block &block);
        const AbstractSolution * getStartSolution() const { return this->startSolution; }

        vector<AbstractSolution *> createNeighbors();

        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        void setOptimizationConstraints(OptimizationConstraints * cons){ constraints = cons; }
        OptimizationConstraints * getOptimizationConstraints(){ return constraints; }
        void setBlock(const Block &other){ this->block = other; }
        unsigned int getNumberOfNeighbors() const { return this->numberOfNeighbors; }
};

/**
 * It creates neighbors by swapping the position of the most frequent products. The list of 
 * the most frequent products is given 
 */
class MostFrequentSwap : public NeighborhoodStructure{

    private:
        int numberOfNeighbors;              // Max number of neighbors that will be created in this class when the 
                                            // function createNeighbors is called. The real number of neighbors can be
                                            // lower due to impossibilities in creating more solutions
        OptimizationConstraints *constraints;
        vector<Product> interchangeableProducts; 
        bool isValidSwap(const Product &first, const Product &second, MapAllocation &allocations);
    public:
        MostFrequentSwap();
        ~MostFrequentSwap();
        MostFrequentSwap(StorageAllocationSolution *initial, OptimizationConstraints *constr , const vector<Product> &products);
        const AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();

        void setInterchangeableProducts(const vector<Product> &prods) { this->interchangeableProducts = prods; }
        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        void setOptimizationConstraints(OptimizationConstraints * cons){ constraints = cons; }
        OptimizationConstraints * getOptimizationConstraints(){ return constraints; }
        vector<Product> getInterchangeableProducts() { return this->interchangeableProducts; }
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
        vector<Product> interchangeableProducts;
        OptimizationConstraints *constraints; 
    public:
        IsolatedFamilySwap();
        ~IsolatedFamilySwap();
        IsolatedFamilySwap(StorageAllocationSolution *initial, OptimizationConstraints *constr,  vector<Product> &products);
        const AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();

        void setNumberOfNeighbors(unsigned int val){ this->numberOfNeighbors = val; }
        void setOptimizationConstraints(OptimizationConstraints * cons){ constraints = cons; }
        OptimizationConstraints * getOptimizationConstraints(){ return constraints; }
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
class StorageAllocationPertubation : public NeighborhoodStructure {

    private: 
        int numOfPertubationMoves; 
		vector<Product> interchangeableProducts; 
        OptimizationConstraints * constraints; 
        set<string> forbiddenAllocationProducts; 
        bool isValidSwap(const Product &first, const Product &second, MapAllocation &allocations);
    public:
        const AbstractSolution * getStartSolution() const; 
        vector<AbstractSolution *> createNeighbors();
        StorageAllocationPertubation(OptimizationConstraints *constr){ constraints = constr; }
        ~StorageAllocationPertubation(){}

        void setNumberOfNeighbors(unsigned int val){ this->numOfPertubationMoves = val; }
        void setOptimizationConstraints(OptimizationConstraints * cons){ constraints = cons; }
        OptimizationConstraints * getOptimizationConstraints(){ return constraints; }
        void setInterchangeableProducts(vector<Product> prods) {this->interchangeableProducts = prods; }
        vector<Product> getInterchangeableProducts() { return this->interchangeableProducts; }
        unsigned int getNumberOfNeighbors(){ return this->numOfPertubationMoves; }
};

/**
 * @brief Class <c>StorageILS</c> is used to execute a ILS based heuristic to
 * improve a storage allocation.
 */
class StorageILS : public Heuristic{
    
    public:
        /**
         * @brief Constructor
         */
        StorageILS();

        /**
         * @brief Copy constructor.
         * @param other The object to be copied.
         */
        StorageILS(StorageILS &other);

        /**
		 * @brief Constructor.
		 * @param prods The list of products.
		 * @param wh The warehouse in which the products are allocated. 
		 * @param distMatrix The warehouse distance matrix.
		 * @param vertexByCell A map from the warehouse positions to the warehouse graph vertexes.
		 * @param orders The product orders. 
		 * @param cons The optimization constraints. 
         */
		StorageILS(const vector<Product> & prods, Warehouse &wh, const DistanceMatrix<Vertex>* distMatrix,
				   map<Position, Vertex>& vertexByCell, const vector<Order> &orders, const OptimizationConstraints &cons);
        
        /**
         * @brief Run the heuristic.
         * @return A solution. 
         */
        AbstractSolution * Execute(); 

    private:
		OptimizationConstraints constraints;
		vector<Product> products; 
        const DistanceMatrix<Vertex> *distanceMatrix; 
		map<Position, Vertex> vertexByCell;
        Warehouse *warehouse; 
		vector<Order> orders; 
        vector<NeighborhoodStructure *> neighborhoodStructures;
        unsigned int numIterationsWithoutImprovement; 
        vector<string> neighborhoodType;
        map<Product, char> productClasses; 
		
        /**
         * @brief Get if the stop criteria has been reached. 
         * @return True if the stop criteria has been reached, false otherwise. 
         */
        bool StopCriteriaReached();

        /**
         * @brief Create an initial solution. 
         * @return A solution. 
         */
        StorageAllocationSolution * CreateInitialSolution();

        /**
         * @brief Evaluate a solution solution.
         * @param solution The solution to be evaluated.
         */ 
        void EvaluateSolution(AbstractSolution * solution); 

        /**
		 * @brief Initialize the set of neighborhoods to be used in the heuristic. 
         */
		void InitializeNeighborhoods();

        /**
         * @brief Perform a local search inside a shelf. 
         * @param currentSolution The solution that will be used as the center of the search. 
         * @param neighborhoodStructure The neighborhood structure to be used in the search. 
         * @param randomSeed The random seed of the search. 
         * @return A new solution. 
         */
        AbstractSolution * SwapInsideShelfLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure,int randomSeed);
        
        /**
         * @brief Perform a local search inside a block.
         * @param currentSolution The solution that will be used as the center of the search. 
         * @param neighborhoodStructure The neighborhood structure to be used in the search. 
         * @param randomSeed The random seed of the search. 
         * @return A new solution. 
         */
        AbstractSolution * SwapInsideBlockLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed);
        
        /**
         * @brief Perform a local search considering only the most frequent products. 
         * @param currentSolution The solution that will be used as the center of the search. 
         * @param neighborhoodStructure The neighborhood structure to be used in the search. 
         * @param randomSeed The random seed of the search. 
         * @return A new solution.
         */ 
        AbstractSolution * SwapMostFrequentLocalSearch(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure, int randomSeed);
        
        /**
         * @brief Perform a pertubation in the given solution.
         * @param currentSolution The solution to be pertubated. 
         * @param neighborhoodStructure The neighborhood structure to be used in the pertubation. 
         * @return A new solution. 
         */
        AbstractSolution * RunPerturbation(AbstractSolution *currentSolution, NeighborhoodStructure * neighborhoodStructure);
        
        /**
         * @brief Get a map from products to ABC frequence classes.
         * @return A map from products to ABC frequence classes.
         */
        const map<Product, char> getProductABCClasses();
};
