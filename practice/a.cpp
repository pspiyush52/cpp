#include "a.h"
#include "b.h"
#include <iostream>

A::A(int num):
    data(num){std::cout << "A: constructor...\n";}

A::A(const A& obj):
    data(obj.data){std::cout << "A: copy A...\n";}

A::A(const B& obj):
    data(obj.get()){std::cout << "A: constructor taking B...\n";}

A& A::operator=(const B& obj){
    data = obj.get();
    std::cout << "A: assignment...\n";
    return *this;
}

A::operator B(){
    std::cout << "A: cast to B...\n";
    return B(data);
}

int A::get() const {
    return data;
}