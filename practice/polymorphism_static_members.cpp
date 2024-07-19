#include "utils.h"

class base {
    public:
        base(){ count++; }
        base(int num) : base_var(num){ count++; }
        virtual unsigned int get_count() const { return count; }
        virtual ~base(){ count--; }
    
    protected:
        int base_var{};
        static inline unsigned int count{};
};
class derived : public base {
    public:
        derived(){ count++; }
        derived(int num) : derived_var(num){ count++; }
        unsigned int get_count() const override { return count; }
        virtual ~derived(){ count--; }
    
    protected:
        int derived_var{};
        /*
         * If we do not define a count member at the derived level then the
         * derived class will have the same count static variable which will
         * result in both the base and derived having the same count which is
         * not what we want sometimes.
         * To prevent that we can redefine the static variale in the deribved
         * class so that the derived class now has a separate static variable
         * to keep track of the number of objects.
         */
        static inline unsigned int count{};
};

int main(void)
{
    base x, y, z, w, br[20];
    derived a, b, c, d, e, f;
    {
        base u, v, p, q;
        std::cout << "Number of base objects(nested scope): " << u.get_count() << '\n';
    }
    std::cout << "Number of base objects: " << x.get_count() << '\n';
    std::cout << "Number of derived objects: " << a.get_count() << '\n';

    // We will get runtime polymorphism because the get_count function is
    // virtual
    base* bptr = &e;  // e is a derived class object
    std::cout << "Number of derived objects: " << bptr->get_count() << '\n';

    return 0;
}