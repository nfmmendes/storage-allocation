#ifndef OPTIMIZATION_PARAMETERS_H
#define OPTIMIZATION_PARAMETERS_H

/**
 *	Class with constant data used as parameters of algorithm 
 */
class OptimizationParameters{
	
	public:
		static const double A_THRESHOLD_CLASS = 30;
		static const double B_THRESHOLD_CLASS = 60;
		static const int MAX_PERTUBATIONS = 20;
		static const int MAX_ITERATIONS_WITHOUT_IMPROVEMENT = 10;
		static const int ALL_PERMUTATIONS_TSP_THRESHOLD = 4;
		static const int INSERTION_TSP_THRESHOLD = 10;
}

#endif