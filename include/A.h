#ifndef GTEST_GMOCK_A_H
#define GTEST_GMOCK_A_H

#include "gtest/gtest.h"
#include <deque>
#include <iostream>
#include <memory>

using namespace std;

class A {
public:
    int add(int a1, int a2) {
        m_a = a1 + a2;
        return m_a;
    };

    virtual int aaa() {
        return m_a;
    };

private:
    int m_a;
};

class TestFA : public ::testing::Test {
public:
    TestFA() {}
    ~TestFA() {}

protected:
    void SetUp() override {
        std::cout << "Reference count: " << deq.use_count() << std::endl;

        auto p    = deq.get();
        auto pxin = *p;

        std::deque< int > a(5, -1);
        std::cout << "1. size: " << pxin.size() << std::endl;

        pxin.swap(a);
        std::cout << "2. size:" << pxin.size() << std::endl;
    }

    void TearDown() override {
        deq.reset();
        deq = nullptr;
    }

public:
    std::shared_ptr< std::deque< int > > deq =
        std::make_shared< std::deque< int > >();
};

class TestFA2 : public testing::Environment {
public:
    void SetUp() override {
        std::cout << "SetUp" << std::endl;
    }
    void TearDown() override {
        std::cout << "TearDown" << std::endl;
    }
};


#endif