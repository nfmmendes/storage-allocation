#include <gtest/gtest.h>

#include "../Warehouse.h"
#include <string>

#include <vector>
#include <fstream>
#include <utility>
using std::vector;
using std::ifstream;
using std::string;
using std::make_pair;

TEST(WarehouseTest, WarehouseDefaultConstructor){
    Warehouse a;

    EXPECT_EQ(a.getName(), "");
    EXPECT_TRUE(a.getBlocks().empty());
    EXPECT_TRUE(a.getExpeditionPoints().empty());
}

TEST(WarehouseTest, ReadWarehouseDataInput1) { 
    string inputDir { TEST_INPUTS_DIR }; 
    ifstream input(inputDir + "warehouse_input_1.txt");
    Warehouse a;

    a.readWarehouseData(input);

    EXPECT_EQ(a.getBlocks().size(), 1);
    EXPECT_EQ(a.getExpeditionPoints().size(), 3);

    const auto& block = a.getBlocks()[0];
    auto [coordX, coordY] = block.getBottomLeftCoords();
    EXPECT_DOUBLE_EQ(coordX, 0.0);
    EXPECT_DOUBLE_EQ(coordY, 0.0);
    
    EXPECT_EQ(block.getName(), "BL1");

    const auto & expeditionPoints = a.getExpeditionPoints();
    for(const auto& ep : expeditionPoints)
        EXPECT_EQ(ep.getBlockCode(), "BL1");

    EXPECT_EQ(expeditionPoints[0].getCoordinates(), make_pair(122, 15));
    EXPECT_EQ(expeditionPoints[1].getCoordinates(), make_pair(122, 60));
    EXPECT_EQ(expeditionPoints[2].getCoordinates(), make_pair(295, 50));
}

TEST(WarehouseTest, ReadWarehouseDataInput2) { 
    string inputDir { TEST_INPUTS_DIR }; 
    ifstream input(inputDir + "warehouse_input_2.txt");
    Warehouse a;

    a.readWarehouseData(input);

    EXPECT_EQ(a.getBlocks().size(), 2);
    EXPECT_EQ(a.getExpeditionPoints().size(), 3);

    const auto blocks = a.getBlocks();

    auto [coordX0, coordY0] = blocks[0].getBottomLeftCoords();
    EXPECT_DOUBLE_EQ(coordX0, 0.0);
    EXPECT_DOUBLE_EQ(coordY0, 0.0);

    auto [coordX1, coordY1] = blocks[1].getBottomLeftCoords();
    EXPECT_DOUBLE_EQ(coordX1, 310.0);
    EXPECT_DOUBLE_EQ(coordY1, 100.0);

    const auto & expeditionPoints = a.getExpeditionPoints();
    EXPECT_EQ(expeditionPoints[0].getCoordinates(), make_pair(122, 15));
    EXPECT_EQ(expeditionPoints[0].getBlockCode(), "BL1");

    EXPECT_EQ(expeditionPoints[1].getCoordinates(), make_pair(122, 60));
    EXPECT_EQ(expeditionPoints[1].getBlockCode(), "BL2");
    
    EXPECT_EQ(expeditionPoints[2].getCoordinates(), make_pair(295, 50));
    EXPECT_EQ(expeditionPoints[2].getBlockCode(), "BL1");
}

TEST(WarehouseTest, GetBlocksByName){
    string inputDir { TEST_INPUTS_DIR }; 
    ifstream first_input(inputDir + "warehouse_input_1.txt");
    Warehouse a;

    EXPECT_TRUE(a.getBlocksByName().empty());

    a.readWarehouseData(first_input);
    auto blocksByName = a.getBlocksByName();

    EXPECT_EQ(blocksByName.size(), 1);
    EXPECT_EQ(blocksByName.begin()->first, "BL1");

    ifstream second_input(inputDir + "warehouse_input_2.txt");
    Warehouse b;

    b.readWarehouseData(second_input);
    blocksByName = b.getBlocksByName();

    EXPECT_EQ(blocksByName.size(), 2);
    EXPECT_NE(blocksByName.find("BL1"), blocksByName.end());
    EXPECT_NE(blocksByName.find("BL2"), blocksByName.end());
}