#include "calculator.h"
#include <iostream>
#include <string>

using namespace std::literals;

constexpr int CALCULATION_ERROR = 1;

bool ReadNumber(Number& result) {
    std::cin >> result;
    if (std::cin.fail()) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number init_number;
    if (!ReadNumber(init_number)) {
        return false;
    }

    Calculator calc;
    calc.Set(init_number);

    std::string token;
    while(std::cin >> token) {
        Number right;
        if (token == "+"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Add(right);
        } else if (token == "-"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Sub(right);
        } else if (token == "*"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Mul(right);
        } else if (token == "/"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Div(right);
        } else if (token == "**"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Pow(right);
        } else if (token == "s"s) {
            calc.Save();
        } else if (token == "l"s) {
            if (!calc.HasMem()) {
                std::cerr << "Error: Memory is empty"s << std::endl;
                return false;
            }
            calc.Load();
        } else if (token == "="s) {
            std::cout << calc.GetNumberRepr() << std::endl;
        } else if (token == "c"s) {
            calc.Set(0);
        } else if (token == "n"s) {
            calc.Set(-calc.GetNumber());
        } else if (token == ":"s) {
            if (!ReadNumber(right)) {
                return false;
            }
            calc.Set(right);
        } else if (token == "q"s) {
            return true;
        } else {
            std::cerr << "Error: Unknown token "s << token << std::endl;
            return false;
        }
    }
    return false;
}

int main() {
    std::cin >> std::ws;

    if (!RunCalculatorCycle()) {
        std::cerr << "Program failed! Error code: " << CALCULATION_ERROR << std::endl;
        return CALCULATION_ERROR;
    }
    return 0;
}