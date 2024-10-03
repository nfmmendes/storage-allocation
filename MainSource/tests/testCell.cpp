#include <gtest/gtest.h>
#include <vector>
#include <String>
#include <utility>
#include "../Cell.h"


TEST(CellTest, CellDefaultConstructor){ 
    Cell a;
    
    EXPECT_EQ(a.getCode(), "");
    EXPECT_EQ(a.getIdShelf(), 0);
    EXPECT_EQ(a.getRow(), 0);
    EXPECT_EQ(a.getColumn(), 0);
    EXPECT_EQ(a.getLevels(), 1);
}

TEST(CellTest, CellMemberConstructor){
    Cell a("A", 2, 3, 5, 4);

    EXPECT_EQ(a.getCode(), "A");
    EXPECT_EQ(a.getIdShelf(), 2);
    EXPECT_EQ(a.getLevels(), 3);
    EXPECT_EQ(a.getRow(), 5);
    EXPECT_EQ(a.getColumn(), 4);
}

TEST(CellTest, CellCopyConstructor){
    Cell a("A", 2, 3, 5, 4);
    Cell b { a };

    EXPECT_EQ(a.getCode(), b.getCode()); 
    EXPECT_EQ(a.getIdShelf(), b.getIdShelf()); 
    EXPECT_EQ(a.getLevels(), b.getLevels()); 
    EXPECT_EQ(a.getRow(), b.getRow()); 
    EXPECT_EQ(a.getColumn(), b.getColumn()); 
}

TEST(CellTest, CellEqualityOperator){
    Cell a("A", 2, 3, 5, 4);
    Cell b("A", 2, 3, 5, 4);
    Cell c("B", 2, 3, 5, 4);
    Cell d("A", 8, 3, 5, 4);
    Cell e("A", 2, 8, 5, 4);
    Cell f("A", 2, 3, 7, 4);
    Cell g("A", 2, 3, 5, 8);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(a == e);
    EXPECT_FALSE(a == f);
    EXPECT_FALSE(a == g);
}

TEST(CellTest, CellTestAssignmentOperator){
    Cell a("A", 2, 3, 5, 4);
    Cell b("B", 3, 8, 4, 9);

    EXPECT_NE(a.getCode(), b.getCode()); 
    EXPECT_NE(a.getIdShelf(), b.getIdShelf()); 
    EXPECT_NE(a.getLevels(), b.getLevels()); 
    EXPECT_NE(a.getRow(), b.getRow()); 
    EXPECT_NE(a.getColumn(), b.getColumn()); 

    b = a;

    EXPECT_EQ(a.getCode(), b.getCode()); 
    EXPECT_EQ(a.getIdShelf(), b.getIdShelf()); 
    EXPECT_EQ(a.getLevels(), b.getLevels()); 
    EXPECT_EQ(a.getRow(), b.getRow()); 
    EXPECT_EQ(a.getColumn(), b.getColumn()); 
}

TEST(CellTest, CellLessThanOperatorEqualValues){
    Cell a("A", 2, 3, 5, 4);
    Cell b("A", 2, 3, 5, 4);

    EXPECT_FALSE(a < b);
}

TEST(CellTest, CellLessThanOperatorDifferentCodes){
    Cell a("B", 2, 3, 5, 4);
    Cell b("A", 2, 3, 5, 4);
    Cell c("C", 2, 3, 5, 4);

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a < c);
}

TEST(CellTest, CellLessThanOperatorDifferentIdShelves){
    Cell a("A", 2, 3, 5, 4);
    Cell b("A", 1, 3, 5, 4);
    Cell c("A", 3, 3, 5, 4);

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a < c);
}

TEST(CellTest, CellLessThanOperatorDifferentRows){
    Cell a("A", 2, 4, 5, 4);
    Cell b("A", 2, 1, 5, 4);
    Cell c("A", 2, 5, 5, 4);

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a < c);
}

TEST(CellTest, CellLessThanOperatorDifferentColums){
    Cell a("A", 2, 3, 2, 4);
    Cell b("A", 2, 3, 1, 4);
    Cell c("A", 2, 3, 3, 4);

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a < c);
}

TEST(CellTest, CellLessThanOperatorDifferentLevels){
    Cell a("A", 2, 3, 5, 2);
    Cell b("A", 2, 3, 5, 1);
    Cell c("A", 2, 3, 5, 3);

    EXPECT_FALSE(a < b);
    EXPECT_TRUE(a < c);
}