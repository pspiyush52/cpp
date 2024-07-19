#include "b.h"
#include "a.h"
#include <iostream>

B::B(int num):
    data(num){std::cout << "B: constructor...\n";}

B::B(const B& obj):
    data(obj.data){std::cout << "B: copy B...\n";}

B::B(const A& obj):
    data(obj.get()){std::cout << "B: constructor taking A...\n";}

B& B::operator=(const A& obj){
    data = obj.get();
    std::cout << "B: assignment...\n";
    return *this;
}
/*
B::operator A(){
    std::cout << "B: cast to A...\n";
    return A(data);
}
*/
int B::get() const {
    return data;
}