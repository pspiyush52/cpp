#ifndef __BASE_DERIVED_H
#define __BASE_DERIVED_H

#include "print.h"

class BaseClass {
    public:
        BaseClass() {
            ::print("BaseClass object created @", this);
        }
        BaseClass(int n): ptr{new int{n}} {
            ::print("BaseClass object created @", this);
        }
        BaseClass(const BaseClass& src) {
            this->ptr = new int{*(src.ptr)};
            ::print("BaseClass::BaseClass(const BaseClass&) @", this);
        }
        BaseClass(BaseClass&& src): ptr{src.ptr} {
            ::print("BaseClass::BaseClass(BaseClass&&) @", this);
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
                ::print("BaseClass move assign", &src, "to", this);
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
        virtual ~BaseClass() {
            ::print("BaseClass object destroyed @", this);
            if (this->ptr)
                this->clear();
        }

        friend std::ostream& operator<<(std::ostream& out, const BaseClass& b) {
            b.streamInsert(out);
            return out;
        }
    
    protected:
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
            static_cast<Base&>(*this) = static_cast<const Base&>(src);
            return *this;
        }
        Derived& operator=(Derived&& src) {
            static_cast<Base&>(*this) = static_cast<Base&&>(src);
            return *this;
        }
    private:
        void streamInsert(std::ostream& out) const {
            if (this->isValid())
                out << "<Derived@" << this << ": " << *(this->ptr) << ">";
            else
                out << "null";
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

#endif  // __BASE_DERIVED_H
