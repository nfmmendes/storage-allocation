#include<gtest/gtest.h>
#include <vector>
#include <utility>
#include "../Vertex.h"
#include "../Arc.h"
#include "../Graph.h"
using std::make_pair;
using namespace QuickTSP;

vector<Vertex> vertexes { {"A", "X", 1}, 
                              {"B", "X", 2}, 
                              {"C", "Y", 3},
                              {"D", "K", 4},
                              {"E", "Y", 5}
                              };
    map<Vertex, vector<Arc>> arcs {
        
        {
            vertexes[0], 
            vector<Arc>({
                            Arc("AB", 2, vertexes[0], vertexes[1]),
                            Arc("AC", 5, vertexes[0], vertexes[2]),
                            Arc("DA", 3, vertexes[3], vertexes[0]),
                            Arc("AA", 1, vertexes[0], vertexes[0])
                        })
        },
        {
            vertexes[1], 
            vector<Arc>({
                            Arc("AB", 2, vertexes[0], vertexes[1]),
                            Arc("BC", 9, vertexes[1], vertexes[2])
                        })
        },
        {
            vertexes[2], 
            vector<Arc>({
                            Arc("AC", 5, vertexes[0], vertexes[2]),
                            Arc("BC", 9, vertexes[1], vertexes[2])
                        })
        },
        {
            vertexes[3],
            vector<Arc>({ 
                            Arc("DE", 8, vertexes[3], vertexes[4]),
                            Arc("DA", 3, vertexes[3], vertexes[0])
                        })
        },
        {
            vertexes[4],
            vector<Arc>({
                            Arc("DE", 8, vertexes[3], vertexes[4])
                        })
        }
    };


TEST(GraphTest, GraphDefaultConstructor){
    Graph a;

    EXPECT_TRUE(a.getVertexes().empty());
    EXPECT_TRUE(a.getArcs().empty());
    EXPECT_EQ(a.getName(), "");
}

TEST(GraphTest, GraphMemberConstructor){

    Graph a(vertexes, arcs, "graph");

    EXPECT_EQ(a.getVertexes().size(), 5);
    EXPECT_EQ(a.getVertexes()[0], vertexes[0]);
    EXPECT_EQ(a.getVertexes()[1], vertexes[1]);
    EXPECT_EQ(a.getVertexes()[2], vertexes[2]);
    EXPECT_EQ(a.getVertexes()[3], vertexes[3]);
    EXPECT_EQ(a.getVertexes()[4], vertexes[4]);

    EXPECT_EQ(a.getArcs().size(), 5);
    EXPECT_EQ(a.getArcs().at(vertexes[0]).size(), 4);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[0], arcs[vertexes[0]][0]); 
    EXPECT_EQ(a.getArcs().at(vertexes[0])[1], arcs[vertexes[0]][1]); 
    EXPECT_EQ(a.getArcs().at(vertexes[0])[2], arcs[vertexes[0]][2]); 
    EXPECT_EQ(a.getArcs().at(vertexes[0])[3], arcs[vertexes[0]][3]); 

    EXPECT_EQ(a.getArcs().at(vertexes[1]).size(), 2);
    EXPECT_EQ(a.getArcs().at(vertexes[1])[0], arcs[vertexes[1]][0]); 
    EXPECT_EQ(a.getArcs().at(vertexes[1])[1], arcs[vertexes[1]][1]); 

    EXPECT_EQ(a.getArcs().at(vertexes[2]).size(), 2);
    EXPECT_EQ(a.getArcs().at(vertexes[2])[0], arcs[vertexes[2]][0]); 
    EXPECT_EQ(a.getArcs().at(vertexes[2])[1], arcs[vertexes[2]][1]); 

    EXPECT_EQ(a.getArcs().at(vertexes[3]).size(), 2);
    EXPECT_EQ(a.getArcs().at(vertexes[3])[0], arcs[vertexes[3]][0]); 
    EXPECT_EQ(a.getArcs().at(vertexes[3])[1], arcs[vertexes[3]][1]); 

    EXPECT_EQ(a.getArcs().at(vertexes[4]).size(), 1); 
    EXPECT_EQ(a.getArcs().at(vertexes[4])[0], arcs[vertexes[4]][0]); 

    EXPECT_EQ(a.getName(), "graph");
    
}

