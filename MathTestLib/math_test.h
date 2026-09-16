#pragma once
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>

struct Task {
    int num_1;
    int num_2;
    char operation;
    int answer;

    int calculateAnswer() {
        int ans = 0;
        switch (operation) {
        case '+':
            ans = num_1 + num_2;
            break;
        case '-':
            ans = num_1 - num_2;
            break;
        case '*':
            ans = num_1 * num_2;
            break;
        }
        return ans;
    }

    Task(int min_val = -100, int max_val = 100) {
        int range = max_val - min_val + 1;
        num_1 = (std::rand() % range) + min_val;
        num_2 = (std::rand() % range) + min_val;

        int op_rander = std::rand() % 3;
        switch (op_rander) {
        case 0:
            operation = '+';
            break;
        case 1:
            operation = '-';
            break;
        case 2:
            operation = '*';
            break;
        }
        answer = calculateAnswer();
    }

    Task(int n1, int n2, char op) : num_1(n1), num_2(n2), operation(op) {
        if (op != '-' && op != '+' && op != '*') {
            throw std::invalid_argument("ERROR: operation char is not valid!");
        }
        answer = calculateAnswer();
    }
};

class MathTest {
private:
    Task* _tasks;
    int _counts;
    int* _user_answers;
    int _correct_count;

public:
    MathTest(int count) : _counts(count), _correct_count(0) {
        if (count <= 0) {
            throw std::invalid_argument("ERROR: Task count must be bigger than 0!");
        }
        _tasks = new Task[_counts];
        _user_answers = new int[_counts] {0};
        for (int i = 0; i < _counts; ++i) {
            _tasks[i] = Task();
        }
    }

    MathTest(int count, int min_val, int max_val) : _counts(count), _correct_count(0) {
        if (count <= 0) {
            throw std::invalid_argument("ERROR: Task count must be bigger than 0!");
        }
        _tasks = new Task[_counts];
        _user_answers = new int[_counts] {0};
        for (int i = 0; i < _counts; ++i) {
            _tasks[i] = Task(min_val, max_val);
        }
    }

    MathTest(int count, int min_val, int max_val, char op) : _counts(count), _correct_count(0) {
        if (count <= 0) {
            throw std::invalid_argument("ERROR: Task count must be bigger than 0!");
        }
        if (op != '-' && op != '+' && op != '*') {
            throw std::invalid_argument("ERROR: operation char is not valid!");
        }
        _tasks = new Task[_counts];
        _user_answers = new int[_counts] {0};
        for (int i = 0; i < _counts; ++i) {
            _tasks[i] = Task(min_val, max_val);
            _tasks[i].operation = op;
            _tasks[i].answer = _tasks[i].calculateAnswer();
        }
    }

    ~MathTest() {
        delete[] _tasks;
        delete[] _user_answers;
    }

    int getCounts() const noexcept {
        return _counts;
    }
    int getCorrectCount() const noexcept {
        return _correct_count;
    }
    Task getTask(int index) const {
        return _tasks[index];
    }
    int getUserAnswer(int index) const {
        return _user_answers[index];
    }

    void setTask(int index, const Task& task) {
        if (index >= 0 && index < _counts) {
            _tasks[index] = task;
        }
        else {
            throw std::out_of_range("ERROR: index out of range!");
        }
    }

    void submitAnswer(int index, int answer) {
        if (index < 0 || index >= _counts) {
            throw std::out_of_range("ERROR: index out of range!");
        }

        _user_answers[index] = answer;

        if (_tasks[index].answer == answer) {
            _correct_count++;
        }
    }

    char calculateMark() const {
        double percentage = (static_cast<double>(_correct_count) / _counts) * 100.0;
        if (percentage >= 90.0) {
            return 'A';
        }
        if (percentage >= 80.0) {
            return 'B';
        }
        if (percentage >= 70.0) {
            return 'C';
        }
        if (percentage >= 60.0) {
            return 'D';
        }
        return 'F';
    }

    void run() {
        std::cout << "ћатематический тест на " << _counts << " вопросов:" << std::endl;
        for (int i = 0; i < _counts; ++i) {
            std::cout << "¬опрос " << (i + 1) << ":" << std::endl
                << _tasks[i].num_1 << " " << _tasks[i].operation << " " << _tasks[i].num_2 << " = ";

            int ans; 
            std::cin >> ans;

            submitAnswer(i, ans);
        }
        std::cout << std::endl << "“ест завершен!" << std::endl << std::endl;
        show_statistics();
    }

    void show_statistics() const {
        const int col_width = 9;

        //1: номера вопросов
        std::cout << "|" << std::setw(12) << "No" << " |";
        for (int i = 0; i < _counts; ++i) {
            std::cout << std::setw(col_width) << (i + 1) << " |";
        }
        std::cout << "\n";

        //разделитель динамической длины
        int total_width = 15 + (col_width + 2) * _counts;
        std::cout << "+" << std::string(total_width - 2, '-') << "+\n";

        //2: вопросы
        std::cout << "|" << std::setw(12) << "Question" << " |";
        for (int i = 0; i < _counts; ++i) {
            std::string q_str = std::to_string(_tasks[i].num_1) + " " +
                _tasks[i].operation + " " +
                std::to_string(_tasks[i].num_2);
            std::cout << std::setw(col_width) << q_str << " |";
        }
        std::cout << "\n";

        //3: ответы правильные
        std::cout << "|" << std::setw(12) << "True Answer" << " |";
        for (int i = 0; i < _counts; ++i) {
            std::cout << std::setw(col_width) << _tasks[i].answer << " |";
        }
        std::cout << std::endl;

        //4: ответы пользовател€
        std::cout << "|" << std::setw(12) << "Your Answer" << " |";
        for (int i = 0; i < _counts; ++i) {
            std::cout << std::setw(col_width) << _user_answers[i] << " |";
        }
        std::cout << "\n";

        //5: результат
        std::cout << "|" << std::setw(12) << "Result" << " |";
        for (int i = 0; i < _counts; ++i) {
            char res = (_tasks[i].answer == _user_answers[i]) ? '+' : '-';
            std::cout << std::setw(col_width) << res << " |";
        }
        std::cout << std::endl << std::endl;

        std::cout << "Total Result: " << _correct_count << " / " << _counts
            << " (mark: " << calculateMark() << ")" << std::endl;
    }
};
