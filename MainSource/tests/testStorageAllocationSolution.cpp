#include<gtest/gtest.h>
#include "../StorageAllocationSolution.h"
#include <memory>
using std::make_unique;


TEST(TestStorageAllocationSolution, StorageAllocationSolutionDefaultConstructor_Test){
    StorageAllocationSolution a; 
    
    EXPECT_EQ(a.getProductAllocations().size(), 0);
    EXPECT_EQ(a.getNonAllocatedProducts().size(), 0);
}

TEST(TestStorageAllocationSolution, StorageAllocationSolutionMemberConstructor_Test){
    double solutionValue = 1.5;
    double time = 5.6;
    double minDelta = 0.002;
    StorageAllocationSolution a(solutionValue, time, minDelta);

    EXPECT_DOUBLE_EQ(a.getMinDelta(), minDelta);
    EXPECT_DOUBLE_EQ(a.getSolutionValue(), solutionValue);
    EXPECT_DOUBLE_EQ(a.getRuntime(), time);
}

TEST(TestStorageAllocationSolution, StorageAllocationSolutionCopyConstructor_test){
    double solutionValue = 1.5;
    double time = 5.6;
    double minDelta = 0.002;
    StorageAllocationSolution a(solutionValue, time, minDelta);
    StorageAllocationSolution b { a };
    
    EXPECT_DOUBLE_EQ(a.getMinDelta(), b.getMinDelta());
    EXPECT_DOUBLE_EQ(a.getSolutionValue(), b.getSolutionValue());
    EXPECT_DOUBLE_EQ(a.getRuntime(), b.getRuntime());
}

TEST(TestStorageAllocationSolution, StorageAllocationSolutionPointerConstructor_test){
    double solutionValue = 1.5;
    double time = 5.6;
    double minDelta = 0.002;
    auto a = make_unique<StorageAllocationSolution>(solutionValue, time, minDelta);
    StorageAllocationSolution b { a.get() };
    
    EXPECT_DOUBLE_EQ(a->getMinDelta(), b.getMinDelta());
    EXPECT_DOUBLE_EQ(a->getSolutionValue(), b.getSolutionValue());
    EXPECT_DOUBLE_EQ(a->getRuntime(), b.getRuntime());
}

TEST(StorageAllocationSolution, StorageAllocationSolutionSetTotalPenalty_Test){
    StorageAllocationSolution a;
    a.setTotalPenalty(3.5);

    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), 3.5);

    a.setTotalPenalty(-1.5);
    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), -1.5);

    a.setTotalPenalty(0);
    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), 0);
}

TEST(StorageAllocationSolution, StorageAllocationSolutionSetMinDelta_Test) {
    StorageAllocationSolution a;

    a.setMinDelta(3.5);

    EXPECT_DOUBLE_EQ(a.getMinDelta(), 3.5);

    a.setMinDelta(-2);

    EXPECT_NE(a.getMinDelta(), -2);
}


TEST(StorageAllocationSolution, StorageAllocationSolutionSetRuntime_Test) {
    StorageAllocationSolution a;

    a.setRuntime(3.5);

    EXPECT_DOUBLE_EQ(a.getRuntime(), 3.5);

    a.setRuntime(-2);

    EXPECT_NE(a.getRuntime(), -2);
}