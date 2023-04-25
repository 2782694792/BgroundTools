#include "B.h"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::AtLeast;
using ::testing::Gt;
using ::testing::Return;
using ::testing::Sequence;

MockB b;

TEST(mock_sub, action_B_sub) {
    EXPECT_CALL(b, sub)
        .Times(::testing::AtLeast(3)) // 3次需要3个WillOnce
        .WillOnce(::testing::Return(1))
        .WillOnce(::testing::Return(2))
        .WillOnce(::testing::Return(34));

    std::cout << b.sub(2, 1) << std::endl;
    std::cout << b.sub(3, 1) << std::endl;
    std::cout << b.sub(55, 44) << std::endl;
    std::cout << b.sub(34, 0) << std::endl; // 默认返回 0
}

TEST(mock_sub, expect_call) {
    EXPECT_CALL(b, sub(123, 123)).WillRepeatedly(Return(246));

    std::cout << b.sub(123, 1234) << std::endl; // 默认 0
    std::cout << b.sub(123, 123) << std::endl; // 符合，246，测试用例失效
    std::cout << b.sub(123, 123) << std::endl; // 默认 0

    EXPECT_CALL(b, sub(Gt(123), _))
        .WillOnce(Return(1234));               // 大于 123，和任意数值
    std::cout << b.sub(124, 123) << std::endl; // 符合，-99
    std::cout << b.sub(123, 2) << std::endl;   // 0
}

TEST(mock_multi_sub, call_in_sequence) {
    Sequence s1;

    EXPECT_CALL(b, multi).InSequence(s1).WillOnce(Return(222)); // 先
    EXPECT_CALL(b, sub).InSequence(s1).WillOnce(Return(333));   // 后

    std::cout << b.sub(124, 123) << std::endl; // 不符。为 0
    std::cout << b.multi(123, 2) << std::endl; // 先，222
    std::cout << b.sub(124, 123) << std::endl; // 后，333
}


