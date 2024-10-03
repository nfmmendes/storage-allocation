#include "../Arc.h"
#include "../Vertex.h"
#include <gtest/gtest.h>
using namespace QuickTSP;


TEST(ArcTest, TestDefaultMemberConstructor)
{
    Vertex beginVertex, endVertex;
    Arc arc("label", 1.0, beginVertex, endVertex);
    
    EXPECT_EQ(arc.getLabel(), "label");
    EXPECT_EQ(arc.getValue(), 1.0);
    EXPECT_TRUE(arc.isDirected());
    EXPECT_EQ(arc.getBeginVertex(), beginVertex);
    EXPECT_EQ(arc.getEndVertex(), endVertex);
}

TEST(ArcTest, TestMemberConstructor){
    Vertex beginVertex, endVertex;
    Arc arc("label", 1.0, beginVertex, endVertex,false);
    
    EXPECT_EQ(arc.getLabel(), "label");
    EXPECT_EQ(arc.getValue(), 1.0);
    EXPECT_FALSE(arc.isDirected());
    EXPECT_EQ(arc.getBeginVertex(), beginVertex);
    EXPECT_EQ(arc.getEndVertex(), endVertex);
}

TEST(ArcTest, TestCopyConstructor){
    Vertex beginVertex, endVertex;
    Arc arc("label", 1.0, beginVertex, endVertex,false);

    Arc copy {arc};

    EXPECT_EQ(arc.getLabel(), copy.getLabel());
    EXPECT_EQ(arc.getValue(), copy.getValue());
    EXPECT_EQ(arc.isDirected(), copy.isDirected());
    EXPECT_EQ(arc.getBeginVertex(), copy.getBeginVertex());
    EXPECT_EQ(arc.getEndVertex(), copy.getEndVertex());
}


TEST(ArcTest, TestAssignment){
    Vertex beginVertexA("vertexBeginA", "A");
    Vertex endVertexA("vertexEndA", "A");
    Arc arc("labelA", 2.0, beginVertexA, endVertexA);

    Vertex beginVertexB("vertexBeginB", "B");
    Vertex endVertexB("vertexEndB","B");
    Arc other("labelB", 1.0, beginVertexB, endVertexB,false);

    // Check pre-conditions.
    EXPECT_NE(arc.getLabel(), other.getLabel());
    EXPECT_NE(arc.getValue(), other.getValue());
    EXPECT_NE(arc.isDirected(), other.isDirected());
    EXPECT_NE(arc.getBeginVertex(), other.getBeginVertex());
    EXPECT_NE(arc.getEndVertex(), other.getEndVertex());

    arc = other;

    EXPECT_EQ(arc.getLabel(), other.getLabel());
    EXPECT_EQ(arc.getValue(), other.getValue());
    EXPECT_EQ(arc.isDirected(), other.isDirected());
    EXPECT_EQ(arc.getBeginVertex(), other.getBeginVertex());
    EXPECT_EQ(arc.getEndVertex(), other.getEndVertex());
}

TEST(ArcTest, TestEqualsOperator){
    Vertex beginVertexA("vertexBeginA", "A");
    Vertex endVertexA("vertexEndA", "A");
    Arc arc("labelA", 2.0, beginVertexA, endVertexA);

    Vertex beginVertexB("vertexBeginB", "B");
    Vertex endVertexB("vertexEndB","B");
    Arc other("labelB", 1.0, beginVertexB, endVertexB,false);

    EXPECT_FALSE(arc == other);

    // If TestAssignment test pass, assignment works properly.
    arc = other;

    EXPECT_TRUE(arc == other);
}

TEST(ArcTest, TestLowerThanOperatorWithSameLabelArcs){
    Vertex beginVertexA("vertexBeginA", "A");
    Vertex endVertexA("vertexEndA", "A");
    Arc arcA("label", 2.0, beginVertexA, endVertexA);

    Vertex beginVertexB("vertexBeginB", "B");
    Vertex endVertexB("vertexEndB","B");
    Arc arcB("label", 1.0, beginVertexB, endVertexB,false);

    EXPECT_TRUE(arcB < arcA);
}

TEST(ArcTest, TestLowerThanOperatorWithDifferentLabelArcs){
    Vertex beginVertexA("vertexBeginA", "A");
    Vertex endVertexA("vertexEndA", "A");
    Arc arcA("labelA", 2.0, beginVertexA, endVertexA);

    Vertex beginVertexB("vertexBeginB", "B");
    Vertex endVertexB("vertexEndB","B");
    Arc arcB("labelB", 1.0, beginVertexB, endVertexB,false);

    EXPECT_TRUE(arcA < arcB);
}