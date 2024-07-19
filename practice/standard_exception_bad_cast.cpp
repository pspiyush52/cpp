#include <iostream>
#include <exception>

class Base{
    public:
        Base() = default;
        virtual int get() const { return base_data; }
    
    protected:
        int base_data{};
};
class Derived : public Base{
    public:
        Derived() = default;
        int get() const override { return derived_data; }
    
    protected:
        int derived_data{};
};

int main(void)
{
    Base b;
    try{
        auto& d = dynamic_cast<Derived&>(b);
        std::cout << "Data: " << d.get();
    }
    catch(std::bad_cast& ex){
        std::cout << "Error: Bad casting, " << ex.what() << '\n';
    }

    return 0;
}