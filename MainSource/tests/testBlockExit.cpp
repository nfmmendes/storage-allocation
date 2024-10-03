#include <gtest/gtest.h>
#include <vector>
#include <String>
#include <utility>
#include "../BlockExit.h"
using std::string;

TEST(BlockExitTests, BlocExitDefaultConstructor_Test){
    BlockExit b;

    EXPECT_EQ(b.getId(), 0);
    EXPECT_DOUBLE_EQ(b.getCoordX(), 0.0);
    EXPECT_DOUBLE_EQ(b.getCoordY(), 0.0);
    EXPECT_EQ(b.getBlockAName(), "");
    EXPECT_EQ(b.getBlockBName(), "");
}

TEST(BlockExitTests, BlockExitMemberConstructor_Test){
    BlockExit b(4, 4.3, 5.9, "A", "B");

    EXPECT_EQ(b.getId(), 4);
    EXPECT_DOUBLE_EQ(b.getCoordX(), 4.3);
    EXPECT_DOUBLE_EQ(b.getCoordY(), 5.9);
    EXPECT_EQ(b.getBlockAName(), "A");
    EXPECT_EQ(b.getBlockBName(), "B");
}

TEST(BlockExitTests, BlockExitCopyConstructor_Test){
    BlockExit a(3, 5.9, 1.2, "X", "Y");
    BlockExit b { a };

    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_DOUBLE_EQ(a.getCoordX(), b.getCoordX());
    EXPECT_DOUBLE_EQ(a.getCoordY(), b.getCoordY());
    EXPECT_EQ(a.getBlockAName(), b.getBlockAName());
    EXPECT_EQ(a.getBlockBName(), b.getBlockBName());
}

TEST(BlockExitTests, BlockExitEqualitOperator_Test){
    BlockExit a(3, 5.9, 1.2, "X", "Y");
    BlockExit b { a };

    EXPECT_TRUE(a == b);

    BlockExit c(10, 5.9, 1.2, "X", "Y");

    EXPECT_FALSE(a == c);

    BlockExit d(3, 2.9, 1.2, "X", "Y");

    EXPECT_FALSE(a == d);

    BlockExit e(3, 5.9, 4.3, "X", "Y");

    EXPECT_FALSE(a == e);

    BlockExit f(3, 5.9, 1.2, "K", "Y");

    EXPECT_FALSE(a == f);

    BlockExit g(3, 5.9, 1.2, "X", "Z");

    EXPECT_FALSE(a == g);
}

TEST(BlockExitTests, BlockExitTests_BlockExitInequalityOperator_Test){
    BlockExit a(3, 5.9, 1.2, "X", "Y");
    BlockExit b { a };

    EXPECT_FALSE(a != b);

    BlockExit c(10, 5.9, 1.2, "X", "Y");

    EXPECT_TRUE(a != c);

    BlockExit d(3, 2.9, 1.2, "X", "Y");

    EXPECT_TRUE(a != d);

    BlockExit e(3, 5.9, 4.3, "X", "Y");

    EXPECT_TRUE(a != e);

    BlockExit f(3, 5.9, 1.2, "K", "Y");

    EXPECT_TRUE(a != f);

    BlockExit g(3, 5.9, 1.2, "X", "Z");

    EXPECT_TRUE(a != g);
}

TEST(BlockExitTests, BlockExitAssignmentOperator_Test){
    BlockExit a(3, 5.9, 1.2, "X", "Y");
    BlockExit b(5, 8.8, 2.3, "A", "B");

    // Test pre-conditions
    EXPECT_NE(a.getId(), b.getId());
    EXPECT_NE(a.getCoordX(), b.getCoordX());
    EXPECT_NE(a.getCoordY(), b.getCoordY());
    EXPECT_NE(a.getBlockAName(), b.getBlockAName());
    EXPECT_NE(a.getBlockBName(), b.getBlockBName());

    b = a;

    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_DOUBLE_EQ(a.getCoordX(), b.getCoordX());
    EXPECT_DOUBLE_EQ(a.getCoordY(), b.getCoordY());
    EXPECT_EQ(a.getBlockAName(), b.getBlockAName());
    EXPECT_EQ(a.getBlockBName(), b.getBlockBName());
}

TEST(BlockExitTests, BlockExitLessThanOperator_Test){
    BlockExit a(2, 2, 3, "A", "B");
    BlockExit b(1, 2, 3, "A", "B");
    BlockExit c(2, 2, 1, "A", "B");
    BlockExit d(2, 2, 4, "A", "B");
    BlockExit e(2, 1, 3, "A", "B");
    BlockExit f(2, 1, 4, "A", "B");
    BlockExit g(2, 3, 1, "A", "B");
    BlockExit h(2, 3, 4, "A", "B");
    BlockExit i(2, 2, 3, "A", "B");

    EXPECT_FALSE( a < b);
    EXPECT_TRUE(b < a);
    EXPECT_TRUE(c < a);
    EXPECT_FALSE(d < a);
    EXPECT_TRUE(e < a);
    EXPECT_TRUE(f < a);
    EXPECT_FALSE(g < a);
    EXPECT_FALSE(h < a);
    EXPECT_FALSE(i < a);
}