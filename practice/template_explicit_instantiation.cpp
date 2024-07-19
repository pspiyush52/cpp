/*
 * We can explicitly instruct the compiler to generate a template
 * instance without creating any objects using the syntax below,
 * 
 *          template class __class_name__<template arguments>;
 * 
 * The compiler generates the instance based on the arguments
 * 
 * Template instances are put exactly where we put the template class
 * statements.
 * 
 * All members of the class template are instantiated, regardless of
 * whether they're used or not.
 * 
 * This feature is used to debug the code.
 */
#include "arrs.h"

template class arr::Array<int>;

int main(void)
{
    for (auto num : arr::range(15)){
        std::cout << num << " squared is " << (num * num) << '\n';
    }
    std::cout << '\n';

    return 0;
}