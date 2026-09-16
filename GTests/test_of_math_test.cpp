#include "pch.h"
#include "math_test.h"
#include <cstdlib>

TEST(TaskMathTest, TestInitFields) {
    Task t1(12, 4, '/');
    EXPECT_EQ(t1.num_1, 12);
    EXPECT_EQ(t1.num_2, 4);
    EXPECT_EQ(t1.operation, '/');
}

TEST(TaskMathTest, TestAddPositive) {
    Task t1(5, 10, '+');
    EXPECT_DOUBLE_EQ(t1.answer, 15.0);
}

TEST(TaskMathTest, TestAddNegative) {
    Task t1(-5, -10, '+');
    EXPECT_DOUBLE_EQ(t1.answer, -15.0);
}

TEST(TaskMathTest, TestSubPositiveResult) {
    Task t1(15, 5, '-');
    EXPECT_DOUBLE_EQ(t1.answer, 10.0);
}

TEST(TaskMathTest, TestSubNegativeResult) {
    Task t1(5, 15, '-');
    EXPECT_DOUBLE_EQ(t1.answer, -10.0);
}

TEST(TaskMathTest, TestMultDifferentSigns) {
    Task t1(-4, 5, '*');
    EXPECT_DOUBLE_EQ(t1.answer, -20.0);
}

TEST(TaskMathTest, TestDivIntegerPositive) {
    Task t1(10, 2, '/');
    EXPECT_DOUBLE_EQ(t1.answer, 5.0);
}

TEST(TaskMathTest, TestDivIntegerNegative) {
    Task t1(10, -2, '/');
    EXPECT_DOUBLE_EQ(t1.answer, -5.0);
}

TEST(TaskMathTest, TestDivFractionalPositive) {
    Task t1(5, 2, '/');
    EXPECT_DOUBLE_EQ(t1.answer, 2.5);
}

TEST(TaskMathTest, TestDivNegativeFractional) {
    Task t1(-5, 2, '/');
    EXPECT_DOUBLE_EQ(t1.answer, -2.5);
}

TEST(TaskMathTest, RangeDefault) {
    for (int i = 0; i < 1000; ++i) {
        Task t1;
        EXPECT_GE(t1.num_1, -100);
        EXPECT_LE(t1.num_1, 100);
        EXPECT_GE(t1.num_2, -100);
        EXPECT_LE(t1.num_2, 100);
        EXPECT_TRUE(t1.operation == '+' || t1.operation == '-' ||
            t1.operation == '*' || t1.operation == '/');
    }
}

TEST(TaskMathTest, TestRangeCustom) {
    int min_v = 10;
    int max_v = 20;
    for (int i = 0; i < 1000; ++i) {
        Task t1(min_v, max_v);
        EXPECT_GE(t1.num_1, min_v);
        EXPECT_LE(t1.num_1, max_v);
        EXPECT_GE(t1.num_2, min_v);
        EXPECT_LE(t1.num_2, max_v);
    }
}

TEST(TaskMathTest, TestRangeSinglePoint) {
    Task t1(5, 5);
    EXPECT_EQ(t1.num_1, 5);
    EXPECT_EQ(t1.num_2, 5);
}

TEST(TaskMathTest, TestZeroDefensePositive) {
    for (int i = 0; i < 1000; ++i) {
        Task t1(0, 5);
        if (t1.operation == '/') {
            EXPECT_NE(t1.num_2, 0);
        }
    }
}

TEST(TaskMathTest, TestZeroDefenseNegative) {
    for (int i = 0; i < 1000; ++i) {
        Task t1(-5, 0);
        if (t1.operation == '/') {
            EXPECT_NE(t1.num_2, 0);
        }
    }
}

TEST(TaskMathTest, TestZeroDefenseAtZero) {
    for (int i = 0; i < 1000; ++i) {
        Task t1(0, 0);
        EXPECT_NE(t1.operation, '/'); //замена деления на +
        EXPECT_DOUBLE_EQ(t1.answer, 0.0);
    }
}
