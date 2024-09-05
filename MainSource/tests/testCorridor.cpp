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

TEST(TestCorridor, CorridorGetEndCoords_Test){
    Corridor a;

    EXPECT_DOUBLE_EQ(a.getEndCoords().first, 0);
    EXPECT_DOUBLE_EQ(a.getEndCoords().second, 0);
}


TEST(TestCorridor, CorridorAssignentOperator_Test){
    Corridor a(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b(5, "B", VERTICAL, UP_DOWN, {1.2, 4.9}, 1.0); 

    // Test pre-conditions
    EXPECT_NE(a.getId(), b.getId());
    EXPECT_NE(a.getDirection(), b.getDirection());
    EXPECT_NE(a.getSense(), b.getSense());
    EXPECT_NE(a.getBeginCoords(), b.getBeginCoords());
    EXPECT_NE(a.getLength(), b.getLength());

    a = b;

    EXPECT_EQ(a.getId(), b.getId());
    EXPECT_EQ(a.getDirection(), b.getDirection());
    EXPECT_EQ(a.getSense(), b.getSense());
    EXPECT_EQ(a.getBeginCoords(), b.getBeginCoords());
    EXPECT_DOUBLE_EQ(a.getLength(), b.getLength());
}

TEST(TestCorridor, CorridorEqualsOperator_Test){ 
    Corridor a(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b(5, "B", VERTICAL, UP_DOWN, {1.2, 4.9}, 1.0); 
    Corridor c(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor d(4, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor e(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor f(3, "A", VERTICAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor g(3, "A", HORIZONTAL, RIGHT_TO_LEFT, {4.5, 3.2}, 3.9);
    Corridor h(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.2, 3.2}, 3.9);
    Corridor i(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.8}, 3.9);
    Corridor j(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 9.9);

    EXPECT_FALSE(a == b);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(a == e);
    EXPECT_FALSE(a == f);
    EXPECT_FALSE(a == g);
    EXPECT_FALSE(a == h);
    EXPECT_FALSE(a == i);
    EXPECT_FALSE(a == j);
    EXPECT_TRUE(a == c);
}

TEST(TestCorridor, CorridorInequalsOperator_Test){ 
    Corridor a(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b(5, "B", VERTICAL, UP_DOWN, {1.2, 4.9}, 1.0); 
    Corridor c(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor d(4, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor e(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor f(3, "A", VERTICAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor g(3, "A", HORIZONTAL, RIGHT_TO_LEFT, {4.5, 3.2}, 3.9);
    Corridor h(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.2, 3.2}, 3.9);
    Corridor i(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.8}, 3.9);
    Corridor j(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 9.9);

    EXPECT_TRUE(a != b);
    EXPECT_TRUE(a != d);
    EXPECT_TRUE(a != e);
    EXPECT_TRUE(a != f);
    EXPECT_TRUE(a != g);
    EXPECT_TRUE(a != h);
    EXPECT_TRUE(a != i);
    EXPECT_TRUE(a != j);
    EXPECT_FALSE(a != c);
}

TEST(Test_Corridor, CorridorLessThanOperatorWithDifferentBlocks_Test){
    Corridor a(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b(3, "C", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor c(3, "A", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(a < c);
}

TEST(Test_Corridor, CorridorLessThanOperatorWithDifferentBegins_Test){
    Corridor a(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 3.2}, 3.9);
    Corridor b(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {5.5, 3.2}, 3.9);
    Corridor c(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 4.2}, 3.9);
    Corridor d(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {2.5, 3.2}, 3.9);
    Corridor e(3, "B", HORIZONTAL, LEFT_TO_RIGHT, {4.5, 2.2}, 3.9);
    
    EXPECT_TRUE(a < b);
    EXPECT_TRUE(a < c);
    EXPECT_FALSE(a < d);
    EXPECT_FALSE(a < e);
}
