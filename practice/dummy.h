#ifndef __DUMMY_H
#define __DUMMY_H

#include <iostream>

class Dummy {
    Dummy(int x): n{x} { ++count; }
    public:
        Dummy(): Dummy(count + 1) {
            std::cout << "Dummy::Dummy@" << this << '\n';
        }
        Dummy(const Dummy& s): Dummy(s.n) {
            std::cout << "Dummy::Dummy(const Dummy&)\n";
        }
        Dummy(Dummy&& s): Dummy(s.n) {
            std::cout << "Dummy::Dummy(Dummy&&)\n";
        }
        Dummy& operator=(const Dummy& s){
            std::cout << "Dummy::copy_assign\n";
            this->n = s.n;
            return *this;
        }
        Dummy& operator=(Dummy&& s) {
            std::cout << "Dummy::move_assign\n";
            this->n = s.n;
            return *this;
        }
        static int getCount() {
            return count;
        }
        friend std::ostream& operator<<(std::ostream& out, const Dummy& d) {
            out << "<Dummy@" << &d << " (" << d.n << ")>";
            return out;
        }
        ~Dummy(){
            std::cout << "Dummy::~Dummy@" << this << '\n';
        }
    private:
        int n;
        inline static int count{};
};


#endif  // __DUMMY_H