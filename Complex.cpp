// matanayabarzilay@gmail.com

#include "Complex.hpp"
#include <cmath>
#include <sstream>

Complex::Complex(const double& re, const double& im) : _re(re), _im(im) {}

// Getters
// Return the real part of the complex number
double Complex::re() const {
    return _re;
}

// Return the imaginary part of the complex number
double Complex::im() const {
    return _im;
}

// Logical NOT: checks if both the real and imaginary parts are zero
bool Complex::operator!() const {
    return _re == 0 && _im == 0;
}

// Unary minus - negates the real and imaginary parts
Complex Complex::operator-() const {
    return Complex(-_re, -_im);
}

// Plus equals - adds the given complex number to the current one
Complex& Complex::operator+=(const Complex& other) {
    _re += other._re;
    _im += other._im;
    return *this;
}

// Minus equals - subtracts the given complex number from the current one
Complex& Complex::operator-=(const Complex& other) {
    _re -= other._re;
    _im -= other._im;
    return *this;
}

// Multiply equals - multiplies the current complex number by the given one
Complex& Complex::operator*=(const Complex& other) {
    double new_re = _re * other._re - _im * other._im;
    double new_im = _re * other._im + _im * other._re;
    _re = new_re;
    _im = new_im;
    return *this;
}

// Prefix increment - increments the real part
Complex& Complex::operator++() {
    _re++;
    return *this;
}

// Postfix increment - increments the real part and returns a copy of the original number
Complex Complex::operator++(int) {
    Complex copy = *this;
    _re++;
    return copy;
}

// Binary minus - subtracts two complex numbers
Complex Complex::operator-(const Complex& other) {
    return Complex(_re - other._re, _im - other._im);
}

// Binary plus - adds two complex numbers
Complex Complex::operator+(const Complex& other) {
    return Complex(_re + other._re, _im + other._im);
}

// Multiply - multiplies two complex numbers
Complex Complex::operator*(const Complex& other) {
    return Complex(_re * other._re - _im * other._im,
                   _re * other._im + _im * other._re);
}

// Hypotenuse comparison - compares the magnitudes of two complex numbers
bool Complex::operator<(const Complex& other) const {
    return std::hypot(_re, _im) < std::hypot(other._re, other._im);
}

// Equality comparison - checks if two complex numbers are equal
bool Complex::operator==(const Complex& other) const {
    return this->im() == other.im() && this->re() == other.re();
}

// Greater than comparison - checks if the magnitude of one complex number is greater than another
bool Complex::operator>(const Complex& other) const {
    return !(*this < other) && !(*this == other);
}

// Inequality comparison - checks if two complex numbers are not equal
bool Complex::operator!=(const Complex& other) const {
    return !(*this == other);
}

// Stream output operator - prints the complex number in the form "a+bi" or "a-bi"
std::ostream& operator<<(std::ostream& output, const Complex& c) {
    output << c._re << (c._im >= 0 ? '+' : '-') << std::abs(c._im) << 'i';
    return output;
}

// Stream input operator - reads a complex number from the input in the form "a+bi" or "a-bi"
std::istream& operator>>(std::istream& input, Complex& c) {
    double re = 0, im = 0;
    char ch1, ch2;

    if (input >> re >> ch1 >> im >> ch2 && ch2 == 'i') {
        if (ch1 == '+') {
            c._re = re;
            c._im = im;
        } else if (ch1 == '-') {
            c._re = re;
            c._im = -im;
        } else {
            input.setstate(std::ios::failbit); // Invalid character between real and imaginary parts
        }
    } else {
        input.setstate(std::ios::failbit); // Invalid format (missing 'i' character)
    }

    return input;
}
