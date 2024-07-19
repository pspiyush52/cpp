#include <stdio.h>
#include <string.h>

void steps(const char* s, int n);
void isteps(const char* s, int n);
void prints(const char* str);

int main(int argc, char* argv[])
{
    const char* s = "OZONE";
    prints(s);
    return 0;
}

void steps(const char* s, int n){
    if (n){
        steps(s, n - 1);
        printf("%.*s\n", n, s);
    }
}
void isteps(const char* s, int n){
    if (n){
        printf("%.*s\n", n, s);
        isteps(s, n - 1);
    }
}
void prints(const char* str){
    if (str){
        size_t size = strlen(str);
        steps(str, size);
        isteps(str, size);
    }
}