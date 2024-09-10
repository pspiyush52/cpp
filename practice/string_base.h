#ifndef __STRING_BASE_H
#define __STRING_BASE_H

#include <cstddef>

class StringBase {
    public:
        virtual constexpr size_t size() = 0;
        
};

#endif  // __STRING_BASE_H