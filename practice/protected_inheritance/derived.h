#ifndef __DERIVED_H
#define __DERIVED_H

#include "base.h"

class Derived : protected Base {
    public:
        int d_public;

        explicit Derived(int x);
        Derived(int x, int y, int z);

        void print_base_info() const;
        void set_base(int x, int y, int z); // setter for base members(accessible)

        friend std::ostream& operator<<(std::ostream& output, const Derived& obj);
    
    protected:
        int d_protected;

    private:
        int d_private;
};

#endif  // __DERIVED_H