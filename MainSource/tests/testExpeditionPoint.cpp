#include<gtest/gtest.h>
#include<utility>
#include "../ExpeditionPoint.h"

using std::pair;
using std::make_pair;

TEST(ExpeditionPointTest, ExpeditionPointConstructor){
    ExpeditionPoint a("A", "b", {3.0, 5.2});
    
    EXPECT_EQ(a.getCode(), "A");
    EXPECT_EQ(a.getBlockCode(), "b");
    EXPECT_EQ(a.getCoordinates(), make_pair(3.0, 5.2));
}

TEST(ExpeditionPointTest, ExpeditionPointCopyConstructor){
    ExpeditionPoint a("A", "b", {3.0, 5.2});
    ExpeditionPoint b { a };

    EXPECT_EQ(a.getCode(), b.getCode());
    EXPECT_EQ(a.getBlockCode(), b.getBlockCode());
    EXPECT_EQ(a.getCoordinates(), b.getCoordinates());
}