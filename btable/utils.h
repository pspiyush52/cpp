#ifndef __UTILS_H
#define __UTILS_H

#include <iostream>
#include <iomanip>

#define nl std::cout << std::endl;
#define repeat(N) for (int i = 0; i < N; i++)
#define repeati(N, i) for (i = 0; i < N; i++)

void bin(int num, int width);
int get_width(int num);
void draw_line(int width);

#endif // __UTILS_H