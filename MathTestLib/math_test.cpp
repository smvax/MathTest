#include "math_test.h"

Task::Task(int in1, int in2, char op, bool is_random) {
    if (op != '\0' && op != '+' && op != '-' && op != '*' && op != '/') {
        throw std::invalid_argument("ERROR: operation char is not valid!");
    }
    if (is_random && in1 >= in2) {
        throw std::invalid_argument("ERROR: range is not valid! Min must be < max!");
    }

    if (!is_random) {
        if (op == '/') {
            if (in2 == 0) {
                throw std::invalid_argument("ERROR: division by zero!");
            }
            if ((in1 / in2) * in2 != in1) {
                throw std::invalid_argument("ERROR: (num1 / num2) is not integer!");
            }
        }
        num_1 = in1;
        num_2 = in2;
        operation = op;
    }
    else {
        if (op == '\0') {
            generateRandomOperation();
        }
        else {
            operation = op;
        }

        if (operation == '/') {
            generateRandomDivision(in1, in2);
        }
        else {
            int range = in2 - in1 + 1;
            num_1 = (std::rand() % range) + in1;
            num_2 = (std::rand() % range) + in1;
        }
    }
    answer = calculateAnswer();
}

int Task::calculateAnswer() noexcept {
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
    case '/':
        ans = num_1 / num_2;
        break;
    }
    return ans;
}

void Task::generateRandomDivision(int n1, int n2) noexcept {
    int root_neg = (n1 < 0) ? static_cast<int>(std::sqrt(std::abs(n1))) : 0;
    int root_pos = (n2 > 0) ? static_cast<int>(std::sqrt(n2)) : 0;

    int sub_min = -root_neg;
    int sub_max = root_pos;
    int sub_range = sub_max - sub_min + 1;

    int range = n2 - n1 + 1;

    do {
        num_2 = (std::rand() % sub_range) + sub_min;
    } while (num_2 == 0);

    int target_quotient = (std::rand() % sub_range) + sub_min;

    num_1 = num_2 * target_quotient;
}

void Task::generateRandomOperation() noexcept {
    int op_rander = std::rand() % 4;
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
    case 3:
        operation = '/';
        break;
    }
}

MathTest::MathTest(int count, int min_val, int max_val, char op) : _counts(count), _correct_count(0) {
    if (count <= 0) {
        throw std::invalid_argument("ERROR: Task count must be bigger than 0!");
    }
    if (op != '-' && op != '+' && op != '*' && op != '/' && op != '\0') {
        throw std::invalid_argument("ERROR: operation char is not valid!");
    }
    _tasks = new Task[_counts];
    _user_answers = new int[_counts] {0};
    if (op == '\0') {
        for (int i = 0; i < _counts; ++i) {
            _tasks[i] = Task(min_val, max_val, op, true);
        }
    }
    else {
        for (int i = 0; i < _counts; ++i) {
            _tasks[i] = Task(min_val, max_val, op, false);
        }
    }
}

MathTest::~MathTest() {
    delete[] _tasks;
    delete[] _user_answers;
}

void MathTest::setTask(int index, const Task& task) {
    if (index >= 0 && index < _counts) {
        _tasks[index] = task;
    }
    else {
        throw std::out_of_range("ERROR: index out of range!");
    }
}

void MathTest::submitAnswer(int index, int answer) noexcept {
    _user_answers[index] = answer;
    if (_tasks[index].answer == answer) {
        _correct_count++;
    }
}

char MathTest::calculateMark() const noexcept {
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

void MathTest::run() noexcept {
    std::cout << "Math test with " << _counts << " questions:" << std::endl;
    for (int i = 0; i < _counts; ++i) {
        std::cout << "Question " << (i + 1) << ":" << std::endl
            << _tasks[i].num_1 << " " << static_cast<char>(_tasks[i].operation) << " " << _tasks[i].num_2 << " = ";

        int ans;
        std::cin >> ans;

        submitAnswer(i, ans);
    }
    std::cout << std::endl << "Test complete!" << std::endl << std::endl;
    show_statistics();
}

void MathTest::show_statistics() const noexcept {
    const int col_width = 9;

    //1: question number
    std::cout << "|" << std::setw(12) << "No" << " |";
    for (int i = 0; i < _counts; ++i) {
        std::cout << std::setw(col_width) << (i + 1) << " |";
    }
    std::cout << "\n";

    //divider
    int total_width = 15 + (col_width + 2) * _counts;
    std::cout << "+" << std::string(total_width - 2, '-') << "+\n";

    //2: question
    std::cout << "|" << std::setw(12) << "Question" << " |";
    for (int i = 0; i < _counts; ++i) {
        std::string q_str = std::to_string(_tasks[i].num_1) + " " +
            _tasks[i].operation + " " +
            std::to_string(_tasks[i].num_2);
        std::cout << std::setw(col_width) << q_str << " |";
    }
    std::cout << "\n";

    //3: correct answers
    std::cout << "|" << std::setw(12) << "True Answer" << " |";
    for (int i = 0; i < _counts; ++i) {
        std::cout << std::setw(col_width) << _tasks[i].answer << " |";
    }
    std::cout << std::endl;

    //4: user answers
    std::cout << "|" << std::setw(12) << "Your Answer" << " |";
    for (int i = 0; i < _counts; ++i) {
        std::cout << std::setw(col_width) << _user_answers[i] << " |";
    }
    std::cout << "\n";

    //5: result
    std::cout << "|" << std::setw(12) << "Result" << " |";
    for (int i = 0; i < _counts; ++i) {
        char res = (_tasks[i].answer == _user_answers[i]) ? '+' : '-';
        std::cout << std::setw(col_width) << res << " |";
    }
    std::cout << std::endl << std::endl;

    std::cout << "Total Result: " << _correct_count << " / " << _counts
        << " (mark: " << calculateMark() << ")" << std::endl;
}