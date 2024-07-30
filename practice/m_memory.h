#ifndef __M_MEMORY_H
#define __M_MEMORY_H

#include <memory>

template<typename T>
using uptr = std::unique_ptr<T>;
template<typename T, typename ...Args>
uptr<T> makeUnique(const Args& ...args) {
    return std::make_unique<T>(args...);
}


#endif  // __M_MEMORY_H