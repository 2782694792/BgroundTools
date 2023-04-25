#include "A.h"
#include <gtest/gtest.h>
#include <iostream>
#include <algorithm>


TEST(test_add, eq_3_when_given_1_and_2) {
    A a;
    EXPECT_EQ(a.add(1, 2), 3); // 类成员

    EXPECT_STREQ("hello", "world") << "string compare";
    SUCCEED();
    // FAIL();

    ASSERT_ANY_THROW(1 == 0);
}

TEST_F(TestFA, is_empty_on_B){
    EXPECT_GE(deq.use_count(), 1);

    if(deq.use_count() != 0){
        deq.reset();
    }
}

TEST_F(TestFA, is_empty_on_B_independence){
    EXPECT_GE(deq.use_count(), 1);
}

TEST(TestFA21, globalEnv){
    EXPECT_EQ(3, 4)  << "int compare";
}
