#include <gtest/gtest.h>

#include "../Warehouse.h"
#include <vector>
using std::vector;

TEST(TestWarehouse, WarehouseDefaultConstructor_Test){
    Warehouse a;
    
    EXPECT_EQ(a.getName(), "");
    EXPECT_TRUE(a.getBlocks().empty());
    EXPECT_TRUE(a.getExpeditionPoints().empty());
}