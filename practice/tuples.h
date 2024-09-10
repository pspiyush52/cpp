#ifndef __TUPLES_H
#define __TUPLES_H

#include <iostream>

// #define PAIR_DEBUG

/**
 * Class to create pairs of objects having same or different types. The
 * objects are created on the heap and the memory is managed by the class
 * itself. The objects are destroyed when the Pair object goes out of scope.
 */
template<typename first_tp, typename second_tp = first_tp>
class Pair {
    public:
        /**
         * Constructors:
         * 
         * The default constructor just initializes both pointers to nullptr.
         * They can later be made to point at valid objects using the setter
         * methods or the emplace methods.
         */
        Pair() = default;
        /**
         * This constructor deals with the case when both objects of the pair
         * are passed as lvalues. In this case copies of both objects are
         * dynamically created on the heap.
         */
        Pair(const first_tp& first, const second_tp& second):
            m_first{new first_tp{first}}, m_second{new second_tp{second}} {
#ifdef PAIR_DEBUG
                print("const first_tp&, const second_tp&");
#endif
            }
        /**
         * For the case when the first object is passed as an rvalue and the
         * second as an lvalue. In this case the first object is used to move
         * construct an object of the same type on the heap and a copy of the
         * second object is created on the heap as well.
         */
        Pair(first_tp&& first, const second_tp& second):
            m_first{new first_tp{static_cast<first_tp&&>(first)}},
            m_second{new second_tp{second}} {
#ifdef PAIR_DEBUG
                print("first_tp&&, const second_tp&");
#endif
            }
        /**
         * For the case when the first object is passed as an lvalue and the
         * second as an rvalue. In this case a copy of the first object is
         * created on the heap and the second object is used to move construct
         * an object of the same type on the heap.
         */
        Pair(const first_tp& first, second_tp&& second):
            m_first{new first_tp{first}},
            m_second{new second_tp{static_cast<second_tp&&>(second)}} {
#ifdef PAIR_DEBUG
                print("const first_tp&, second_tp&&");
#endif
            }
        /**
         * For the case where both the objects are passed as rvalue
         * references. In this case both the objects are used to move
         * construct objects of their respective types on the heap.
         * This is the mode of construction with the least overhead and is
         * recommended if the types of objects to be stored in the pair have
         * dynamic memory associated with them.
         */
        Pair(first_tp&& first, second_tp&& second):
            m_first{new first_tp{static_cast<first_tp&&>(first)}},
            m_second{new second_tp{static_cast<second_tp&&>(second)}} {
#ifdef PAIR_DEBUG
                print("first_tp&&, second_tp&&");
#endif
            }
        /**
         * Move constructor.
         */
        Pair(Pair&& src) {
            this->clearFirst();
            this->clearSecond();
            this->set(src.m_first, src.m_second);
            src.invalidate();
        }
        /**
         * Move assignment operator.
         * @returns A reference to the Pair object.
         */
        Pair& operator=(Pair&& src) {
            if (this != &src) {
                this->clearFirst();
                this->clearSecond();
                this->set(src.m_first, src.m_second);
                src.invalidate();
            }
            return *this;
        }
        /**
         * Deletes the first object if present and then uses the passed
         * arguments to construct a new object of first_tp type on the heap.
         * @returns A reference to the Pair object.
         */
        template<typename ...Args>
        Pair& emplaceFirst(Args&& ...args) {
            this->clearFirst();
            this->m_first = new first_tp{static_cast<Args&&>(args)...};
            return *this;
        }
        /**
         * Deletes the second object if present and then uses the passed
         * arguments to construct a new object of second_tp type on the heap.
         * @returns A reference to the Pair object.
         */
        template<typename ...Args>
        Pair& emplaceSecond(Args&& ...args) {
            this->clearSecond();
            this->m_second = new second_tp{static_cast<Args&&>(args)...};
            return *this;
        }
        /**
         * Indicates whether the Pair contains a valid first object or not.
         */
        constexpr bool hasFirst() const {
            return (this->m_first != nullptr);
        }
        /**
         * Indicates whether the Pair contains a valid second object or not.
         */
        constexpr bool hasSecond() const {
            return (this->m_second != nullptr);
        }
        /**
         * Access the first object of the pair.
         * @returns A non-const reference to the first object.
         */
        first_tp& getFirst() {
            return *(this->m_first);
        }
        /**
         * Read-only access to the first object of the pair.
         * @returns A const reference to the first object.
         */
        const first_tp& getFirst() const {
            return *(this->m_first);
        }
        /**
         * Access the second object of the pair.
         * @returns A non-const reference to the first object.
         */
        second_tp& getSecond() {
            return *(this->m_second);
        }
        /**
         * Read-only access to the second object of the pair.
         * @returns A const reference to the second object.
         */
        const second_tp& getSecond() const {
            return *(this->m_second);
        }
        /**
         * Setter methods for both first and second objects of the pair:
         * 
         * This method is invoked when an lvalue is used to set the value of
         * the first object.
         * If there is a first object in the pair then the argument f is
         * copied to it and if not then a new object is copy constructed.
         * @param f The object of type first_tp which is to be assigned to the
         * first object.
         * @returns A reference to the Pair object.
         */
        Pair& setFirst(const first_tp& f) {
#ifdef PAIR_DEBUG
            print("setFirst(first_tp&)");
#endif
            if (this->m_first)
                *(this->m_first) = f;
            else
                this->m_first = new first_tp{f};
            return *this;
        }
        /**
         * This method is invoked when an rvalue is used to set the value of
         * the first object.
         * If there is a first object in the pair then the argument f is moved
         * to it and if not then a new object is move constructed.
         * @param f The object of type first_tp passed as an rvalue which is
         * to be assigned to the first object.
         * @returns A reference to the Pair object.
         * @note If you are creating a temporary object in the method call
         * itself then it is better to use the emplaceFirst() method instead
         * with the arguments you are using to create that temporary object.
         * emplaceFirst() method will create an object of first_tp and make
         * it the first object of the pair but using the setFirst() method a
         * temporary object will be created first and then that temporary
         * object will either be moved to the first object or used to move
         * construct the first object thus increasing the overhead.
         * 
         * E.g.:
         * @note Rather than doing,
         * @note points.setFirst(Point{1.45, 2.09});
         * @note do,
         * @note points.emplaceFirst(1.45, 2.09);
         */
        Pair& setFirst(first_tp&& f) {
#ifdef PAIR_DEBUG
            print("setFirst(first_tp&&)");
#endif
            if (this->m_first)
                *(this->m_first) = static_cast<first_tp&&>(f);
            else
                this->m_first = new first_tp{static_cast<first_tp&&>(f)};
            return *this;
        }
        /**
         * This method is invoked when an lvalue is used to set the value of
         * the first object.
         * If there is a first object in the pair then the argument f is
         * copied to it and if not then a new object is copy constructed.
         * @param f The object of type first_tp which is to be assigned to the
         * first object.
         * @returns A reference to the Pair object.
         */
        Pair& setSecond(const second_tp& s) {
#ifdef PAIR_DEBUG
            print("setSecond(second_tp&)");
#endif
            if (this->m_second)
                *(this->m_second) = s;
            else
                this->m_second = new second_tp{s};
            return *this;
        }
        /**
         * This method is invoked when an rvalue is used to set the value of
         * the second object.
         * If there is a second object in the pair then the argument f is moved
         * to it and if not then a new object is move constructed.
         * @param f The object of type second_tp passed as an rvalue which is
         * to be assigned to the second object.
         * @returns A reference to the Pair object.
         * @note If you are creating a temporary object in the method call
         * itself then it is better to use the emplaceSecond() method instead
         * with the arguments you are using to create that temporary object.
         * emplaceSecond() method will create an object of second_tp and make
         * it the second object of the pair but using the setSecond() method a
         * temporary object will be created second and then that temporary
         * object will either be moved to the second object or used to move
         * construct the second object thus increasing the overhead.
         * 
         * E.g.:
         * @note Rather than doing,
         * @note points.setSecond(Point{1.45, 2.09});
         * @note do,
         * @note points.emplaceSecond(1.45, 2.09);
         */
        Pair& setSecond(second_tp&& s) {
#ifdef PAIR_DEBUG
            print("setSecond(second_tp&&)");
#endif
            if (this->m_second)
                *(this->m_second) = static_cast<second_tp&&>(s);
            else
                this->m_second = new second_tp{static_cast<second_tp&&>(s)};
            return *this;
        }
        ~Pair() {
            this->clearFirst();
            this->clearSecond();
        }
        friend std::ostream& operator<<(std::ostream& out, const Pair& p) {
            out << "Pair@" << &p << "<";
            p.printFirst(out);
            out << ", ";
            p.printSecond(out);
            out << ">";
            return out;
        }
    
