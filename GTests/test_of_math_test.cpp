#include "pch.h"
#include "math_test.h"
#include <cstdlib>

TEST(TaskTest, TestInitConsFields) {
    Task t1(12, 4, '*');
    EXPECT_EQ(t1.num_1, 12);
    EXPECT_EQ(t1.num_2, 4);
    EXPECT_EQ(t1.operation, '*');
}

TEST(TaskTest, TestBadInitConsFields) {
    ASSERT_THROW(Task t1(12, 4, 'j'), std::invalid_argument);
}

TEST(TaskTest, TestBaseConsRange) {
    for (int i = 0; i < 1000; ++i) {
        Task t1;
        EXPECT_GE(t1.num_1, -100);
        EXPECT_LE(t1.num_1, 100);
        EXPECT_GE(t1.num_2, -100);
        EXPECT_LE(t1.num_2, 100);
        EXPECT_TRUE(t1.operation == '+' || t1.operation == '-' || t1.operation == '*');
    }
}

TEST(TaskTest, TestInitConsRange) {
    int min_v = 10;
    int max_v = 20;
    for (int i = 0; i < 1000; ++i) {
        Task t1(min_v, max_v);
        EXPECT_GE(t1.num_1, min_v);
        EXPECT_LE(t1.num_1, max_v);
        EXPECT_GE(t1.num_2, min_v);
        EXPECT_LE(t1.num_2, max_v);
        EXPECT_TRUE(t1.operation == '+' || t1.operation == '-' || t1.operation == '*');
    }
}

TEST(TaskTest, TestAddPositive) {
    Task t1(5, 10, '+');
    EXPECT_EQ(t1.answer, 15);
}

TEST(TaskTest, TestAddNegative) {
    Task t1(-5, -10, '+');
    EXPECT_EQ(t1.answer, -15);
}

TEST(TaskTest, TestSubPositiveResult) {
    Task t1(15, 5, '-');
    EXPECT_EQ(t1.answer, 10);
}

TEST(TaskTest, TestSubNegativeResult) {
    Task t1(5, 15, '-');
    EXPECT_EQ(t1.answer, -10);
}

TEST(TaskTest, TestMultDifferentSigns) {
    Task t1(-4, 5, '*');
    EXPECT_EQ(t1.answer, -20);
}

TEST(TaskTest, TestRangeSinglePoint) {
    Task t1(5, 5);
    EXPECT_EQ(t1.num_1, 5);
    EXPECT_EQ(t1.num_2, 5);
}

TEST(MathTestTest, TestConstructorCount) {
    MathTest test(100);
    EXPECT_EQ(test.getCounts(), 100);
    EXPECT_EQ(test.getCorrectCount(), 0);

    for (int i = 0; i < 100; ++i) {
        Task t = test.getTask(i);
        EXPECT_GE(t.num_1, -100);
        EXPECT_LE(t.num_1, 100);
    }
}

TEST(MathTestTest, TestConstructorCountBad) {
    ASSERT_THROW(MathTest test(-1), std::invalid_argument);
}

TEST(MathTestTest, TestConstructorRange) {
    MathTest test(100, 10, 20);
    EXPECT_EQ(test.getCounts(), 100);

    for (int i = 0; i < 100; ++i) {
        Task t = test.getTask(i);
        EXPECT_GE(t.num_1, 10);
        EXPECT_LE(t.num_1, 20);
    }
}

TEST(MathTestTest, TestConstructorRangeBad) {
    ASSERT_THROW(MathTest test(-1, 10, 20), std::invalid_argument);
}
 
TEST(MathTestTest, TestConstructorFixedOp) {
    MathTest test(100, 1, 10, '*');
    EXPECT_EQ(test.getCounts(), 100);

    for (int i = 0; i < 100; ++i) {
        Task t = test.getTask(i);
        EXPECT_EQ(t.operation, '*');
        EXPECT_EQ(t.answer, t.num_1 * t.num_2);
    }
}

TEST(MathTestTest, TestConstructorFixedOpBad) {
    ASSERT_THROW(MathTest test(-1, 10, 20, '+'), std::invalid_argument);
    ASSERT_THROW(MathTest test(1, 10, 20, 'f'), std::invalid_argument);
}

TEST(TaskMathTest, TestMathTestSubmit) {
    MathTest test(3);

    test.setTask(0, Task(5, 5, '+'));  //10
    test.setTask(1, Task(10, 4, '-')); //6
    test.setTask(2, Task(3, 4, '*'));  //12

    test.submitAnswer(0, 10); //+
    test.submitAnswer(1, 99); //-
    test.submitAnswer(2, 12); //+

    EXPECT_EQ(test.getCorrectCount(), 2);
    EXPECT_EQ(test.getUserAnswer(0), 10);
    EXPECT_EQ(test.getUserAnswer(1), 99);
}

TEST(TaskMathTest, TestMathTestMark) {
    MathTest test(10);

    for (int i = 0; i < 10; ++i) {
        test.setTask(i, Task(1, 1, '+')); //2
    }

    for (int i = 0; i < 10; ++i) test.submitAnswer(i, 2);
    EXPECT_EQ(test.calculateMark(), 'A');

    MathTest testB(10);
    for (int i = 0; i < 10; ++i) testB.setTask(i, Task(1, 1, '+'));
    for (int i = 0; i < 8; ++i)  testB.submitAnswer(i, 2);  //8+
    for (int i = 8; i < 10; ++i) testB.submitAnswer(i, 99); //2-
    EXPECT_EQ(testB.calculateMark(), 'B');

    MathTest testF(10);
    for (int i = 0; i < 10; ++i) testF.setTask(i, Task(1, 1, '+'));

    for (int i = 0; i < 5; ++i)  testF.submitAnswer(i, 2);
    for (int i = 5; i < 10; ++i) testF.submitAnswer(i, 99);
    EXPECT_EQ(testF.calculateMark(), 'F');
}
