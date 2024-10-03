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