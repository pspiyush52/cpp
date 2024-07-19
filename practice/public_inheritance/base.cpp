#include "base.h"

Base::Base(int x) : b_public(x), b_protected(x), b_private(x){}
Base::Base(int x, int y, int z) : b_public(x), b_protected(y), b_private(z){}

// Getters
int Base::get_public() const { return b_public; }
int Base::get_protected() const { return b_protected; }
int Base::get_private() const { return b_private; }

// Setters
void Base::set_public(int num) { b_public = num; }
void Base::set_protected(int num) { b_protected = num; }
void Base::set_private(int num) { b_private = num; }

std::ostream& operator<<(std::ostream& output, const Base& obj){
    output << "Base[" << obj.b_public << ", " << obj.b_protected
    << ", " << obj.b_private << ']';
    return output;
}