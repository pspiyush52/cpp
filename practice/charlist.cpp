#include "print.h"
#include "integer.h"
#include "frand.h"

int main(void)
{
    const char* str = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char* ptr = str;
    CharList cl;
    for (; *ptr; ++ptr) {
        cl.prepend(*ptr);
        print(cl, '\n');
    }
    print("\nNow deleting:");
    for (int i{}, upto{cl.size() }; i < upto; ++i)
        cl.pop_back();
    print("\nAfter deleting:", cl, '\n');
    for (ptr = str; *ptr; ++ptr) {
        cl.append(*ptr);
        cl.append(*ptr);
        cl.pop_front();
        print(cl, '\n');
    }
    print(cl, '\n');
    for (int i{}; i < cl.size(); ++i)
        std::cout << cl[i] << ' ';
    print('\n');
    CharList st{"PARADOXICAL"};
    rng r;
    print("In string", st, '\n');
    for (int i{}; i < 20; ++i) {
        int j = r.randint(st.size());
        printf("\tcl[%d]: %c\n", j, st[j]);
    }
    return 0;
}
