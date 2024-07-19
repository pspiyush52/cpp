#ifndef __BASE_H
#define __BASE_H

#include <iostream>

class Base {
    public:
        int b_public;

        explicit Base(int x);
        Base(int x, int y, int z);

        // getters
        int get_base_public() const;
        int get_base_protected() const;
        int get_base_private() const;

        friend std::ostream& operator<<(std::ostream& output, const Base& obj);

    protected:
        int b_protected;

        // setters
        void set_public(int num);
        void set_protected(int num);
        void set_private(int num);
    
    private:
        int b_private;
};

#endif  // __BASE_H