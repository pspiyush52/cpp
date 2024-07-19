#include <stdio.h>

void stars(int n){
    if (!n)
        putchar('\n');
    else{
        putchar('*');
        stars(n - 1);
    }
}
void lines(int n){
    if (n){
        lines(n - 1);
        stars(n);
    }
}

int main(void)
{
    lines(5);
    return 0;
}