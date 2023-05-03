#ifndef GTEST_GMOCK_B_H
#define GTEST_GMOCK_B_H

#include "gmock/gmock.h"

class B {
public:
    B() {}
    ~B() {}

    virtual const int sub(int s1, const int s2) const = 0;
    virtual const int multi(int m1, int m2) const = 0;
};


class MockB : public B {
private:
public:
    MockB(/* args */){}
    ~MockB(){}

    MOCK_METHOD(const int, sub, ( int, const int ), (const, override));
    MOCK_METHOD(const int, multi, ( int, int ), (const, override));
}; 

#endif