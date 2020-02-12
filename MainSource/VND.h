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
#include "IsolatedFamily.h"

class VND {
    
    public:
        VND();
        VND(Warehouse &wh, vector<Order> &orders, vector<ProductAllocationProhibitions> &prohibitions, vector<IsolatedFamily> &isolated, vector<Parameter> &param);
        VND(const VND & other);
        void run();
        AbstractSolution *getSolution();
        double getSolutionValue();
    
    
    private:
        Warehouse warehouse;								///< Warehouse where the products will be stored 
        vector<Order> orders;								///< Orders to be used in the evaluation
        vector<ProductAllocationProhibitions> prohibitions;	///< Allocation prohibitions 
        vector<Parameter> parameters;						///< Optimization parameters 
        AbstractSolution * bestSolution;					///< Best solution found
        double bestSolutionValue;							///< Best solution value
        void pertubation(AbstractSolution *solution);		
        void firstLocalSearch(AbstractSolution *solution); 	
        void secondLocalSearch(AbstractSolution *solution);	
        void thirdLocalSearch(AbstractSolution *solution);	
        bool stopCriteria();								
        bool pertubationCriteria();
    
    
};

#endif /* VND_hpp */
