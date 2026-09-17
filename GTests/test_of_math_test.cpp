#include "pch.h"
#include "math_test.h"
#include <cstdlib>
#include <stdexcept>

TEST(TaskTest, TestManualInitSuccess) {
    Task t1(15, 3, '*', false);
    EXPECT_EQ(t1.num_1, 15);
    EXPECT_EQ(t1.num_2, 3);
    EXPECT_EQ(t1.operation, '*');
    EXPECT_EQ(t1.answer, 45);

    Task t2(20, -5, '+', false);
    EXPECT_EQ(t2.num_1, 20);
    EXPECT_EQ(t2.num_2, -5);
    EXPECT_EQ(t2.operation, '+');
    EXPECT_EQ(t2.answer, 15);
}

TEST(TaskTest, TestRandomInitWithFixedOp) {
    int min_v = 10;
    int max_v = 50;
    for (int i = 0; i < 10000; ++i) {
        Task t(min_v, max_v, '*', true);
        EXPECT_GE(t.num_1, min_v);
        EXPECT_LE(t.num_1, max_v);
        EXPECT_GE(t.num_2, min_v);
        EXPECT_LE(t.num_2, max_v);
        EXPECT_EQ(t.operation, '*');
        EXPECT_EQ(t.answer, t.num_1 * t.num_2);
    }
}

TEST(TaskTest, TestDefaultConstructorGeneration) {
    for (int i = 0; i < 10000; ++i) {
        Task t; //Task(-100, 100, '\0', true)
        EXPECT_GE(t.num_1, -100);
        EXPECT_LE(t.num_1, 100);
        EXPECT_GE(t.num_2, -100);
        EXPECT_LE(t.num_2, 100);
        EXPECT_TRUE(t.operation == '+' || t.operation == '-' || t.operation == '*' || t.operation == '/');

        if (t.operation == '/') {
            EXPECT_NE(t.num_2, 0);
            EXPECT_EQ(t.num_1 % t.num_2, 0);
        }
    }
}

TEST(TaskTest, TestInvalidOperationThrow) {
    EXPECT_THROW(Task(10, 2, 'x', false), std::invalid_argument);
    EXPECT_THROW(Task(10, 2, '?', true), std::invalid_argument);
}

TEST(TaskTest, TestInvalidRangeThrow) {
    //is_random && in1 >= in2
    EXPECT_THROW(Task(10, 10, '+', true), std::invalid_argument);
    EXPECT_THROW(Task(20, 10, '+', true), std::invalid_argument);
}

TEST(TaskTest, TestDivisionByZeroThrow) {
    EXPECT_THROW(Task(10, 0, '/', false), std::invalid_argument);
}

//is_random = false
TEST(TaskTest, TestNonIntegerDivisionThrow) {
    //10 / 3 = 3.333
    EXPECT_THROW(Task(10, 3, '/', false), std::invalid_argument);
    EXPECT_THROW(Task(-5, 2, '/', false), std::invalid_argument);
}

TEST(TaskTest, TestValidManualDivision) {
    Task t(10, 2, '/', false);
    EXPECT_EQ(t.num_1, 10);
    EXPECT_EQ(t.num_2, 2);
    EXPECT_EQ(t.operation, '/');
    EXPECT_EQ(t.answer, 5);
}

TEST(TaskTest, TestCalculateAnswerAllOperators) {
    Task tAdd(10, 5, '+', false);
    EXPECT_EQ(tAdd.answer, 15);

    Task tSub(10, 5, '-', false);
    EXPECT_EQ(tSub.answer, 5);

    Task tMul(10, 5, '*', false);
    EXPECT_EQ(tMul.answer, 50);

    Task tDiv(10, 5, '/', false);
    EXPECT_EQ(tDiv.answer, 2);
}

TEST(TaskTest, TestRandomOperationGeneration) {
    bool generated_add = false;
    bool generated_sub = false;
    bool generated_mul = false;
    bool generated_div = false;

    for (int i = 0; i < 10000; ++i) {
        Task t(-50, 50, '\0', true);
        if (t.operation == '+') {
            generated_add = true;
        }
        if (t.operation == '-') {
            generated_sub = true;
        }
        if (t.operation == '*') {
            generated_mul = true;
        }
        if (t.operation == '/') {
            generated_div = true;
        }
        if (generated_add && generated_sub && generated_mul && generated_div) {
            break;
        }
    }

    EXPECT_TRUE(generated_add);
    EXPECT_TRUE(generated_sub);
    EXPECT_TRUE(generated_mul);
    EXPECT_TRUE(generated_div);
}

TEST(TaskTest, TestRandomDivisionWithNegativeRange) {
    for (int i = 0; i < 10000; ++i) {
        Task t(-100, -10, '/', true);
        EXPECT_EQ(t.operation, '/');
        EXPECT_NE(t.num_2, 0);
        EXPECT_EQ(t.num_1 % t.num_2, 0);
    }
}

TEST(MathTestTest, TestConstructorByCount) {
    MathTest test(50);
    EXPECT_EQ(test.getCounts(), 50);
    EXPECT_EQ(test.getCorrectCount(), 0);

    for (int i = 0; i < 50; ++i) {
        Task t = test.getTask(i);
        EXPECT_GE(t.num_1, -100);
        EXPECT_LE(t.num_1, 100);
        EXPECT_TRUE(t.operation == '+' || t.operation == '-' || t.operation == '*' || t.operation == '/');
    }
}

