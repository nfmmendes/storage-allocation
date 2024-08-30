#include<iostream>
#include<map>
#include<algorithm>
#include<vector>
#include <gtest/gtest.h>
#include "../Block.h"
#include "../Shelf.h"
#include "../BlockExit.h"
#include "../Corridor.h"
#include "../Point.h"
#include "../Curve.h"


TEST(BlockTests, TestDefaultConstructor){
    Block b;
    
    EXPECT_TRUE(b.getShelves().empty());
    EXPECT_TRUE(b.getCorridors().empty());
    EXPECT_TRUE(b.getExits().empty());
    EXPECT_TRUE(b.getCurves().empty());
    EXPECT_TRUE(b.getName().empty());
}

TEST(BlockTests, TestMemberConstructor){
    Block b("Block", 4, 5, 10, 12);

    EXPECT_EQ(b.getName(), "Block");
    EXPECT_DOUBLE_EQ(b.getBottomLeftCoords().first, 4);
    EXPECT_DOUBLE_EQ(b.getBottomLeftCoords().second, 5);
    EXPECT_DOUBLE_EQ(b.getWidth(), 10);
    EXPECT_DOUBLE_EQ(b.getLenght(), 12);
    // Neither here the internal structures must be initialized.
    EXPECT_TRUE(b.getShelves().empty());
    EXPECT_TRUE(b.getCorridors().empty());
    EXPECT_TRUE(b.getExits().empty());
    EXPECT_TRUE(b.getCurves().empty());
}

TEST(BlockTests, TestCopyConstructor){
    Shelf s1(15, {}, {0,0}, "Block", 1, 1, 1, 1);
    Shelf s2(13, {}, {0,0}, "Block", 1, 1, 1, 1);
    Shelf s3(28, {}, {0,0}, "Block", 1, 1, 1, 1);

    Block a("Block", 8, 9, 15, 12);
    a.setShelves(vector<Shelf>({ s1, s2, s3}));
    a.setCurves(vector<Curve>(5));
    a.setCorridors(vector<Corridor>(10));
    a.addExit(BlockExit());
    a.addExit(BlockExit());
    a.addExit(BlockExit());

    Block b {a};

    EXPECT_EQ(a.getName(), b.getName());
    EXPECT_DOUBLE_EQ(a.getWidth(), b.getWidth());
    EXPECT_DOUBLE_EQ(a.getLenght(), b.getLenght());
    
    EXPECT_EQ(a.getBottomLeftCoords(), b.getBottomLeftCoords());
    EXPECT_EQ(a.getCorridors().size(), b.getCorridors().size());
    EXPECT_EQ(a.getCurves().size(), b.getCurves().size());
    EXPECT_EQ(a.getExits().size(), b.getExits().size());
    EXPECT_EQ(a.getShelves().size(), b.getShelves().size());
    
    const auto & shelfList { a.getShelvesById() };
    auto result = all_of(begin(shelfList), end(shelfList),[&b, &shelfList](const auto& elem){    
        return b.getShelvesById().at(elem.first) == elem.second; 
    });
    EXPECT_TRUE(result);
}
