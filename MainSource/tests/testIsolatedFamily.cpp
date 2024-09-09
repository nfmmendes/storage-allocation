#include <gtest/gtest.h>
#include "../IsolatedFamily.h"

TEST(TestIsolatedFamily, IsolatedFamilyDefaultConstructor_Test){
    IsolatedFamily a;

    EXPECT_EQ(a.getCode(), "");
    EXPECT_EQ(a.getForce(), "");
    EXPECT_EQ(a.getLevel(), "");
}

TEST(TestIsolatedFamily, IsolatedFamilyMemberConstructor_Test){
    IsolatedFamily a("Force", "Level", "Code");

    EXPECT_EQ(a.getCode(), "Code");
    EXPECT_EQ(a.getForce(), "Force");
    EXPECT_EQ(a.getLevel(), "Level");
}


TEST(TestIsolatedFamily, IsolatedFamilyCopyConstructor_Test){
    IsolatedFamily a("Force", "Level", "Code");
    IsolatedFamily b { a };

    EXPECT_EQ(a.getCode(), b.getCode());
    EXPECT_EQ(a.getForce(), b.getForce());
    EXPECT_EQ(a.getLevel(), b.getLevel());
}