#include <iostream>
class base{
    public:
        int b_public{-12};
        base() = default;
        base(int x, int y, int z) : b_public(x), b_protected(y), b_private(z){}
    protected:
        int b_protected{77};
        int get_b_protected() const { return b_protected; }
    private: int b_private{};
};
class first : private base{
    public:
        int f_public;
    protected:
        /*
         * Writing using base::get_b_protected in the protected section of the
         * first class changes the scope of get_b_protected from private to
         * protected.
         * Without this, get_b_protected will become a private member of the
         * first class making it not accessible to any classes which inherit
         * from first i.e., the print_b_protected member function in the class
         * second will not work.
         */
        using base::get_b_protected;
    private: int f_private{};
};
class second : public first{
    public:
        void print_b_protected(){
            /*
             * get_b_protected can be used here since it's scope was changed
             * from private to protected in first and so it is protected in
             * this class as well due to public inheritance.
             */
            std::cout << "b_protected: " << get_b_protected() << '\n';
        }
};
int main(void)
{
    first f;  std::cout << "f.f_public: " << f.f_public << '\n';
    // f.get_b_protected();  // protected within first
    second s;
    // s.get_b_protected();  // protected within second
    s.print_b_protected();
    return 0;
}