TEST(MathTestTest, TestConstructorByRange) {
    int min_range = 5;
    int max_range = 15;
    MathTest test(30, min_range, max_range);

    EXPECT_EQ(test.getCounts(), 30);

    for (int i = 0; i < 30; ++i) {
        Task t = test.getTask(i);
        if (t.operation != '/') {
            EXPECT_GE(t.num_1, min_range);
            EXPECT_LE(t.num_1, max_range);
            EXPECT_GE(t.num_2, min_range);
            EXPECT_LE(t.num_2, max_range);
        }
        else {
            EXPECT_NE(t.num_2, 0);
            EXPECT_EQ(t.num_1 % t.num_2, 0);
        }
    }
}

TEST(MathTestTest, TestConstructorByFixedOp) {
    MathTest test(20, -10, 10, '-');
    EXPECT_EQ(test.getCounts(), 20);

    for (int i = 0; i < 20; ++i) {
        Task t = test.getTask(i);
        EXPECT_EQ(t.operation, '-');
        EXPECT_GE(t.num_1, -10);
        EXPECT_LE(t.num_1, 10);
        EXPECT_EQ(t.answer, t.num_1 - t.num_2);
    }
}

TEST(MathTestTest, TestInvalidCountThrows) {
    EXPECT_THROW(MathTest(-5), std::invalid_argument);
    EXPECT_THROW(MathTest(0), std::invalid_argument);
    EXPECT_THROW(MathTest(-1, 1, 10), std::invalid_argument);
    EXPECT_THROW(MathTest(0, 1, 10), std::invalid_argument);
    EXPECT_THROW(MathTest(-1, 1, 10, '+'), std::invalid_argument);
    EXPECT_THROW(MathTest(0, 1, 10, '+'), std::invalid_argument);
}

TEST(MathTestTest, TestInvalidOperatorInConstructorThrows) {
    EXPECT_THROW(MathTest(5, 1, 10, 'x'), std::invalid_argument);
    EXPECT_THROW(MathTest(5, 1, 10, '?'), std::invalid_argument);
}

TEST(MathTestTest, TestIndexOutOfRangeThrows) {
    MathTest test(3);

    EXPECT_THROW(test.setTask(-1, Task(1, 1, '+', false)), std::out_of_range);
    EXPECT_THROW(test.setTask(3, Task(1, 1, '+', false)), std::out_of_range);

    EXPECT_THROW(test.submitAnswer(-1, 5), std::out_of_range);
    EXPECT_THROW(test.submitAnswer(3, 5), std::out_of_range);

    test.setTask(2, Task(2, 2, '+', false));
    test.submitAnswer(2, 4);
    EXPECT_EQ(test.getUserAnswer(2), 4);
}

TEST(MathTestTest, TestGettersAndSettersWork) {
    MathTest test(2);
    Task t1(2, 3, '+', false);
    test.setTask(0, t1);

    EXPECT_EQ(test.getTask(0).num_1, 2);
    EXPECT_EQ(test.getTask(0).answer, 5);
    EXPECT_EQ(test.getUserAnswer(0), 0);
}

TEST(MathTestTest, TestCalculateMarkThresholds) {
    MathTest test(10);
    for (int i = 0; i < 10; ++i) {
        test.setTask(i, Task(1, 1, '+', false));
    }

    for (int i = 0; i < 9; ++i) test.submitAnswer(i, 2);
    test.submitAnswer(9, 99);
    EXPECT_EQ(test.calculateMark(), 'A');

    MathTest testB(10);
    for (int i = 0; i < 10; ++i) testB.setTask(i, Task(1, 1, '+', false));
    for (int i = 0; i < 8; ++i)  testB.submitAnswer(i, 2);
    for (int i = 8; i < 10; ++i) testB.submitAnswer(i, 99);
    EXPECT_EQ(testB.calculateMark(), 'B');

    MathTest testC(10);
    for (int i = 0; i < 10; ++i) testC.setTask(i, Task(1, 1, '+', false));
    for (int i = 0; i < 7; ++i)  testC.submitAnswer(i, 2);
    for (int i = 7; i < 10; ++i) testC.submitAnswer(i, 99);
    EXPECT_EQ(testC.calculateMark(), 'C');

    MathTest testD(10);
    for (int i = 0; i < 10; ++i) testD.setTask(i, Task(1, 1, '+', false));
    for (int i = 0; i < 6; ++i)  testD.submitAnswer(i, 2);
    for (int i = 6; i < 10; ++i) testD.submitAnswer(i, 99);
    EXPECT_EQ(testD.calculateMark(), 'D');

    MathTest testF(10);
    for (int i = 0; i < 10; ++i) testF.setTask(i, Task(1, 1, '+', false));
    for (int i = 0; i < 5; ++i)  testF.submitAnswer(i, 2);
    for (int i = 5; i < 10; ++i) testF.submitAnswer(i, 99);
    EXPECT_EQ(testF.calculateMark(), 'F');
}