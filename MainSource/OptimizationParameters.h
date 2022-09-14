#pragma once

/**
 *	Class with constant data used as parameters of algorithm 
 */
class OptimizationParameters {
	
	public: 
		const unsigned int A_THRESHOLD_CLASS;
		const unsigned int B_THRESHOLD_CLASS;
		const unsigned int MAX_PERTUBATIONS;
		const unsigned int MAX_ITERATIONS_WITHOUT_IMPROVEMENT;
		const unsigned int BRUTE_FORCE_TSP_THRESHOLD;
		const unsigned int INSERTION_TSP_THRESHOLD;
		static const unsigned int NON_ALLOCATED_PRODUCT_PENALTY = 800;
		static const unsigned int WEAK_ALLOCATION_PROHIBITION_PENALTY = 8000;
		static const unsigned int WEAK_ISOLATED_FAMILY_ALLOCATION_PENALTY = 50000;

		OptimizationParameters(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							int bruteForceTSPThreshold, int insertionTSPThreshold);

		static void initialize(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							int bruteForceTSPThreshold, int insertionTSPThreshold);

		static const OptimizationParameters* instance();

	private:
		static OptimizationParameters* m_instance; 
		static const int DEFAULT_A_THRESHOLD_CLASS = 30;
		static const int DEFAULT_B_THRESHOLD_CLASS = 60;
		static const int DEFAULT_MAX_PERTUBATIONS = 20;
		static const int DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT = 10;
		static const int DEFAULT_BRUTE_FORCE_TSP_THRESHOLD = 7;
		static const int DEFAULT_INSERTION_TSP_THRESHOLD = 11;
};
