#include "math_test.h"
#include <clocale>

int main() {
    setlocale(LC_ALL, "rus");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    std::cout << "Смешанный тест\n\n";
    MathTest mixedTest(5, -10, 50);

    mixedTest.run();

    std::cout << "\nТест только на умножение\n\n";
    MathTest multiplyTest(3, 1, 20, '*');

    multiplyTest.run();

    return 0;
}

