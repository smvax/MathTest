#pragma once
#include <cstdlib>
#include <ctime>
#include <cmath>

struct Task {
	int num_1;
	int num_2;
	char operation;
	double answer;

	double calculateAnswer() {
		double ans = 0;
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
			ans = static_cast<double>(num_1) / num_2;
			break;
		}
		return ans;
	}

    Task(int min_val = -100, int max_val = 100) {
        int range = max_val - min_val + 1;
        num_1 = (std::rand() % range) + min_val;
        num_2 = (std::rand() % range) + min_val;

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

        if (operation == '/' && num_2 == 0) {
            if (max_val >= 1) {
                num_2 = 1;
            }
            else if (min_val <= -1) {
                num_2 = -1;
            }
            else {
                operation = '+';
            }
        }

        answer = calculateAnswer();
    }

	Task(int n1, int n2, char op) : num_1(n1), num_2(n2), operation(op) {
		answer = calculateAnswer();
	}
};

class MathTest {

};