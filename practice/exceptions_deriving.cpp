#include <iostream>
#include <exception>
#include <string>

class DivideByZeroError : public std::exception{
    public:
        DivideByZeroError(int num, int denom):
            numerator(num), denominator(denom){}
        const char* what() const noexcept override{
            // return "Divide by zero error";
            return (
                std::string{"DivideByZeroError: Dividing "} +
                    std::to_string(numerator) + " by " +
                        std::to_string(denominator)
            ).c_str();
        }
        int get_num() const { return numerator; }
        int get_denom() const { return denominator; }
    
    private:
        int numerator;
        int denominator;
};

double divide(int, int);
int main(void)
{
    try{
        divide(3, 0);
    }
    catch(std::exception& ex){
        std::cout << "Exception occurred\n  " << ex.what() << '\n';
        /*
         * Attempting to cast std::exception object to DivideByZeroError
         * exception object. If the cast is succesful it means the
         * exception thrown is of DivideByZeroError type because
         * otherwise the cast would fail.
         * 
         * After the cast we can provide further details about the
         * exception which can only be accessed via DivideByZeroError
         * object or pointer.
         */
        /*DivideByZeroError* d_err = dynamic_cast<DivideByZeroError*>(&ex);
        if (d_err)
        {
            std::cout << "  dividing " << d_err->get_num() << " by "
                << d_err->get_denom() << '\n';
        }*/
    }
    return 0;
}

double divide(int a, int b){
    if(!b)
        throw DivideByZeroError{a, b};
    return static_cast<double>(a) / b;
}