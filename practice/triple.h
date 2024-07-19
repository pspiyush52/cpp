#ifndef __triple_H
#define __triple_H

class triple {
    public:
        triple() = default;
        // Not marked as explicit as we want to compare with base types
        triple(int num):
            triple(num, num, num){}
        triple(int x, int y, int z):
            a(x), b(y), c(z){}
        /*
            When we mark the function for the '==' operator as default the
            compiler automatically generates a function which compares all the
            member variables of the class one by one and returns true if all
            of them are equal.
            The members are compared in the order of their declarations in the
            class.
        */
        bool operator==(const triple& rhs) const = default;
        /*
            Also, in C++20, when we have the '==' operator defined, the
            compiler automatically defines the '!=' operator as well using the
            equivalence of lhs != rhs and !(lhs == rhs).
        */
    
    private:
        int a{};
        int b{};
        int c{};
};

#endif  // __triple_H