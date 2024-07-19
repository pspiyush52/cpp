#ifndef __NONGCC__NOEXCEPT_H
#define __NONGCC__NOEXCEPT_H

namespace ex{
    class NoExcept{
        public:
            NoExcept() = default;
            void some_method() const noexcept { throw 1; }
    };
}

#endif  // __NONGCC__NOEXCEPT_H