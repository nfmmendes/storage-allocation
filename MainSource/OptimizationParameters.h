#ifndef OPTIMIZATION_PARAMETERS_H
#define OPTIMIZATION_PARAMETERS_H


namespace {
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
		const unsigned int NON_ALLOCATED_PRODUCT_PENALTY = 800;
		const unsigned int WEAK_ALLOCATION_PROHIBITION_PENALTY = 8000;
		const unsigned int WEAK_ISOLATED_FAMILY_ALLOCATION_PENALTY = 50000;

		static void initialize(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							   int bruteForceTSPThreshold, int insertionTSPThreshold){
								    m_instance = new OptimizationParameters(aThresholdClass, bThresholdClass, maxPerturbations, maxIWI, 
										  bruteForceTSPThreshold, insertionTSPThreshold);
							   }

		const static OptimizationParameters* instance() { return m_instance; }	

	private:
		OptimizationParameters(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							   int bruteForceTSPThreshold, int insertionTSPThreshold):
							A_THRESHOLD_CLASS(aThresholdClass < 0? DEFAULT_A_THRESHOLD_CLASS : aThresholdClass),
							B_THRESHOLD_CLASS(bThresholdClass < 0? DEFAULT_B_THRESHOLD_CLASS : bThresholdClass),
							MAX_PERTUBATIONS (maxPerturbations < 0? DEFAULT_MAX_PERTUBATIONS : maxPerturbations),
							MAX_ITERATIONS_WITHOUT_IMPROVEMENT(maxIWI < 0? DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT : maxIWI),
							BRUTE_FORCE_TSP_THRESHOLD(bruteForceTSPThreshold < 0 ? DEFAULT_BRUTE_FORCE_TSP_THRESHOLD: bruteForceTSPThreshold),
							INSERTION_TSP_THRESHOLD(insertionTSPThreshold < 0 ? DEFAULT_INSERTION_TSP_THRESHOLD : insertionTSPThreshold) {
		}

		static OptimizationParameters* m_instance;
		const static int DEFAULT_A_THRESHOLD_CLASS = 30;
		const static int DEFAULT_B_THRESHOLD_CLASS = 60;
		const static int DEFAULT_MAX_PERTUBATIONS = 20;
		const static int DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT=10;
		const static int DEFAULT_BRUTE_FORCE_TSP_THRESHOLD=7;
		const static int DEFAULT_INSERTION_TSP_THRESHOLD=11;
};
	OptimizationParameters* OptimizationParameters::m_instance = {};
}

#endif