    protected:
        void printFirst(std::ostream& out) const {
            if (this->m_first)
                out << this->getFirst();
            else
                out << "null";
        }
        void printSecond(std::ostream& out) const {
            if (this->m_second)
                out << this->getSecond();
            else
                out << "null";
        }
    
    private:
        first_tp* m_first{};
        second_tp* m_second{};
        void set(first_tp* first, second_tp* second) {
            this->m_first = first;
            this->m_second = second;
        }
        void clearFirst() {
            if (this->m_first) {
                delete this->m_first;
                this->m_first = {};
            }
        }
        void clearSecond() {
            if (this->m_second) {
                delete this->m_second;
                this->m_second = {};
            }
        }
        void invalidate() {
            this->m_first = {};
            this->m_second = {};
        }
};
template<typename first_tp, typename second_tp = first_tp, typename third_tp = second_tp>
class Triple : public Pair<first_tp, second_tp> {
    typedef                    Pair<first_tp, second_tp>                       Base;
    public:
        Triple(): Base() {}
        
        template<typename F, typename S, typename T>
        Triple(F&& first, S&& second, T&& third):
            Base{std::forward<F>(first), std::forward<S>(second)},
            m_third{new third_tp{std::forward<T>(third)}}
            {
            }
        
        template<typename ...Args>
        Triple& emplaceThird(Args&& ...args) {
            this->clearThird();
            this->m_third = new third_tp{static_cast<Args&&>(args)...};
            return *this;
        }
        third_tp& getThird() {
            return *(this->m_third);
        }
        const third_tp& getThird() const {
            return *(this->m_third);
        }
        Triple& setThird(const third_tp& third) {
            if (this->m_third)
                *(this->m_third) = third;
            else
                this->m_third = new third_tp{third};
            return *this;
        }
        Triple& setThird(third_tp&& third) {
            if (this->m_third)
                *(this->m_third) = static_cast<third_tp&&>(third);
            else
                this->m_third = new third_tp{static_cast<third_tp&&>(third)};
            return *this;
        }
        ~Triple() {
            this->clearThird();
        }
        friend std::ostream& operator<<(std::ostream& out, const Triple& t) {
            out << "Triple@" << &t << "<";
            t.printFirst(out);
            out << ", ";
            t.printSecond(out);
            out << ", ";
            t.printThird(out);
            out << ">";
            return out;
        }
    private:
        third_tp* m_third{};
        void printThird(std::ostream& out) const {
            if (this->m_third)
                out << this->getThird();
            else
                out << "null";
        }
        void set(first_tp* first, second_tp* second, third_tp* third) {
            Base::set(first, second);
            this->m_third = third;
        }
        void clearThird() {
            if (this->m_third)
                delete this->m_third;
            this->m_third = {};
        }
        void invalidate() {
            Base::invalidate();
            this->m_third = {};
        }
};

#endif  // __TUPLES_H
