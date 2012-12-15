#include "Job.hpp"

#include "gtest/gtest.h"
using namespace std;

TEST(LWLR_1, LessWeightLenRatio)
{
    Job j1(61, 58);
    Job j2(86, 46);

    LessWeightLenRatio less_ratio;
    ASSERT_TRUE(less_ratio(j1, j2));
}

TEST(LWLD_1, LessWeightLenDiff)
{
    Job j0(4, 1);
    Job j1(61, 58);
    Job j2(86, 46);
    Job j3(87, 46);
    Job j4(87, 45);

    LessWeightLenDiff less_diff;
    ASSERT_TRUE(less_diff(j0, j1));
    ASSERT_TRUE(less_diff(j1, j2));
    ASSERT_TRUE(less_diff(j2, j3));
    ASSERT_TRUE(less_diff(j3, j4));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
