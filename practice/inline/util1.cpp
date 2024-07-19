#include "util1.h"
#include "util2.h"
#include "form.h"

namespace util1{
    void print_shift(){
        std::cout << "SHIFT : " << SHIFT << ", at : " << &SHIFT << '\n';
        newline();
    }
    void print_distance(){
        std::cout << "DISTANCE : " << DISTANCE << ", at : " << &DISTANCE << '\n';
        newline();
    }
}