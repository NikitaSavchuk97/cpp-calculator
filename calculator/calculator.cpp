#include "calculator.h"
#include <cmath>
#include <string>

using namespace std::literals;

void Calculator::Set(Number n) {
    current_number_ = n;
}

Number Calculator::GetNumber() const {
    return current_number_;
}

void Calculator::Add(Number n) {
    current_number_ += n;
}

void Calculator::Sub(Number n) {
    current_number_ -= n;
}

void Calculator::Div(Number n) {
    current_number_ /= n;
}

void Calculator::Mul(Number n) {
    current_number_ *= n;
}

void Calculator::Pow(Number n) {
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