#pragma once

#include <iostream>
#include <numeric>
#include <compare>
#include <cstdint>

class Rational {
public:
    // Конструкторы
    Rational() : numerator_(0), denominator_(1) {}

    Rational(int numerator) : numerator_(numerator), denominator_(1) {}

    Rational(int numerator, int denominator)
        : numerator_(numerator), denominator_(denominator) {
        if (denominator == 0) {
            throw std::invalid_argument("Denominator cannot be zero");
        }
        Reduction();
    }

    Rational(const Rational& other) = default;

    // Оператор присваивания
    Rational& operator=(const Rational& other) = default;

    // Методы доступа
    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    // Метод для получения обратной дроби
    Rational Inv() const {
        if (numerator_ == 0) {
            throw std::invalid_argument("Cannot invert zero");
        }
        return Rational(denominator_, numerator_);
    }

    // Унарные операторы
    Rational operator+() const {
        return *this;
    }

    Rational operator-() const {
        return Rational(-numerator_, denominator_);
    }

    // Присваивающие арифметические операторы
    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - other.numerator_ * denominator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        *this *= other.Inv();
        return *this;
    }

    // Бинарные арифметические операторы
    Rational operator+(const Rational& other) const {
        Rational result = *this;
        result += other;
        return result;
    }

    Rational operator-(const Rational& other) const {
        Rational result = *this;
        result -= other;
        return result;
    }

    Rational operator*(const Rational& other) const {
        Rational result = *this;
        result *= other;
        return result;
    }

    Rational operator/(const Rational& other) const {
        Rational result = *this;
        result /= other;
        return result;
    }

    // Операторы сравнения
    bool operator==(const Rational& other) const = default;

    auto operator<=>(const Rational& other) const {
        // Используем long long для избежания переполнения
        long long left_num = static_cast<long long>(numerator_) * other.denominator_;
        long long right_num = static_cast<long long>(other.numerator_) * denominator_;
        return left_num <=> right_num;
    }

private:
    int numerator_;
    int denominator_;

    // Приведение дроби к несократимому виду
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;

        // Нормализация нуля
        if (numerator_ == 0) {
            denominator_ = 1;
        }
    }
};

// Операторы ввода/вывода
inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.GetNumerator();
    if (r.GetDenominator() != 1) {
        os << " / " << r.GetDenominator();
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int numerator = 0;
    int denominator = 1;
    char slash = '\0';

    // Пытаемся прочитать числитель
    if (!(is >> numerator)) {
        is.setstate(std::ios::failbit);
        return is;
    }

    // Пропускаем возможные пробелы
    while (is.peek() == ' ') {
        is.get();
    }

    // Проверяем, есть ли знак дроби
    if (is.peek() == '/') {
        is >> slash; // Читаем '/'

        // Пропускаем возможные пробелы после '/'
        while (is.peek() == ' ') {
            is.get();
        }

        if (!(is >> denominator) || denominator == 0) {
            is.setstate(std::ios::failbit);
            return is;
        }
    }

    r = Rational(numerator, denominator);
    return is;
}
