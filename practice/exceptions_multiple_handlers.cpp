#include "utils.h"
void f1();
void f2();
void f3();
void ext();

int main(void)
{
    cout << "-------------START-------------\n";
    try{
        f1();
    }catch(int ex){
        cout << "Exception handled in main()\n";
    }
    cout << "--------------END--------------\n";
    return 0;
}

void f1(){
    cout << "Starting f1()\n";
    try{
        f2();
    }catch(int ex){
        cout << "Exception handled in f1()\n";
    }
    cout << "Ending f1()\n";
}
void f2(){
    cout << "Starting f2()\n";
    try{
        f3();
    }catch(int ex){
        cout << "Exception handled in f2()\n";
    }
    cout << "Ending f2()\n";
}
void f3(){
    cout << "Starting f3()\n";
    try{
        ext();
    }catch(int ex){
        cout << "Exception handled in f3()\n";
    }
    cout << "Ending f3()\n";
}
void ext(){
    cout << "Starting problematic ext()\n";
    throw 1;
    cout << "Ending ext()\n";
}