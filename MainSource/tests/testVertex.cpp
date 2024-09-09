#include <gtest/gtest.h>
#include "../Vertex.h"
using namespace QuickTSP;


TEST(TestVertex, VertexDefaultConstructor_Test){
    Vertex a;

    EXPECT_DOUBLE_EQ(a.getValue(), 0);
    EXPECT_EQ(a.getLabel(), "");
    EXPECT_EQ(a.getType(), "");
}

TEST(TestVertex, VertexMemberConstructor_Test){ 
    Vertex a("LABEL", "TYPE", 10.4);

    EXPECT_DOUBLE_EQ(a.getValue(), 10.4);
    EXPECT_EQ(a.getLabel(), "LABEL");
    EXPECT_EQ(a.getType(), "TYPE");
}

TEST(TestVertex, VertexCopyConstructor_Test){ 
    Vertex a("LABEL", "TYPE", 10.4);
    Vertex b { a };

    EXPECT_DOUBLE_EQ(a.getValue(), b.getValue());
    EXPECT_EQ(a.getLabel(), "LABEL", b.getLabel());
    EXPECT_EQ(a.getType(), "TYPE", b.getType());
}

TEST(TestVertex, VertexSetLabel_Test) { 
    Vertex a("LABEL", "TYPE", 10.4);

    string newLabel = "NEW_LABEL";

    // Test pre-condition
    EXPECT_NE(a.getLabel(), newLabel);

    a.setLabel(newLabel);

    EXPECT_EQ(a.getLabel(), newLabel);
}

TEST(TestVertex, VertexSetTYPE_Test) { 
    Vertex a("LABEL", "TYPE", 10.4);

    string newType = "NEW_TYPE";

    // Test pre-condition
    EXPECT_NE(a.getType(), newType);

    a.setType(newType);

    EXPECT_EQ(a.getType(), newType);
}