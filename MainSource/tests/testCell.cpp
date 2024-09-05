#include <gtest/gtest.h>
#include <vector>
#include <String>
#include <utility>
#include "../Cell.h"


TEST(TestCell, CellDefaultConstructor_Test){ 
    Cell a;
    
    EXPECT_EQ(a.getCode(), "");
    EXPECT_EQ(a.getIdShelf(), 0);
    EXPECT_EQ(a.getRow(), 0);
    EXPECT_EQ(a.getColumn(), 0);
    EXPECT_EQ(a.getLevels(), 1);
}

TEST(TestCell, CellMemberConstructor_Test){
    Cell a("A", 2, 3, 5, 4);

    EXPECT_EQ(a.getCode(), "A");
    EXPECT_EQ(a.getIdShelf(), 2);
    EXPECT_EQ(a.getLevels(), 3);
    EXPECT_EQ(a.getRow(), 5);
    EXPECT_EQ(a.getColumn(), 4);
}

TEST(TestCell, CellCopyConstructor_Test){
    Cell a("A", 2, 3, 5, 4);
    Cell b { a };

    EXPECT_EQ(a.getCode(), b.getCode()); 
    EXPECT_EQ(a.getIdShelf(), b.getIdShelf()); 
    EXPECT_EQ(a.getLevels(), b.getLevels()); 
    EXPECT_EQ(a.getRow(), b.getRow()); 
    EXPECT_EQ(a.getColumn(), b.getColumn()); 
}