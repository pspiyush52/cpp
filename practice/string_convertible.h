#ifndef __STRING_CONVERTIBLE_H
#define __STRING_CONVERTIBLE_H

#include "arr_string.h"

class StringConvertible{
    public:
        virtual string __str__() const = 0;
        friend string str(StringConvertible& arg){
            return arg.__str__();
        }
};

#endif  // __STRING_CONVERTIBLE_H