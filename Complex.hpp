// matanayabarzilay@gmail.com

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <iostream>

class Complex {
private:
    double _re, _im;

public:
    // Constructor with default arguments
    Complex(const double& re = 0, const double& im = 0);

    // Getters
    double re() const;
    double im() const;

    // Unary operators
    bool operator!() const;
    Complex operator-() const;

    // Compound assignment operators
    Complex& operator+=(const Complex& other);
    Complex& operator-=(const Complex& other);
    Complex& operator*=(const Complex& other);

    // Increment operators
    Complex& operator++();      // Prefix
    Complex operator++(int);    // Postfix

    // Binary arithmetic operators
    Complex operator-(const Complex& other);
    Complex operator+(const Complex& other);
    Complex operator*(const Complex& other);

    // Comparison operators
    bool operator<(const Complex& other) const;
    bool operator==(const Complex& other) const;  // Mark as const
    bool operator>(const Complex& other) const;
    bool operator!=(const Complex& other) const;  // Mark as const

    // Input/Output operators
    friend std::ostream& operator<<(std::ostream& output, const Complex& c);
    friend std::istream& operator>>(std::istream& input, Complex& c);
};

#endif // COMPLEX_HPP