TEST(GraphTest, GraphCopyConstructor){
    
    Graph a(vertexes, arcs, "graph");
    Graph b { a };

    EXPECT_EQ(a.getVertexes().size(), b.getVertexes().size());
    EXPECT_EQ(a.getVertexes()[0],  b.getVertexes()[0]);
    EXPECT_EQ(a.getVertexes()[1],  b.getVertexes()[1]);
    EXPECT_EQ(a.getVertexes()[2],  b.getVertexes()[2]);
    EXPECT_EQ(a.getVertexes()[3],  b.getVertexes()[3]);
    EXPECT_EQ(a.getVertexes()[4],  b.getVertexes()[4]);

    EXPECT_EQ(a.getArcs().size(), b.getArcs().size());
    EXPECT_EQ(a.getArcs().at(vertexes[0]).size(), b.getArcs().at(vertexes[0]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[0])[0], b.getArcs().at(vertexes[0])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[1], b.getArcs().at(vertexes[0])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[2], b.getArcs().at(vertexes[0])[2]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[3], b.getArcs().at(vertexes[0])[3]);
    EXPECT_EQ(a.getArcs().at(vertexes[1]).size(), b.getArcs().at(vertexes[1]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[1])[0], b.getArcs().at(vertexes[1])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[1])[1], b.getArcs().at(vertexes[1])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[2]).size(), b.getArcs().at(vertexes[2]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[2])[0], b.getArcs().at(vertexes[2])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[2])[1], b.getArcs().at(vertexes[2])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[3]).size(), b.getArcs().at(vertexes[3]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[3])[0], b.getArcs().at(vertexes[3])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[3])[1], b.getArcs().at(vertexes[3])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[4]).size(), b.getArcs().at(vertexes[4]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[4])[0], b.getArcs().at(vertexes[4])[0]);
 
    EXPECT_EQ(a.getName(), b.getName());   
}


TEST(GraphTest, GraphAssignmentOperator){
    Graph a(vertexes, arcs, "graph");
    Graph b(vector<Vertex>{vertexes[0], 
                           vertexes[1], 
                           vertexes[2]}, map<Vertex,vector<Arc>>(), 
                             "graphB");
    
    // Test pre conditions
    EXPECT_NE(a.getVertexes().size(), b.getVertexes().size());
    EXPECT_NE(a.getArcs().size(), b.getArcs().size());
    EXPECT_NE(a.getName(), b.getName());

    b = a;

    EXPECT_EQ(a.getVertexes().size(), b.getVertexes().size());
    EXPECT_EQ(a.getVertexes()[0],  b.getVertexes()[0]);
    EXPECT_EQ(a.getVertexes()[1],  b.getVertexes()[1]);
    EXPECT_EQ(a.getVertexes()[2],  b.getVertexes()[2]);
    EXPECT_EQ(a.getVertexes()[3],  b.getVertexes()[3]);
    EXPECT_EQ(a.getVertexes()[4],  b.getVertexes()[4]);

    EXPECT_EQ(a.getArcs().size(), b.getArcs().size());
    EXPECT_EQ(a.getArcs().at(vertexes[0]).size(), b.getArcs().at(vertexes[0]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[0])[0], b.getArcs().at(vertexes[0])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[1], b.getArcs().at(vertexes[0])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[2], b.getArcs().at(vertexes[0])[2]);
    EXPECT_EQ(a.getArcs().at(vertexes[0])[3], b.getArcs().at(vertexes[0])[3]);
    EXPECT_EQ(a.getArcs().at(vertexes[1]).size(), b.getArcs().at(vertexes[1]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[1])[0], b.getArcs().at(vertexes[1])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[1])[1], b.getArcs().at(vertexes[1])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[2]).size(), b.getArcs().at(vertexes[2]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[2])[0], b.getArcs().at(vertexes[2])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[2])[1], b.getArcs().at(vertexes[2])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[3]).size(), b.getArcs().at(vertexes[3]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[3])[0], b.getArcs().at(vertexes[3])[0]);
    EXPECT_EQ(a.getArcs().at(vertexes[3])[1], b.getArcs().at(vertexes[3])[1]);
    EXPECT_EQ(a.getArcs().at(vertexes[4]).size(), b.getArcs().at(vertexes[4]).size());
    EXPECT_EQ(a.getArcs().at(vertexes[4])[0], b.getArcs().at(vertexes[4])[0]);
 
    EXPECT_EQ(a.getName(), b.getName());   
}