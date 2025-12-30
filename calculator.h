#pragma once

#include <string>
#include <optional>
#include <cmath>
#include <type_traits>
#include "rational.h"
#include "pow.h"

using Error = std::string;

// Объявление шаблонной функции Pow
template<class Number>
Number PowFunction(Number base, Number exponent) {
    if constexpr (std::is_floating_point_v<Number>) {
        return std::pow(base, exponent);
    } else if constexpr (std::is_same_v<Number, Rational>) {
        return ::Pow(base, exponent);
    } else {
        return IntegerPow(base, exponent);
    }
}

template<class Number>
class Calculator
{
public:
    Calculator() = default;

    Number GetNumber() const {
        return current_number_;
    }

    void Set(Number n) {
        current_number_ = n;
    }

    std::optional<Error> Add(Number n) {
        current_number_ += n;
        return std::nullopt;
    }

    std::optional<Error> Sub(Number n) {
        current_number_ -= n;
        return std::nullopt;
    }

    std::optional<Error> Mul(Number n) {
        current_number_ *= n;
        return std::nullopt;
    }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n == Number{0}) {
                return "Division by zero";
            }
        }
        current_number_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            // Проверка 0^0
            if (current_number_ == Number{0} && n == Number{0}) {
                return "Zero power to zero";
            }

            // Для целых чисел проверка отрицательной степени
            if constexpr (std::is_integral_v<Number>) {
                if (n < Number{0}) {
                    return "Integer negative power";
                }
            }

            // Для Rational проверка дробной степени
            if constexpr (std::is_same_v<Number, Rational>) {
                if (n.GetDenominator() != 1) {
                    return "Fractional power is not supported";
                }
            }
        }

        // Вычисление степени для всех типов
        current_number_ = PowFunction<Number>(current_number_, n);
        return std::nullopt;
    }

    void Save() {
        mem_ = current_number_;
    }

    void Load() {
        if (mem_.has_value()) {
            current_number_ = mem_.value();
        }
    }

    bool GetHasMem() const {
        return mem_.has_value();
    }

private:
    Number current_number_ = Number{};
    std::optional<Number> mem_ = std::nullopt;
};
