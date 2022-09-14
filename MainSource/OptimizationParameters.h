#pragma once

/**
 *	Class with constant data used as parameters of algorithm 
 */
class OptimizationParameters {
	
	public: 
		static unsigned int A_THRESHOLD_CLASS;
		static unsigned int B_THRESHOLD_CLASS;
		static unsigned int MAX_PERTUBATIONS;
		static unsigned int MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
		static unsigned int BRUTE_FORCE_TSP_THRESHOLD;
		static unsigned int INSERTION_TSP_THRESHOLD;
		static const unsigned int NON_ALLOCATED_PRODUCT_PENALTY = 800;
		static const unsigned int WEAK_ALLOCATION_PROHIBITION_PENALTY = 8000;
		static const unsigned int WEAK_ISOLATED_FAMILY_ALLOCATION_PENALTY = 50000;

		static void initialize(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							int bruteForceTSPThreshold, int insertionTSPThreshold){
	     	A_THRESHOLD_CLASS = aThresholdClass < 0? DEFAULT_A_THRESHOLD_CLASS : aThresholdClass;
			B_THRESHOLD_CLASS = bThresholdClass < 0? DEFAULT_B_THRESHOLD_CLASS : bThresholdClass;
			MAX_PERTUBATIONS  = maxPerturbations < 0? DEFAULT_MAX_PERTUBATIONS : maxPerturbations;
			MAX_ITERATIONS_WITHOUT_IMPROVEMENT = maxIWI < 0? DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT : maxIWI;
			BRUTE_FORCE_TSP_THRESHOLD= bruteForceTSPThreshold < 0 ? DEFAULT_BRUTE_FORCE_TSP_THRESHOLD: bruteForceTSPThreshold;
			INSERTION_TSP_THRESHOLD = insertionTSPThreshold < 0 ? DEFAULT_INSERTION_TSP_THRESHOLD : insertionTSPThreshold;
		}

	private:
		OptimizationParameters() = default;
		OptimizationParameters(OptimizationParameters&&) = delete;
		OptimizationParameters(OptimizationParameters&) = delete;
		OptimizationParameters& operator=(const OptimizationParameters&) = delete;
  		OptimizationParameters& operator=(OptimizationParameters&&) = delete;

		static const int DEFAULT_A_THRESHOLD_CLASS = 30;
		static const int DEFAULT_B_THRESHOLD_CLASS = 60;
		static const int DEFAULT_MAX_PERTUBATIONS = 20;
		static const int DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT = 10;
		static const int DEFAULT_BRUTE_FORCE_TSP_THRESHOLD = 7;
		static const int DEFAULT_INSERTION_TSP_THRESHOLD = 11;
};
