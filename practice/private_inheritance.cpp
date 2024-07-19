#include <iostream>

class base{
    public: base(int num) : b_data(num){}
    protected: int b_protected{1};
    private: int b_data;
};
class derived : private base{
    public:
        derived(int base_num, int derived_num) : base(base_num), d_data(derived_num){}
        void print() { std::cout << b_protected; }
    protected: int d_protected{12};
    private: int d_data;
};
class derived2 : public derived{
    public:
        derived2(int base_num, int derived_num) : derived(base_num, derived_num), d2_data(derived_num){}
        void print(){ std::cout << d_protected; }
    private: int d2_data;
};

int main(void)
{
    derived2 obj{3, 5};
    std::cout << "Protected member of the derived class accessed from the derived2 class: "; obj.print();
    std::cout << "\nProtected member of the base class accessed from the derived class: "; obj.derived::print();
    return 0;
}