#include <gtest/gtest.h>
#include "../Vertex.h"
using namespace QuickTSP;


TEST(VertexTest, VertexDefaultConstructor){
    Vertex a;

    EXPECT_DOUBLE_EQ(a.getValue(), 0);
    EXPECT_EQ(a.getLabel(), "");
    EXPECT_EQ(a.getType(), "");
}

TEST(VertexTest, VertexMemberConstructor){ 
    Vertex a("LABEL", "TYPE", 10.4);

    EXPECT_DOUBLE_EQ(a.getValue(), 10.4);
    EXPECT_EQ(a.getLabel(), "LABEL");
    EXPECT_EQ(a.getType(), "TYPE");
}

TEST(VertexTest, VertexCopyConstructor){ 
    Vertex a("LABEL", "TYPE", 10.4);
    Vertex b { a };

    EXPECT_DOUBLE_EQ(a.getValue(), b.getValue());
    EXPECT_EQ(a.getLabel(), b.getLabel());
    EXPECT_EQ(a.getType(), b.getType());
}

TEST(VertexTest, VertexSetLabel) { 
    Vertex a("LABEL", "TYPE", 10.4);

    string newLabel = "NEW_LABEL";

    // Test pre-condition
    EXPECT_NE(a.getLabel(), newLabel);

    a.setLabel(newLabel);

    EXPECT_EQ(a.getLabel(), newLabel);
}

TEST(VertexTest, VertexSetTYPE) { 
    Vertex a("LABEL", "TYPE", 10.4);

    string newType = "NEW_TYPE";

    // Test pre-condition
    EXPECT_NE(a.getType(), newType);

    a.setType(newType);

    EXPECT_EQ(a.getType(), newType);
}

TEST(VertexTest, VertexEqualityOperator){
    Vertex a("A", "T_A", 10.0);
    Vertex b("A", "T_A", 10.0);
    Vertex c("B", "T_A", 10.0);
    Vertex d("A", "T_B", 10.0);
    Vertex e("A", "T_A", 10.2);
    Vertex f("A", "T_A", 10.000000000002);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);
    EXPECT_FALSE(a == d);
    EXPECT_FALSE(a == e);
    EXPECT_TRUE(a == f);
}

TEST(VertexTest, VertexInequalityOperator){
    Vertex a("A", "T_A", 10.0);
    Vertex b("A", "T_A", 10.0);
    Vertex c("B", "T_A", 10.0);
    Vertex d("A", "T_B", 10.0);
    Vertex e("A", "T_A", 10.2);
    Vertex f("A", "T_A", 10.000000000002);

    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
    EXPECT_TRUE(a != d);
    EXPECT_TRUE(a != e);
    EXPECT_FALSE(a != f);
}

TEST(VertexTest, VertexLessThanOperator){
    Vertex a("B", "T_B", 10.0);
    Vertex b("B", "T_B", 10.0);
    Vertex c("C", "T_B", 10.0);
    Vertex d("B", "T_C", 10.0);
    Vertex e("B", "T_B", 10.2);
    Vertex f("A", "T_B", 10.0);
    Vertex g("B", "T_A", 10.0);
    Vertex h("B", "T_B", 9.2);

    EXPECT_FALSE( a < b);
    EXPECT_TRUE(a < c);
    EXPECT_TRUE( a < d);
    EXPECT_TRUE( a < e);
    EXPECT_FALSE( a < f);
    EXPECT_FALSE(a < g);
    EXPECT_FALSE( a < h);
}


TEST(VertexTest, VertexAssingmentOperator){
    Vertex a("B", "T_B", 10.0);
    Vertex b("A", "T_X", 9.0);

    // Test pre conditions.
    EXPECT_NE(a.getValue(), b.getValue());
    EXPECT_NE(a.getLabel(), b.getLabel());
    EXPECT_NE(a.getType(), b.getType());

    b = a;

    EXPECT_DOUBLE_EQ(a.getValue(), b.getValue());
    EXPECT_EQ(a.getLabel(), b.getLabel());
    EXPECT_EQ(a.getType(), b.getType());
}