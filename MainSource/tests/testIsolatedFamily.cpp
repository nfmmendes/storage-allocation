#include <gtest/gtest.h>
#include "../IsolatedFamily.h"
#include <gtest/gtest-spi.h>
#include <gmock/gmock.h>
using ::testing::Throws;

TEST(TestIsolatedFamily, IsolatedFamilyDefaultConstructor_Test){
    IsolatedFamily a;

    EXPECT_EQ(a.getCode(), "");
    EXPECT_EQ(a.getForce(), "");
    EXPECT_EQ(a.getLevel(), "");
}

TEST(TestIsolatedFamily, IsolatedFamilyMemberConstructor_Test){
    IsolatedFamily a("Force", "Level", "Code");

    EXPECT_EQ(a.getCode(), "Code");
    EXPECT_EQ(a.getForce(), "Force");
    EXPECT_EQ(a.getLevel(), "Level");
}


TEST(TestIsolatedFamily, IsolatedFamilyCopyConstructor_Test){
    IsolatedFamily a("Force", "Level", "Code");
    IsolatedFamily b { a };

    EXPECT_EQ(a.getCode(), b.getCode());
    EXPECT_EQ(a.getForce(), b.getForce());
    EXPECT_EQ(a.getLevel(), b.getLevel());
}

TEST(TestIsolatedFamily, IsolatedFamilyAssignmentOperator_Test){
    IsolatedFamily a("Force", "Level", "Code");
    IsolatedFamily b("No", "Pi", "Delta"); 
    
    //Test pre conditions.
    EXPECT_NE(a.getCode(), b.getCode());
    EXPECT_NE(a.getForce(), b.getForce());
    EXPECT_NE(a.getLevel(), b.getLevel());
    
    b = a;

    EXPECT_EQ(a.getCode(), b.getCode());
    EXPECT_EQ(a.getForce(), b.getForce());
    EXPECT_EQ(a.getLevel(), b.getLevel());
}

TEST(TestIsolatedFamily, IsolatedFamilyEqualityOperator_Test){
    IsolatedFamily a("Force", "Level", "Code");
    IsolatedFamily b("Force", "Level", "Code");
    IsolatedFamily c("X", "Level", "Code");
    IsolatedFamily d("Force", "X", "Code");
    IsolatedFamily e("Force", "Level", "X");

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(a == e);
}


TEST(TestISolatedFamily, IsolatedFamilyIsLowerOrEqualLevel_Test){
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(CELL_LEVEL, CELL_LEVEL));
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(CELL_LEVEL, SHELF_LEVEL));
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(CELL_LEVEL, BLOCK_LEVEL));
    EXPECT_FALSE(IsolatedFamily::isLowerOrEqualLevel(SHELF_LEVEL, CELL_LEVEL));
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(SHELF_LEVEL, SHELF_LEVEL));
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(SHELF_LEVEL, BLOCK_LEVEL));
    EXPECT_FALSE(IsolatedFamily::isLowerOrEqualLevel(BLOCK_LEVEL, CELL_LEVEL));
    EXPECT_FALSE(IsolatedFamily::isLowerOrEqualLevel(BLOCK_LEVEL, SHELF_LEVEL));
    EXPECT_TRUE(IsolatedFamily::isLowerOrEqualLevel(BLOCK_LEVEL, BLOCK_LEVEL));

    EXPECT_THAT([]() { IsolatedFamily::isLowerOrEqualLevel("X", SHELF_LEVEL); }, Throws<std::exception>());
    EXPECT_THAT([]() { IsolatedFamily::isLowerOrEqualLevel(CELL_LEVEL, "X"); }, Throws<std::exception>());
}