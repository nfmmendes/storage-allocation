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
#include "Solution.h"

class VND {
    
    public:
        VND();
        VND(Warehouse warehouse, vector<Order> orders, vector<ProductAllocationProhibitions> prohibitions, vector<Parameter> parameters);
        VND(const VND & other);
        void run();
        Solution &getSolution();
        double getSolutionValue();
    
    
    private:
        Warehouse warehouse;
        vector<Order> orders;
        vector<ProductAllocationProhibitions> prohibitions;
        vector<Parameter> parameters;
        Solution bestSolution;
        double bestSolutionValue;
        void pertubation(Solution &solution);
        void firstLocalSearch(Solution &solution);
        void secondLocalSearch(Solution &solution);
        void thirdLocalSearch(Solution &solution);
        bool stopCriteria();
        bool pertubationCriteria();
    
    
};

#endif /* VND_hpp */
