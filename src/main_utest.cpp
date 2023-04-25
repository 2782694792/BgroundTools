#include "A_Test.h"
// #include "B_Mock.h"
#include <gtest/gtest.h>


int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);

    // testing::Environment* env = new TestFA2();
    // testing::AddGlobalTestEnvironment(env);

    int ret = 0;
    ret     = RUN_ALL_TESTS();
    return ret;
}
