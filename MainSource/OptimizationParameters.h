#ifndef OPTIMIZATION_PARAMETERS_H
#define OPTIMIZATION_PARAMETERS_H

/**
 *	Class with constant data used as parameters of algorithm 
 */
class OptimizationParameters{
	
	public:
		static const int A_THRESHOLD_CLASS = 30;
		static const int B_THRESHOLD_CLASS = 60;
		static const int MAX_PERTUBATIONS = 20;
		static const int MAX_ITERATIONS_WITHOUT_IMPROVEMENT=10;
		static const int ALL_PERMUTATIONS_TSP_THRESHOLD=4;
		static const int INSERTION_TSP_THRESHOLD=10;
		static const int NON_ALLOCATED_PRODUCT_PENALTY = 10000;
		static const int WEAK_ALLOCATION_PROHIBITION_PENALTY = 8000;
		static const int WEAK_ISOLATED_FAMILY_ALLOCATION_PENALTY = 5000;
};

#endif