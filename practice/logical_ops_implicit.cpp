#include <iostream>
#include <iomanip>
#include <type_traits>
#include <utility>

template<typename T>
concept Numeric = std::is_convertible_v<T, double> &&
requires (T a){
    requires sizeof(a) >= 4;
};

class Number {
    public:
        explicit Number(int num);
        /*
            If we want the number objects to be comparable to numbers of
            fundamental numeric types then we have to overload the operator
            functions for 3 combinations of operands:
                1. fundamental_type (operand) Number_obj
                2. Number_obj (operand) fundamental_type
                3. Number_obj (operand) Number_obj
            
            So three overloaded functions will have to be written for each
            operand and not even std::rel_ops can help us in this case because
            it contains templates where both the operands for an operator are
            of the same type and we are dealing with different types here.

            Following the above method we will end up with 18 logical operator
            functions. This can be resolved by using the three way comparison
            operator '<=>'.
        */
        // Functions for the '<' operator
        template<Numeric T>
        friend bool operator<(const T& lhs, const Number& rhs);
        template<Numeric T>
        friend bool operator<(const Number& lhs, const T& rhs);
        friend bool operator<(const Number& lhs, const Number& rhs);

        // Functions for the '>' operator
        template<Numeric T>
        friend bool operator>(const T& lhs, const Number& rhs);
        template<Numeric T>
        friend bool operator>(const Number& lhs, const T& rhs);
        /*
            We can use rel_ops namespace to automatically define the operator
            function for '>' where both the operands are of type Number since
            the rel_ops templates work for operators where both the operands
            are of the same type.
            So, the following is not needed but rest two overloads still have
            to be defined.
        */
        friend bool operator>(const Number& lhs, const Number& rhs);
        /*
            We still have to define the above function because we have defined
            the double type conversion operator below and so the call to the <
            operator function will become ambiguous since the builtin function
            which takes two double parameters and compares them will also fit
            the call and so will the template from rel_ops. To resolve this
            amibguity we have to define our own function for < operator which
            compares two Number objects.
        */
        operator double(){
            return static_cast<double>(num);
        }

    private:
        int num;
};
Number::Number(int Num):
    num(Num){}

template<Numeric T>
void fun(const T& a){
    std::cout <<"fun called.\n";
}

int main(void)
{
    using namespace std::rel_ops;
    Number x{42}, y{31};
    std::cout << "x > y : " << std::boolalpha << (x > y) << '\n';
    fun(x);
    return 0;
}

template<Numeric T>
bool operator<(const T& lhs, const Number& rhs){
    std::cout << "< called...\n";
    return (lhs < rhs.num);
}

template<Numeric T>
bool operator<(const Number& lhs, const T& rhs){
    return (lhs.num < rhs);
}

bool operator<(const Number& lhs, const Number& rhs){
    return (lhs.num < rhs.num);
}

template<Numeric T>
bool operator>(const T& lhs, const Number& rhs){
    return (lhs > rhs.num);
}

template<Numeric T>
bool operator>(const Number& lhs, const T& rhs){
    return (lhs.num > rhs);
}

bool operator>(const Number& lhs, const Number& rhs){
    return (lhs.num > rhs.num);
}