#pragma once

#include <string>

class Calculator {
public:
    double GetNumber() const;
    void Set(double n);
    void Add(double n);
    void Sub(double n);
    void Div(double n);
    void Mul(double n);
    void Pow(double n);
    void Save();
    void Load();
    bool HasMem() const;
    std::string GetNumberRepr() const;

private:
    double current_number_ = 0.0;
    double memory_number_ = 0.0;
    bool has_memory_ = false;
};
