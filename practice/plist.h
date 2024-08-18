#ifndef __PLIST_H
#define __PLIST_H

#include <iostream>
#include "reverse_iterator.h"

template<typename T>
class PList {
    static const int DEFAULT_SIZE{8};
    static const int SHRINK{0};
    static const int EXPAND{1};
    class PListPointer;
    public:
        typedef                                                 PList                         self;
        typedef                                                     T                         value_type;
        typedef                                           value_type&                         reference;
        typedef                                     const value_type&                         const_reference;
        typedef                                          PListPointer                         pointer;
        typedef                                    const PListPointer                         const_pointer;
        class                                                                                 iterator;
        typedef                               ConstIterator<iterator>                         const_iterator;
        typedef                BidirectionalReverseIterator<iterator>                         reverse_iterator;
        typedef                       ConstIterator<reverse_iterator>                         const_reverse_iterator;

    public:

        PList(): A{new pointer[DEFAULT_SIZE]}, cur{}, arr_size{DEFAULT_SIZE} {}
        PList(int size) {
            size = (size < DEFAULT_SIZE) ? DEFAULT_SIZE : size;
            this->make(size);
        }
        constexpr int size() const {
            return this->cur;
        }
        constexpr int capacity() const {
            return this->arr_size;
        }
        constexpr bool isEmpty() {
            return (!(this->cur));
        }
        /**
         * Accepts a pointer to the object of type T and appends it at the end
         * of the list. The raw pointer will be wrapped by a Pointer object
         * and so when the list goes out of scope and the destructor is called
         * the object will be deleted by the destructor of the Pointer class.
         * @param ptr The raw pointer of type T* pointing towards the heap
         * object to be inserted into the list.
         * @note Possible usage:
         * @note list.insert(new T{args});
         * @note The moment the list goes out of scope the object will be
         * deleted from the heap and the pointer ptr will be left dangling.
         */
        self& insert(T* ptr) {
            if (this->isFull())
                this->alter(EXPAND);
            this->A[(this->cur)++] = pointer(ptr);
            return *this;
        }
        template<typename ...Args>
        self& emplace(Args&& ...args) {
            if (this->isFull())
                this->alter(EXPAND);
            this->A[(this->cur)++].setPointer(new value_type(static_cast<Args&&>(args)...));
            return *this;
        }
        /**
         * Creates an object with the passed arguments on the heap and
         * replaces the object at index position. The object at index gets
         * deleted from the heap and cannot be recovered.
         * @param index The position where the object is to be placed.
         * @param args The arguments needed to construct an object of type T.
         * @warning The object at index will get deleted and the new object
         * will take its place. The only way to save the object at index is to
         * copy or move it to some object of type T.
         */
        template<typename ...Args>
        self& emplaceAt(int index, Args&& ...args) {
            if (indexInRange(index)) {
                this->A[index].del();
                this->A[index].setPointer(new value_type(static_cast<Args&&>(args)...));
            }
            return *this;
        }
        self& pop() {
            if (this->isEmpty())
                return *this;
            if (this->isVacant())
                this->alter(SHRINK);
            this->A[this->cur - 1].deleteItem();
            --(this->cur);
            return *this;
        }
        void printArray() {
            std::cout << '[';
            if (this->cur) {
                int i{};
                for (; i < this->arr_size - 1; ++i) {
                    std::cout << this->A[i] << ", ";
                }
                std::cout << this->A[i];
            }
            std::cout << ']';
        }
        reference operator[](int index) {
            return *(this->A[index]);
        }
        const_reference operator[](int index) const {
            return *(this->A[index]);
        }

        iterator begin() {
            return {this->A};
        }
        iterator end() {
            return {this->A + this->cur};
        }
        const_iterator begin() const {
            return {this->A};
        }
        const_iterator end() const {
            return {this->A + this->cur};
        }
        const_iterator cbegin() const {
            return {this->A};
        }
        const_iterator cend() const {
            return {this->A + this->cur};
        }

