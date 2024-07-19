#include "util2.h"
#include "util1.h"
#include "form.h"

namespace util2{
    void print_distance(){
        std::cout << "DISTANCE : " << DISTANCE << ", at : " << &DISTANCE << '\n';
        newline();
    }
    void print_shift(){
        std::cout << "SHIFT : " << SHIFT << ", at : " << &SHIFT << '\n';
        newline();
    }
}