#ifndef __BASE_H
#define __BASE_H

#include <iostream>

class Base {
    public:
        int b_public;

        explicit Base(int x);
        Base(int x, int y, int z);

        // getters
        int get_public() const;
        int get_protected() const;
        int get_private() const;

        friend std::ostream& operator<<(std::ostream& output, const Base& obj);

    protected:
        int b_protected;

        // setters
        /*
         * Making the setters protected makes it so that the objects of the
         * base class cannot access these setters and so cannot change the
         * values of protected or private members. But the derived class can
         * access these inside their member functions and if the member
         * functions are public then the objects of the Derived class can be
         * used to set the values of the base class members.
         */
        void set_public(int num);
        void set_protected(int num);
        void set_private(int num);
    
    private:
        int b_private;
};

#endif  // __BASE_H