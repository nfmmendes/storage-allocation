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


TEST(BlockTest, TestDefaultConstructor){
    Block b;
    
    EXPECT_TRUE(b.getShelves().empty());
    EXPECT_TRUE(b.getCorridors().empty());
    EXPECT_TRUE(b.getExits().empty());
    EXPECT_TRUE(b.getCurves().empty());
    EXPECT_TRUE(b.getName().empty());
}

TEST(BlockTest, TestMemberConstructor){
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

TEST(BlockTest, TestMemberConstructorWithNegativeWidth){
    Block b("", 0, 0, -5, 1);

    EXPECT_DOUBLE_EQ(b.getWidth(), 0);
}

TEST(BlockTest, TestMemberConstructorWithNegativeLength){
    Block b("", 0, 0, 1, -5);

    EXPECT_DOUBLE_EQ(b.getLenght(), 0);
}

TEST(BlockTest, TestCopyConstructor){
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

TEST(BlockTest, TestSetBlockCurvesEmpty){
    Block block;
    block.setCurves(vector<Curve>());

    EXPECT_TRUE(block.getCurves().empty());
}


TEST(BlockTest, TestSetBlockCurves){
    Curve a(5, 1, 2, Point("A", 3, 4), Point("B", 5, 6));
    Curve b(6, 5, 6, Point("C", 8, 9), Point("D", 1, 4));
    Curve c(7, 0, 3, Point("E", 7, 5), Point("F", 3, 9));

    vector<Curve> curves {a, b, c};

    Block block;
    block.setCurves(curves);

    EXPECT_EQ(block.getCurves().size(), curves.size());
    for(auto i = 0; i< curves.size(); i++){
        EXPECT_EQ(curves[i] , block.getCurves()[i]);
    }
}

TEST(BlockTest, TestSetBlockCorridorsEmpty){
    Block b;
    b.setCorridors(vector<Corridor>());

    EXPECT_TRUE(b.getCorridors().empty());
}

TEST(BlockTest, TestSetBlockCorridors){ 
    Corridor a (1, "A", "HORIZONTAL", "LEFT_TO_RIGHT", {2, 4}, 3);
    Corridor b (2, "B", "VERTICAL", "UP_DOWN", {2, 4}, 3);
    Corridor c (3, "C", "HORIZONTAL", "RIGHT_TO_LEFT", {2, 4}, 3);

    vector<Corridor> corridors{a, b, c};

    Block block;
    block.setCorridors(corridors);

    EXPECT_EQ(corridors.size(), block.getCorridors().size());
    for(auto i=0; i< corridors.size(); i++){
        EXPECT_EQ(corridors[i], block.getCorridors()[i]);
    }
}

TEST(BlockTest, TestSetShelvesEmpty){
    Block b;
    b.setShelves(vector<Shelf>());

    EXPECT_TRUE(b.getShelves().empty());
}

TEST(BlockTest, TestSetShelves){
    Shelf a(1, {}, {1, 2}, "A", 3, 5, 2, 7);
    Shelf b(2, {}, {3, 5}, "A", 6, 2, 1, 5);
    Shelf c(3, {}, {4, 7}, "A", 1, 4, 3, 8);

    vector<Shelf> shelves{a,b, c};

    Block block;
    block.setShelves(shelves);

    EXPECT_EQ(shelves.size(), block.getShelves().size());

    for(auto i=0; i<shelves.size(); i++){
        EXPECT_EQ(shelves[i], block.getShelves()[i]);
    }
    
    auto result = all_of(begin(shelves), end(shelves),[&block](const auto& elem){    
        return block.getShelvesById().at(elem.getId()) == elem; 
    });
    EXPECT_TRUE(result);
}

TEST(BlockTest, TestAddExits){
    Block b;
    BlockExit exit(1, 9, 2, "A", "B");

    b.addExit(exit);
    EXPECT_EQ(b.getExits().size(), 1);
    EXPECT_EQ(b.getExits()[0], exit);
}

TEST(BlockTest, TestSetName){
    Block b;

    b.setName("Test");

    EXPECT_EQ(b.getName(), "Test");
}

TEST(BlockTest, TestLowerThanOperator){
    Block b("AAA", 0, 0, 0, 0); 
    Block c("BBB", 0, 0, 0, 0);

    EXPECT_TRUE(b < c);
}

TEST(BlockTest, TestAssignmentOperator){
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

    Block b = a;

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
