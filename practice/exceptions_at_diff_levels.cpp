/*
 * If an unhandled exception occurs in the program then the exception
 * propagates to the scope from where the function was called until it finally
 * reaches the origin call which resulted in the exception being thrown or it
 * encounters a catch block which handles the exception.
 */
#include "utils.h"

void f1(int);
void f2(int);
void f3(int);

int main(void)
{
    try{
        f1(101); // exception at f2()
        // f1(7);   // exception at f3()
        // f1(2);      // exception at f1()
    }
    catch(int ex){
        cout << "Exception occurred at f(" << ex << ")\n";
    }
    return 0;
}

void f3(int z){
    cout << "Starting f3()\n";
    if (z < 10)
        throw 3;
    sep;
    cout << "Ending f3()\n";
}

void f2(int y){
    cout << "Starting f2()\n";
    if (y > 100)
        throw 2;
    f3(y);
    cout << "Ending f2()\n";
}

void f1(int x){
    sep;
    cout << "Starting f1()\n";
    if (x < 5)
        throw 1;
    f2(x);
    cout << "Ending f1()\n";
    sep;
}