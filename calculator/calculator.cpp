#include "calculator.h"
#include <string>
#include <cmath>

bool ReadNumber(Number& result) {
    std::cin >> result;
    if (std::cin.fail()) {
        std::cerr << "Error: Numeric operand expected";
        return false;
    }
    return true;
}

bool RunCalculatorCycle() {
    Number current_value;
    Number memory_value = 0;
    bool memory_initialized = false;
    
    if (!ReadNumber(current_value)) {
        return false;
    }
    
    std::string command;
    
    while (std::cin >> command) {
        if (command == "+") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value += operand;
        }
        else if (command == "-") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value -= operand;
        }
        else if (command == "*") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value *= operand;
        }
        else if (command == "/") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value /= operand;
        }
        else if (command == "**") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value = std::pow(current_value, operand);
        }
        else if (command == ":") {
            Number operand;
            if (!ReadNumber(operand)) return false;
            current_value = operand;
        }
        else if (command == "c") {
            current_value = 0;
        }
        else if (command == "=") {
            std::cout << current_value << std::endl;
        }
        else if (command == "s") {
            memory_value = current_value;
            memory_initialized = true;
        }
        else if (command == "l") {
            if (!memory_initialized) {
                std::cerr << "Error: Memory is empty";
                return false;
            }
            current_value = memory_value;
        }
        else if (command == "q") {
            return true;
        }
        else {
            std::cerr << "Error: Unknown token " << command;
            return false;
        }
    }
    
    return true;
}