        reverse_iterator rbegin() {
            return {this->A + this->cur - 1};
        }
        reverse_iterator rend() {
            return {this->A - 1};
        }
        const_reverse_iterator rbegin() const {
            return {reverse_iterator(this->A + this->cur - 1)};
        }
        const_reverse_iterator rend() const {
            return {reverse_iterator(this->A - 1)};
        }
        const_reverse_iterator crbegin() const {
            return {reverse_iterator(this->A + this->cur - 1)};
        }
        const_reverse_iterator crend() const {
            return {reverse_iterator(this->A - 1)};
        }
        
        ~PList() {
            if (this->A) {
                delete[] this->A;
                this->set({}, {}, {});
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const PList& list) {
            out << '[';
            if (list.cur) {
                int i{};
                for (; i < list.size() - 1; ++i)
                    out << list.A[i] << ", ";
                out << list.A[i];
            }
            out << ']';
            return out;
        }

    private:
        pointer* A;
        int cur;
        int arr_size;

        bool isFull() {
            return (this->cur == this->arr_size);
        }
        bool isVacant() {
            return ((this->arr_size > DEFAULT_SIZE) && (this->cur == this->arr_size / 3));
        }
        bool indexInRange(int index) {
            return ((index >= 0) && (index < this->cur));
        }
        void set(pointer* _A, int _cur, int _size) {
            this->A = _A;
            this->cur = _cur;
            this->arr_size = _size;
        }
        void make(int size) {
            this->set(new pointer[size], {}, size);
        }
        void alter(int flag) {
            pointer* newArray{};
            int newSize{};
            switch(flag) {
                case EXPAND:
                    newSize = this->arr_size * 2;
                    break;
                case SHRINK:
                    newSize = this->arr_size / 2;
                    break;
            }
            newArray = new pointer[newSize];
            for (int i{}; i < this->cur; ++i)
                newArray[i] = static_cast<pointer&&>(this->A[i]);
            delete[] this->A;
            this->A = newArray;
            this->arr_size = newSize;
        }
};

template<typename T>
class PList<T>::PListPointer {
    typedef                             T                         value_type;
    typedef                            T&                         reference;
    typedef                      const T&                         const_reference;
    typedef                            T*                         pointer;
    typedef                      const T*                         const_pointer;
    
    public:
        PListPointer() = default;
        PListPointer(pointer p) {
            this->ptr = p;
        }
        template<typename ...Args>
        void bind(Args&& ...args) {
            this->ptr = new value_type(static_cast<Args&&>(args)...);
        }
        reference operator*() {
            return *(this->ptr);
        }
        const_reference operator*() const {
            return *(this->ptr);
        }
        operator bool() const {
            return (this->ptr != nullptr);
        }
        PListPointer operator=(const PListPointer&) = delete;
        PListPointer& operator=(PListPointer&& src) {
            this->ptr = src.ptr;
            src.ptr = {};
            return *this;
        }
        pointer operator->() {
            return this->ptr;
        }
        pointer getPointer() {
            return this->ptr;
        }
        void setPointer(pointer p) {
            this->ptr = p;
        }
        ~PListPointer(){
            if (this->ptr)
                this->deleteItem();
        }
        void deleteItem() {
            delete this->ptr;
            this->ptr = {};
        }
        bool del() {
            if (this->ptr) {
                this->deleteItem();
                return true;
            }
            return false;
        }
        friend std::ostream& operator<<(std::ostream& out, const PListPointer& p) {
            if (p.ptr)
                out << (*(p.ptr));
            else
                out << "null";
            return out;
        }

    private:
        pointer ptr{};
};

template<typename T>
class PList<T>::iterator {
    public:
        typedef               T                value_type;
        iterator(pointer* iter): it{iter} {}
        PList<T>::reference operator*() {
            return (**it);
        }
        iterator& operator++() {
            ++it;
            return *this;
        }
        iterator& operator--() {
            --it;
            return *this;
        }
        bool operator==(const iterator& rhs) {
            return (this->it == rhs.it);
        }
        bool operator!=(const iterator& rhs) {
            return (this->it != rhs.it);
        }
    
    private:
        pointer* it;
};

#endif  // __PLIST_H
