//
//  VND.hpp
//  
//
//  Created by Nilson Mendes on 07/01/2019.
//

#ifndef VND_hpp
#define VND_hpp

#include <stdio.h>
#include <vector>
#include "Order.h"
#include "ProductAllocationProhibition.h"
#include "Parameter.h"
#include "AbstractSolution.h"

class VND {
    
    public:
        VND();
        VND(Warehouse warehouse, vector<Order> orders, vector<ProductAllocationProhibitions> prohibitions, vector<Parameter> parameters);
        VND(const VND & other);
        void run();
        AbstractSolution *getSolution();
        double getSolutionValue();
    
    
    private:
        Warehouse warehouse;
        vector<Order> orders;
        vector<ProductAllocationProhibitions> prohibitions;
        vector<Parameter> parameters;
        AbstractSolution * bestSolution;
        double bestSolutionValue;
        void pertubation(AbstractSolution *solution);
        void firstLocalSearch(AbstractSolution *solution);
        void secondLocalSearch(AbstractSolution *solution);
        void thirdLocalSearch(AbstractSolution *solution);
        bool stopCriteria();
        bool pertubationCriteria();
    
    
};

#endif /* VND_hpp */
