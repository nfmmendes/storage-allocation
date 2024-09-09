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
