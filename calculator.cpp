#include "calculator.h"
#include <cmath>
#include <string>

using namespace std::literals;

double Calculator::GetNumber() const {
    return current_number_;
}

void Calculator::Set(double n) {
    current_number_ = n;
}

void Calculator::Add(double n) {
    current_number_ += n;
}

void Calculator::Sub(double n) {
    current_number_ -= n;
}

void Calculator::Div(double n) {
    current_number_ /= n;
}

void Calculator::Mul(double n) {
    current_number_ *= n;
}

void Calculator::Pow(double n) {
    current_number_ = std::pow(current_number_, n);
}

void Calculator::Save() {
    memory_number_ = current_number_;
    has_memory_ = true;
}

void Calculator::Load() {
    if (has_memory_) {
        current_number_ = memory_number_;
    }
}

bool Calculator::HasMem() const {
    return has_memory_;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(current_number_);
}
