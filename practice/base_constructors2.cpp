#include "utils.h"

class BaseClass {
    public:
        BaseClass() = default;
        BaseClass(int n): ptr{new int{n}} {}
        BaseClass(const BaseClass& src): BaseClass(*(src.ptr)) {
            ::print("BaseClass::BaseClass(const BaseClass&)");
        }
        BaseClass(BaseClass&& src): ptr{src.ptr} {
            ::print("BaseClass::BaseClass(BaseClass&&)");
            src.ptr = {};
        }
        BaseClass& operator=(const BaseClass& src) {
            if (this != &src) {
                ::print("BaseClass copy assign");
                if (this->isValid())
                    *(this->ptr) = *(src.ptr);
                else
                    this->alloc(*(src.ptr));
            }
            return *this;
        }
        BaseClass& operator=(BaseClass&& src) {
            if (this != &src) {
                ::print("BaseClass move assign");
                if (this->isValid())
                    delete this->ptr;
                this->alloc(*(src.ptr));
                src.clear();
            }
            return *this;
        }
        virtual void print() final {
            ::print("BaseClass::print()");
        }
        bool isValid() const {
            return (this->ptr != nullptr);
        }
        void alloc(int n) {
            this->ptr = new int{n};
        }
        ~BaseClass() {
            if (this->ptr)
                this->clear();
        }

        friend std::ostream& operator<<(std::ostream& out, const BaseClass& b) {
            b.streamInsert(out);
            return out;
        }
    
    private:
        int* ptr{};

        void clear() {
            delete this->ptr;
            this->ptr = {};
        }
        void streamInsert(std::ostream& out) const {
            if (this->isValid())
                out << "<BaseClass@" << this << ": " << *(this->ptr) << ">";
            else
                out << "null";
        }
};
class Derived : public BaseClass {
    typedef                      BaseClass                     Base;
    public:
        Derived() = default;
        Derived(int x): Base{x} {}
        Derived(const Derived& src): Base{static_cast<const Base&>(src)} {}
        Derived(Derived&& src): Base{static_cast<Base&&>(src)} {}
        Derived& operator=(const Derived& src) {
            *(static_cast<Base*>(this)) = static_cast<Base>(src);
            return *this;
        }
        Derived& operator=(Derived&& src) {
            *(static_cast<Base*>(this)) = static_cast<Base&&>(src);
            return *this;
        }
};

template<typename T>
constexpr std::remove_reference_t<T>&& move(T& x) {
    return static_cast<std::remove_reference_t<T>&&>(x);
}
template<typename T>
constexpr std::remove_reference_t<T>&& move(T&& x) {
    return static_cast<std::remove_reference_t<T>&&>(x);
}

int main(void)
{
    Derived x{0}, y{10}, z{y};
    std::cout << std::boolalpha;
    auto det = [](std::initializer_list<Derived*> args) {
        for (auto* arg : args)
            print(*arg, arg->isValid());
    };
    det({&x, &y, &z});
    return 0;
}
