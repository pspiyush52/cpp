#ifndef __OPERATOR_OVERLOADING_H
#define __OPERATOR_OVERLOADING_H

#include <iostream>

class Complex {
    public:
        Complex();
        Complex(double Real, double Imaginary);
        Complex(double x);
        Complex(const Complex& num);
        Complex operator+(const Complex& cnum) const;
        friend inline Complex operator-(const Complex& left, const Complex& right);
        Complex& operator++();
        Complex operator++(int);
        Complex& operator--();
        Complex operator--(int);
        friend inline std::ostream& operator<<(std::ostream& output, const Complex& cnum);
    private:
        double real;
        double imaginary;
};

Complex::Complex():
    Complex(0, 0){}

Complex::Complex(double x):
    Complex(x, x){}

Complex::Complex(double Real, double Imaginary):
    real(Real), imaginary(Imaginary){}

Complex::Complex(const Complex& cnum):
    Complex(cnum.real, cnum.imaginary){}

Complex Complex::operator+(const Complex& cnum) const {
    return Complex{real + cnum.real, imaginary + cnum.imaginary};
}

inline Complex operator-(const Complex& left, const Complex& right){
    return Complex{left.real - right.real, left.imaginary - right.imaginary};
}

Complex& Complex::operator++(){
    real++; imaginary++;
    return *this;
}

Complex Complex::operator++(int){
    Complex tmp{*this};
    ++(*this);  // Re-using the prefix increment operator defined above
    return tmp;
}

Complex& Complex::operator--(){
    real--; imaginary--;
    return *this;
}

Complex Complex::operator--(int){
    Complex tmp{*this};
    --(*this);  // Re-using the prefix decrement operator defined above
    return tmp;
}

inline std::ostream& operator<<(std::ostream& output, const Complex& cnum){
    output << cnum.real;
    if (cnum.imaginary < 0)
        output << " - " << (-cnum.imaginary) << 'i';
    else
        output<< " + " << cnum.imaginary << 'i';
    return output;
}

#endif  // __OPERATOR_OVERLOADING_H