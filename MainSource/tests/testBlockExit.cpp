#include <gtest/gtest.h>
#include <vector>
#include <String>
#include <utility>
#include "../BlockExit.h"
using std::string;

TEST(BlockExitTests, BlocExitDefaultConstructor){
    BlockExit b;

    EXPECT_EQ(b.getId(), 0);
    EXPECT_DOUBLE_EQ(b.getCoordX(), 0.0);
    EXPECT_DOUBLE_EQ(b.getCoordY(), 0.0);
    EXPECT_EQ(b.getBlockAName(), "");
    EXPECT_EQ(b.getBlockBName(), "");
}

TEST(BlockExitTests, BlockExitMemberConstructor){
    BlockExit b(4, 4.3, 5.9, "A", "B");

    EXPECT_EQ(b.getId(), 4);
    EXPECT_DOUBLE_EQ(b.getCoordX(), 4.3);
    EXPECT_DOUBLE_EQ(b.getCoordY(), 5.9);
    EXPECT_EQ(b.getBlockAName(), "A");
    EXPECT_EQ(b.getBlockBName(), "B");
}

TEST(BlockExitTests, BlockExitCopyConstructor){
    BlockExit a(3, 5.9, 1.2, "X", "Y");
    BlockExit b { a };

    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_DOUBLE_EQ(a.getCoordX(), b.getCoordX());
    EXPECT_DOUBLE_EQ(a.getCoordY(), b.getCoordY());
    EXPECT_EQ(a.getBlockAName(), b.getBlockAName());
    EXPECT_EQ(a.getBlockBName(), b.getBlockBName());
}
