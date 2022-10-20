#include "OptimizationParameters.h"


OptimizationParameters* OptimizationParameters::m_instance = {}; 
/*
unsigned int OptimizationParameters::A_THRESHOLD_CLASS = 0;
unsigned int OptimizationParameters::B_THRESHOLD_CLASS = 0;
unsigned int OptimizationParameters::MAX_PERTUBATIONS = 0;
unsigned int OptimizationParameters::MAX_ITERATIONS_WITHOUT_IMPROVEMENT = 0;
unsigned int OptimizationParameters::BRUTE_FORCE_TSP_THRESHOLD = 0;
unsigned int OptimizationParameters::INSERTION_TSP_THRESHOLD = 0;
*/

const OptimizationParameters* OptimizationParameters::instance() { 
    return OptimizationParameters::m_instance; 
}

OptimizationParameters::OptimizationParameters(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
							int bruteForceTSPThreshold, int insertionTSPThreshold): 
    A_THRESHOLD_CLASS (aThresholdClass < 0? DEFAULT_A_THRESHOLD_CLASS : aThresholdClass),
    B_THRESHOLD_CLASS (bThresholdClass < 0? DEFAULT_B_THRESHOLD_CLASS : bThresholdClass),
    MAX_PERTUBATIONS  (maxPerturbations < 0? DEFAULT_MAX_PERTUBATIONS : maxPerturbations),
    MAX_ITERATIONS_WITHOUT_IMPROVEMENT (maxIWI < 0? DEFAULT_MAX_ITERATIONS_WITHOUT_IMPROVEMENT : maxIWI),
    BRUTE_FORCE_TSP_THRESHOLD (bruteForceTSPThreshold < 0 ? DEFAULT_BRUTE_FORCE_TSP_THRESHOLD: bruteForceTSPThreshold),
    INSERTION_TSP_THRESHOLD (insertionTSPThreshold < 0 ? DEFAULT_INSERTION_TSP_THRESHOLD : insertionTSPThreshold)
{}

void OptimizationParameters::initialize(int aThresholdClass, int bThresholdClass, int maxPerturbations, int maxIWI, 
                    int bruteForceTSPThreshold, int insertionTSPThreshold){
    OptimizationParameters::m_instance = new OptimizationParameters(aThresholdClass, bThresholdClass, maxPerturbations, 
                                            maxIWI, bruteForceTSPThreshold, insertionTSPThreshold);
}