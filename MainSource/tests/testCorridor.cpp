#include<gtest/gtest.h>
#include<utility>
#include "../Corridor.h"

using std::make_pair;

TEST(TestCorridor, CorridorDefaultConstructor_Test){
    Corridor a;

    EXPECT_EQ(a.getId(), 0);
    EXPECT_EQ(a.getDirection(), VERTICAL);
    EXPECT_EQ(a.getSense(), UP_DOWN);
    EXPECT_EQ(a.getBeginCoords(), make_pair(0.0 , 0.0));
    EXPECT_DOUBLE_EQ(a.getLength(), 0.0);
}

TEST(TestCorridor, CorridorMemberConstructor_Test){
    Corridor a(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);

    EXPECT_EQ(a.getId(), 3);
    EXPECT_EQ(a.getDirection(), HORIZONTAL);
    EXPECT_EQ(a.getSense(), LEFT_TO_RIGHT);
    EXPECT_EQ(a.getBeginCoords(), make_pair(4.5, 3.2));
    EXPECT_EQ(a.getLength(), 3.9);
}

TEST(TestCorridor, CorridorCopyConstructor_Test){
    Corridor a(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b { a }; 

    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_EQ(a.getDirection(), b.getDirection());
    EXPECT_EQ(a.getSense(), b.getSense());
    EXPECT_EQ(a.getBeginCoords(), b.getBeginCoords());
    EXPECT_EQ(a.getLength(), b.getLength());
}