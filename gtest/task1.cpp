#include "gtest/gtest.h"
#include <bits/stdc++.h>

TEST(Cast,IntToLong){
    for(int i=0; i<30000; i+=3){
        EXPECT_EQ(i, (long)i);
    }
}

TEST(Vectors,NullVectorEquality) {
    std::vector<int> v1,v2;
    EXPECT_EQ(v1,v2);
}

TEST(Vectors,NonNullVectorEquality){
    std::vector<int> v1,v2,v3;
    for(int i=0; i<10000; i++){
        v1.push_back(i);
        v2.push_back(i);
    }
    v3 = v1;
    EXPECT_EQ(v1,v2);
    EXPECT_EQ(v2,v3);
}

TEST(Float, SquarePrecision){
    float f=0.0;
    double d;
    for(int i=0; i<10000; i++, f+=0.0324324){ //fails for 100000 iterations
        d = (double)f;
        EXPECT_NEAR(d*d,f*f,0.1);
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}