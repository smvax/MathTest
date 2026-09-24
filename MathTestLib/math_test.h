#pragma once
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>

struct Task {
    int num_1;
    int num_2;
    char operation;
    int answer;

    Task(int in1 = -100, int in2 = 100, char op = '\0', bool is_random = true);

    int calculateAnswer() noexcept;
};

class MathTest {
private:
    Task* _tasks;
    int _counts;
    int* _user_answers;
    int _correct_count;

public:
    MathTest(int count);
    MathTest(int count, int min_val, int max_val);
    MathTest(int count, int min_val, int max_val, char op);

    ~MathTest();

    inline int getCounts() const noexcept;
    inline int getCorrectCount() const noexcept;
    inline Task getTask(int index) const;
    inline int getUserAnswer(int index) const;

    void setTask(int index, const Task& task);
    void submitAnswer(int index, int answer) noexcept;
    char calculateMark() const noexcept;
    void run() noexcept;
    void show_statistics() const noexcept;
};

inline int MathTest::getCounts() const noexcept {
    return _counts;
}
inline int MathTest::getCorrectCount() const noexcept {
    return _correct_count;
}
inline Task MathTest::getTask(int index) const {
    return _tasks[index];
}
inline int MathTest::getUserAnswer(int index) const {
    return _user_answers[index];
}