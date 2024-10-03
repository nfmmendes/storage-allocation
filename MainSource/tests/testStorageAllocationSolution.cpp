#include "../StorageAllocationSolution.h"

#include<gtest/gtest.h>
#include <memory>
#include <map>
#include <vector>
#include <utility>
#include <string>
#include "../Cell.h"
#include "../Product.h"
using std::make_unique;
using std::vector;
using std::map;
using std::string;
using std::make_pair;

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

TEST(TestStorageAllocationSolution, StorageAllocationSolutionSetTotalPenalty_Test){
    StorageAllocationSolution a;
    a.setTotalPenalty(3.5);

    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), 3.5);

    a.setTotalPenalty(-1.5);
    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), -1.5);

    a.setTotalPenalty(0);
    EXPECT_DOUBLE_EQ(a.getTotalPenalty(), 0);
}

TEST(TestStorageAllocationSolution, StorageAllocationSolutionSetMinDelta_Test) {
    StorageAllocationSolution a;

    a.setMinDelta(3.5);

    EXPECT_DOUBLE_EQ(a.getMinDelta(), 3.5);

    a.setMinDelta(-2);

    EXPECT_NE(a.getMinDelta(), -2);
}


TEST(TestStorageAllocationSolution, StorageAllocationSolutionSetRuntime_Test) {
    StorageAllocationSolution a;

    a.setRuntime(3.5);

    EXPECT_DOUBLE_EQ(a.getRuntime(), 3.5);

    a.setRuntime(-2);

    EXPECT_NE(a.getRuntime(), -2);
}

TEST(TestStorageAllocationSolution, StorageAllocationSolutionSetAllocations_Test){
    vector<Product> products { 
        { 1, "AAA", "family_a"},
        { 2, "ABC", "family_a"},
        { 3, "ACD", "family_a"},
        { 4, "BBB", "family_b"},
        { 5, "BBC", "family_b"},
        { 6, "CCC", "family_c"},
        { 7, "CCD", "family_c"},
        { 8, "CCE", "family_c"},
        { 9, "CCF", "family_c"},
    };

    vector<Cell> cells { 
        {"cell1", 1, 1, 1, 1}, 
        {"cell2", 1, 1, 1, 2},
        {"cell3", 1, 1, 2, 1},
        {"cell4", 1, 1, 2, 2},
        {"cell5", 1, 2, 3, 1},
        {"cell6", 1, 2, 3, 2},
        {"cell7", 1, 1, 4, 1},
        {"cell8", 1, 1, 4, 2},
        {"cell11", 2, 1, 1, 1}, 
        {"cell12", 2, 1, 1, 2},
        {"cell13", 2, 1, 2, 1},
        {"cell14", 2, 1, 2, 2},
        {"cell15", 2, 1, 3, 1},
        {"cell16", 2, 1, 3, 2},

    };

    map<Product, Position> allocations {
        { products[0], make_pair(cells[0], 1) },
        { products[1], make_pair(cells[2], 1) },
        { products[2], make_pair(cells[3], 1) },
        { products[3], make_pair(cells[5], 2) },
        { products[4], make_pair(cells[5], 1) },
        { products[5], make_pair(cells[8], 1) },
        { products[6], make_pair(cells[10], 1) },
        { products[7], make_pair(cells[11], 1) },
        { products[8], make_pair(cells[12], 1) },
    };
    
    StorageAllocationSolution a;
    
    EXPECT_TRUE(a.getProductAllocations().empty());
    
    a.setAllocation(allocations, vector<Order>());

    int sequence[] = { 0, 2, 3, 5, 5, 8, 10, 11, 12};
    EXPECT_EQ(a.getProductAllocations().size(), allocations.size());
    for(auto i = 0; i < products.size(); i++)
        EXPECT_EQ(a.getProductAllocations().at(products[i]).first.getCode(), cells[sequence[i]].getCode());
}