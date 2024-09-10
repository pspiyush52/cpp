#ifndef __DEQUE_H
#define __DEQUE_H

#include <iostream>
#include <stdlib.h>
#include <initializer_list>
#include <concepts>
#include "..\practice\print.h"

template<typename T>
concept ForwardIterable = requires (T obj) {
    std::begin(obj);
    std::end(obj);
};

template<typename T>
concept ReverseIterable = requires (T obj) {
    std::rbegin(obj);
    std::rend(obj);
};


template<typename T>
class deque {
    static const int DEFAULT_SIZE{8};
    static const int SHRINK{};
    static const int EXPAND{1};
    struct Tautology {
        bool operator()(const T&) {
            return true;
        }
    };
    struct Identity {
        template<typename value_tp>
        const value_tp& operator()(const value_tp& x) {
            return std::forward<const value_tp>(x);
        }
        template<typename value_tp>
        value_tp&& operator()(value_tp& x) {
            return std::forward<value_tp>(x);
        }
        template<typename value_tp>
        value_tp&& operator()(value_tp&& x) {
            return std::forward<value_tp>(x);
        }
    };
    static int max(int x, int y) {
        return (x > y) ? x : y;
    }
    
    public:
        typedef                            T                      value_type;
        typedef                  value_type*                      pointer;
        typedef                  value_type&                      reference;
        typedef            const value_type*                      const_pointer;
        typedef            const value_type&                      const_reference;
        class                                                     iterator;
        class                                                     const_iterator;
        class                                                     reverse_iterator;
        class                                                     const_reverse_iterator;
        class                                                     view_iterator;
        class                                                     const_view_iterator;
    
    public:
        deque(): arr{new T[DEFAULT_SIZE + 1]}, front{}, cur{}, arr_size{DEFAULT_SIZE + 1} {}
        deque(int size) {
            this->initialize(max(size, DEFAULT_SIZE) + 1);
        }
        deque(int size, const value_type& default_value): deque(2 * size) {
            for (int i{}; i < size; ++i)
                this->arr[i] = default_value;
            if (size >= 0)
                this->cur = size;
        }
        deque(const deque& src, int from, int to) {
            if ((from < 0) || (from >= src.size()) || (to <= from)) {
                this->initialize(DEFAULT_SIZE + 1);
            }
            else {
                int src_size{src.size()}, dsize{};
                to = (to > src_size) ? (src_size - 1) : to;
                dsize = to - from + 1;
                this->initialize(2 * dsize + 1);
                this->cur = dsize;
                for (int i{}; i < dsize; ++i, ++from)
                    this->arr[i] = src[from];
            }
        }
        deque(const_iterator& from, const_iterator& to): deque(2 * from.getSize()) {
            int i{};
            for (; from != to; ++from, ++i)
                this->arr[i] = *from;
            this->cur = i;
        }
        deque(const_iterator&& from, const_iterator&& to): deque(from, to) {}
        deque(const std::initializer_list<value_type>& args) {
            this->initialize(args.size() * 2 + 1);
            auto iter = args.begin();
            for (; iter != args.end(); ++iter)
                this->push_back(*iter);
        }
        template<ForwardIterable Container>
        deque(const Container& c): deque(2 * std::size(c)) {
            for (auto& x : c)
                this->push_back(x);
        }
        deque(const deque& src): deque(src.size() * 2) {
            const_iterator iter = src.cbegin();
            int i{};
            for (; iter != src.cend(); ++iter, ++i)
                this->arr[i] = *iter;
            this->cur = i;
        }
        deque(deque&& src) {
            this->set(src.arr, src.front, src.cur, src.arr_size);
            src.invalidate();
        }
        deque& operator=(const deque& src) {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->initialize(src.size() * 2);
                const_iterator iter = src.cbegin();
                int i{};
                for (; iter != src.cend(); ++iter, ++i)
                    this->arr[i] = *iter;
                this->cur = i;
            }
            return *this;
        }
        deque& operator=(deque&& src) {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->set(src.arr, src.front, src.cur, src.arr_size);
                src.invalidate();
            }
            return *this;
        }

        constexpr bool isEmpty() const {
            return (!this->cur);
        }
        constexpr int size() const {
            return this->cur;
        }
        constexpr int capacity() const {
            return (this->arr_size - 1);
        }
        
        /**
         * Returns a modifiable reference to the first element of the list.
         * @note It will still return a reference to an item of the list even
         * if the list is empty so it might contain some garbage value.
         */
        reference getFront() {
            return this->arr[this->front];
        }
        /**
         * Returns a non-modifiable reference to the first element of the
         * list.
         * @note It will still return a reference to an item of the list even
         * if the list is empty so it might contain some garbage value.
         */
        const_reference getFront() const {
            return this->arr[this->front];
        }
        /**
         * Insert an item at the front of the list.
         * Similar to the enqueue() operation of a Queue.
         */
        deque& push_front(const value_type& item) {
            if (this->isFull())
                this->alter(EXPAND);
            this->front = (this->front + this->arr_size - 1) % this->arr_size;
            this->arr[this->front] = item;
            ++(this->cur);
            return *this;
        }
        /**
         * Insert an item at the front of the list.
         * Similar to the enqueue() operation of a Queue.
         */
        deque& push_front(value_type&& item) {
            if (this->isFull())
                this->alter(EXPAND);
            this->front = (this->front + this->arr_size - 1) % this->arr_size;
            this->arr[this->front] = static_cast<T&&>(item);
            ++(this->cur);
            return *this;
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the front of the list.
         */
        deque& push_front(const deque& d) {
            const_reverse_iterator it = d.crbegin();
            for (; it != d.crend(); ++it)
                this->push_front(*it);
            return *this;
        }
        /**
         * Inserts all the items from a container containing compatible types
         * if items at the front of the list.
         * @note Compilation fails if the container contains incompatible type
         * of data.
         * @note A "compatible" type is one which can be converted to the type
         * of data that the deque holds.
         */
        template<ReverseIterable Container>
        deque& push_front(const Container& c) {
            static_assert(
                std::is_convertible_v<typename Container::value_type, value_type>,
                "Container holds incompatible type of data\n"
            );
            auto it = std::rbegin(c);
            auto rend = std::rend(c);
            for (; it != rend; ++it)
                this->push_front(*it);
            return *this;
        }
        /**
         * Inserts an item at the back of the list.
         * Similar to the push() operation on a Stack.
         */
        deque& push_back(const value_type& item) {
#ifdef DEQUE_DEBUG
            std::cout << "deque::push_back(const value_type&)\n";
#endif
            if (this->isFull())
                this->alter(EXPAND);
            this->arr[(this->front + this->cur) % this->arr_size] = item;
            ++(this->cur);
            return *this;
        }
        /**
         * Inserts an item at the back of the list.
         * Similar to the push() operation on a Stack.
         */
        deque& push_back(value_type&& item) {
#ifdef DEQUE_DEBUG
            std::cout << "deque::push_back(value_type&&)\n";
#endif
            if (this->isFull())
                this->alter(EXPAND);
            this->arr[(this->front + this->cur) % this->arr_size] = static_cast<T&&>(item);
            ++(this->cur);
            return *this;
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the back of the list.
         */
        deque& push_back(const deque& d) {
            const_iterator it = d.cbegin();
            for (; it != d.cend(); ++it)
                this->push_back(*it);
            return *this;
        }
        /**
         * Inserts all the items from an initializer list containing the same
         * type of data at the back of the list.
         */
        deque& push_back(std::initializer_list<value_type> args) {
            auto it = args.begin();
            for (; it != args.end(); ++it)
                this->push_back(*it);
            return *this;
        }
        /**
         * Inserts all the items from a container containing compatible types
         * if items at the back of the list.
         * @note Compilation fails if the container contains incompatible type
         * of data.
         * @note A "compatible" type is one which can be converted to the type
         * of data that the deque holds.
         */
        template<ForwardIterable Container>
        deque& push_back(const Container& c) {
            static_assert(
                std::is_convertible_v<typename Container::value_type, typename deque<T>::value_type>,
                "Container holds incompatible type of data\n"
            );
            auto it = std::begin(c);
            auto end = std::end(c);
            for (; it != end; ++it)
                this->push_back(*it);
            return *this;
        }
        /**
         * Insert an item at the front of the list.
         * Similar to the enqueue() operation of a Queue.
         * @note This method delegates to the push_front() method.
         */
        deque& prepend(const value_type& item) {
            return this->push_front(item);
        }
        /**
         * Insert an item at the front of the list.
         * Similar to the enqueue() operation of a Queue.
         * @note This method delegates to the push_front() method.
         */
        deque& prepend(value_type&& item) {
            return this->push_front(static_cast<T&&>(item));
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the front of the list.
         * @note This method delegates to the push_front() method.
         */
        deque& prepend(const deque& d) {
            return this->push_front(d);
        }
        /**
         * Inserts all the items from a container containing compatible types
         * if items at the front of the list.
         * @note Compilation fails if the container contains incompatible type
         * of data.
         * @note A "compatible" type is one which can be converted to the type
         * of data that the deque holds.
         * @note This method delegates to the push_front() method.
         */
        template<ReverseIterable Container>
        deque& prepend(const Container& c) {
            return this->push_front<Container>(c);
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& append(const value_type& item) {
#ifdef DEQUE_DEBUG
            print("deque::append(const value_type&)");
#endif
            return this->push_back(item);
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& append(value_type&& item) {
#ifdef DEQUE_DEBUG
            print("deque::append(value_type&&)");
#endif
            return this->push_back(static_cast<T&&>(item));
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the back of the list.
         * @note This method delegates to the push_back() method.
         */
        deque& append(const deque& d) {
            return this->push_back(d);
        }
        /**
         * Inserts all the items from a container containing compatible types
         * if items at the back of the list.
         * @note Compilation fails if the container contains incompatible type
         * of data.
         * @note A "compatible" type is one which can be converted to the type
         * of data that the deque holds.
         * @note This method delegates to the push_back() method.
         */
        template<ForwardIterable Container>
        deque& append(const Container& c) {
            return this->push_back<Container>(c);
        }
        /**
         * This method removes an item from the front of the list.
         * Similar to the dequeue() operation of a Queue.
         */
        deque& pop_front() {
            if (this->isVacant())
                this->alter(SHRINK);
            if (this->cur) {
                this->front = ((this->front + 1) % this->arr_size);
                --(this->cur);
            }
            return *this;
        }
        /**
         * This method removes an item fron the back of the list.
         * Similar to the pop() operation of a Stack.
         */
        deque& pop_back() {
            if (this->isVacant())
                this->alter(SHRINK);
            if (this->cur)
                --(this->cur);
            return *this;
        }
        /**
         * Instead of creating an object and then inserting it into the list
         * using push_front(), the emplace_front() method can be used to pass
         * the arguments needed to create the object which is then created and
         * inserted at the front of the list.
         * @param args The arguments needed to create the object.
         */
        template<typename ...Args>
        deque& emplace_front(Args&& ...args) {
            if (this->isFull())
                this->alter(EXPAND);
            this->front = (this->front + this->arr_size - 1) % this->arr_size;
            this->arr[this->front] = static_cast<T&&>(T{static_cast<Args&&>(args)...});
            ++(this->cur);
            return *this;
        }
        /**
         * Instead of creating an object and then inserting it into the list
         * using push_back(), the emplace_back() method can be used to pass
         * the arguments needed to create the object which is then created and
         * inserted at the back of the list.
         * @param args The arguments needed to create the object.
         */
        template<typename ...Args>
        deque& emplace_back(Args&& ...args) {
            if (this->isFull())
                this->alter(EXPAND);
            this->arr[(this->front + this->cur) % this->arr_size] = static_cast<T&&>(T{static_cast<Args&&>(args)...});
            ++(this->cur);
            return *this;
        }
        /**
         * Shrinks the containing array so that it is just large enough to
         * hold all the items in the deque.
         * @note If the list is empty then the size of the containing array is
         * readjusted back to the DEFAULT_SIZE which is 8.
         * @note The mehtod allocates new memory which is exactly large enough
         * to just hold the number of items in the list currently and copies
         * the elements into the newly allocated memory which becomes the new
         * containing array for the deque.
         */
        deque& shrink_to_fit() {
            if (this->isEmpty()) {
                delete[] this->arr;
                this->initialize(DEFAULT_SIZE + 1);
            }
            else {
                int newSize = this->cur + 1;
                pointer newArray = new value_type[newSize];
                pointer ptr = newArray;
                iterator iter = this->begin();
                for (; iter != this->end(); ++iter, ++ptr)
                    *ptr = *iter;
                delete[] this->arr;
                this->set(newArray, {}, this->cur, newSize);
            }
            return *this;
        }
        /**
         * Modifies the items of the list which satisfy the Predicate
         * according to the function like entity mod_fun.
         * @param mod_fun Function like entity that can accept an item of the
         * list and returns an item of the same type. So if the deque holds
         * int values then the mod_fun must have a signature: int mod_fun(int).
         * The value returned by mod_fun will replace the original value
         * present in the deque.
         * @param pred Function like entity that can accept an item of the
         * list and returns a boolean result that will decide whether that
         * item gets modified or not;
         */
        template<typename Modifier, typename Predicate = Tautology>
        deque& modify(Modifier mod_fun = {}, Predicate pred = {}) {
            for (auto iter = this->begin(); iter != this->end(); ++iter)
                if (pred(*iter))
                    *iter = mod_fun(*iter);
            return *this;
        }
        deque& setValue(const value_type& val) {
            deque& self{*this};
            for (int i{}; i < self.size(); ++i)
                self[i] = val;
            return *this;
        }
        /**
         * Reverses the list.
         */
        deque& reverse() {
            reverse_iterator riter = this->rbegin();
            iterator iter = this->begin();
            for (int i{}; i < (this->cur / 2); ++i) {
                this->swap(iter.getPos(), riter.getPos());
                ++riter;
                ++iter;
            }
            return *this;
        }
        /**
         * Search for an item by the key in the list.
         * @param key The key to be used for searching.
         * @param p A function like entity which accepts an item of the list
         * as parameter and returns the field value to be used for matching
         * with the key.
         * @returns The index i of the item whose field matches the key and -1
         * if no such item exists in the list.
         */
        template<typename key_tp, typename Projection = Identity>
        int search(const key_tp& key, Projection p = {}) const {
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                if (p(*it) == key)
                    return it.getPos();
            return -1;
        }
        /**
         * Search for an item by the key in the list starting from the given
         * position.
         * @param key The key to be used for searching.
         * @param fromPosition The index from where the search should begin.
         * @param p A function like entity which accepts an item of the list
         * as parameter and returns the field value to be used for matching
         * with the key.
         * @returns The index i of the item whose field matches the key and -1
         * if no such item exists in the list or if fromPosition exceeds the
         * bounds of the list.
         */
        template<typename key_tp, typename Projection = Identity>
        int search(const key_tp& key, int fromPosition, Projection p = {}) const {
            if (fromPosition >= this->cur - 1)
                return -1;
            const_iterator it{this, this->relativePosition(fromPosition)};
            for (; it != this->cend(); ++it)
                if (p(*it) == key)
                    return it.getPos();
            return -1;
        }
        /**
         * Provides a view of the items in the list from index i up to but not
         * including index j.
         * @returns A view_iterator object that can be used to iterate through
         * the items of the list in the specified range.
         * @note The view_iterator object contains begin() and end() methods
         * that return the appropriate deque::iterator objects to allow
         * traversal.
         */
        view_iterator sliceView(int i, int j) {
            if (isOutOfBounds(i) || isOutOfBounds(j) || (i >= j))
                return {this, 0, 0};
            return {this, i, j};
        }
        view_iterator sliceView(int i) {
            if (isOutOfBounds(i))
                return {this, 0, 0};
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        /**
         * Provides a view of the items in the list from index i up to but not
         * including index j.
         * @returns A const_view_iterator object that can be used to iterate
         * through the items of the list in the specified range but does not
         * allow modification.
         * @note The view_iterator object contains begin() and end() methods
         * that return the appropriate deque::const_iterator objects to allow
         * traversal.
         */
        const_view_iterator sliceView(int i, int j) const {
            if (isOutOfBounds(i) || isOutOfBounds(j) || (i >= j))
                return {this, 0, 0};
            return {this, i, j};
        }
        const_view_iterator sliceView(int i) const {
            if (isOutOfBounds(i))
                return {this, 0, 0};
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        /**
         * Returns a new list containing the items from the existing list from
         * index i up to but not including index j.
         * @note Returns an empty list if the index values are not valid.
         */
        deque slice(int i, int j) const {
            if ((i < 0) || (j < 0) || (i >= j))
                return {};
            deque res;
            const_iterator it{this, relativePosition(i)}, end{this, relativePosition(j)};
            for (; it != end; ++it)
                res.append(*it);
            return res;
        }

        iterator begin() {
            return {this, this->front};
        }
        iterator end() {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        const_iterator begin() const {
            return {this, this->front};
        }
        const_iterator end() const {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        const_iterator cbegin() const {
            return {this, this->front};
        }
        const_iterator cend() const {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        reverse_iterator rbegin() {
            return {this, (this->front + this->cur - 1) % this->arr_size};
        }
        reverse_iterator rend() {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
        }
        const_reverse_iterator rbegin() const {
            return {this, (this->front + this->cur - 1) % this->arr_size};
        }
        const_reverse_iterator rend() const {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
        }
        const_reverse_iterator crbegin() const {
            return {this, (this->front + this->cur - 1) % this->arr_size};
        }
        const_reverse_iterator crend() const {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
        }

        view_iterator operator()(int i, int j) {
            if (isOutOfBounds(i) || isOutOfBounds(j) || (i >= j))
                return {this, 0, 0};
            return {this, i, j};
        }
        view_iterator operator()(int i) {
            if (isOutOfBounds(i))
                return {this, 0, 0};
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        const_view_iterator operator()(int i, int j) const {
            if (isOutOfBounds(i) || isOutOfBounds(j) || (i >= j))
                return {this, 0, 0};
            return {this, i, j};
        }
        const_view_iterator operator()(int i) const {
            if (isOutOfBounds(i))
                return {this, 0, 0};
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        /**
         * Returns a reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        reference operator[](int i) {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Returns a const reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        const_reference operator[](int i) const {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(const value_type& item) {
            return this->push_back(std::forward<const T>(item));
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(value_type&& item) {
            return this->push_back(static_cast<T&&>(item));
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the back of the list.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(const deque& d) {
            return this->push_back(std::forward<const deque<T>>(d));
        }
        /**
         * Inserts all the items from a container containing compatible types
         * if items at the back of the list.
         * @note Compilation fails if the container contains incompatible type
         * of data.
         * @note A "compatible" type is one which can be converted to the type
         * of data that the deque holds.
         * @note This method delegates to the push_back() method.
         */
        template<ForwardIterable Container>
        deque& operator+=(const Container& c) {
            return this->push_back<Container>(std::forward<Container>(c));
        }

        // DBG
        /**
         * Displays the values for the front, rear, current size, and total
         * capacity of the deque.
         * @note The rear is calculated and not stored.
         */
        void __print_status() const {
            printf("(Front: %d, Rear: %d, Cur: %d, size: %d)\n", front, (front + cur) % (arr_size + 1), cur, arr_size);
        }
        /**
         * Prints the contents of the entire containing array.
         */
        void __print_array() const {
            std::cout << '[';
            for (int i{}; i < this->arr_size; ++i)
                std::cout << this->arr[i] << ", ";
            std::cout << this->arr[this->arr_size] << ']';
        }

        ~deque() {
            if (this->arr) {
                delete[] this->arr;
                this->invalidate();
            }
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const deque<U>& d);
    
    protected:
        /**
         * This method is written with the assumption that it will be used
         * only when Deque is adapted to work as a Stack and hence the front
         * will never change since push and pop operations will work at the
         * rear end.
         */
        reference getTop() {
            return this->arr[this->cur - 1];
        }
        int Front() const {
            return this->front;
        }
        int Cur() const {
            return this->cur;
        }
        void setFront(int f) {
            this->front = f;
        }
        void setCur(int c) {
            this->cur = c;
        }

    private:
        value_type* arr{};
        int front{};
        int cur{};
        int arr_size{};

        void streamInsert(std::ostream& out) const {
            out << '[';
            if (this->cur) {
                int i{this->front}, count{};
                for (; count < this->cur - 1; ++count, i = (i + 1) % this->arr_size)
                    out << this->arr[i] << ", ";
                out << this->arr[i];
            }
            else if (this->arr == nullptr)
                out << "null";
            out << ']';
        }
        constexpr bool isFull() const {
            return (this->cur == this->arr_size - 1);
        }
        constexpr bool isVacant() const {
            return (this->cur == this->arr_size / 3);
        }
        bool isOutOfBounds(int index) const {
            return ((index < 0) || (index > this->cur - 1));
        }
        /**
         * Set the value of all member variables one by one in sequence.
         * @param arr
         * @param front
         * @param cur
         * @param arr_size
         */
        void set(pointer _arr, int _front, int _cur, int _arr_size) {
            this->arr = _arr;
            this->front = _front;
            this->cur = _cur;
            this->arr_size = _arr_size;
        }
        /**
         * Allocates memory to hold _size number of list items and then
         * calls the set() method to set appropriate values of the member
         * variables.
         */
        void initialize(int _size) {
            this->set(new value_type[_size], 0, 0, _size);
        }
        /**
         * Grows or shrinks the containing array according to the value of the
         * flag parameter.
         * @param flag Must be one out of the two static constants defined in
         * the class, deque::EXPAND or deque::SHRINK.
         */
        void alter(int flag) {
            pointer newArray{};
            int i{}, newSize{};
            switch (flag) {
                case EXPAND:
                    newSize = this->arr_size * 2;
                break;
                case SHRINK:
                    newSize = this->arr_size / 2;
                break;
            }
            newArray = new value_type[newSize];
            iterator iter = this->begin();
            for (; iter != this->end(); ++i, ++iter)
                newArray[i] = std::move(*iter);
            delete[] this->arr;
            this->set(newArray, {}, this->cur, newSize);
        }
        void invalidate() {
            this->set({}, {}, {}, 1);
        }
        /**
         * Swap elements at indices i and j in the containing array.
         */
        void swap(int i, int j) {
            value_type tmp{this->arr[i]};
            this->arr[i] = static_cast<value_type&&>(this->arr[j]);
            this->arr[j] = static_cast<value_type&&>(tmp);
        }
        /**
         * Returns the actual index at which the element at index i in the
         * list will be located in the containing array.
         * @param i The index of the list item whose actual position in the
         * containing array is required.
         */
        int relativePosition(int i) const {
            return (this->front + i) % this->arr_size;
        }
};

template<typename U>
inline std::ostream& operator<<(std::ostream& out, const deque<U>& d) {
    d.streamInsert(out);
    return out;
}

template<typename T>
void det(const deque<T>& d) {
    std::cout << d << '\n';
    std::cout << "Size: " << d.size() << '\n';
    std::cout << "Capacity: " << d.capacity() << '\n';
}

/**
 * Iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::iterator {
    public:
        iterator(deque* ptr, int i): p{ptr}, pos{i} {}
        reference operator*() {
            return p->arr[pos];
        }
        iterator& operator++() {
            pos = (pos + 1) % p->arr_size;
            return *this;
        }
        iterator& operator--() {
            pos = (pos + p->arr_size - 1) % p->arr_size;
            return *this;
        }
        bool operator==(const iterator& rhs) {
            return (this->pos == rhs.pos);
        }
        bool operator!=(const iterator& rhs) {
            return (this->pos != rhs.pos);
        }
        int getPos() {
            return this->pos;
        }
    
    private:
        deque* p;
        int pos;
};

/**
 * const iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::const_iterator {
    public:
        const_iterator(const deque* ptr, int i): p{ptr}, pos{i} {}
        const_reference operator*() {
            return p->arr[pos];
        }
        const_iterator& operator++() {
            pos = (pos + 1) % p->arr_size;
            return *this;
        }
        const_iterator& operator--() {
            pos = (pos + p->arr_size - 1) % p->arr_size;
            return *this;
        }
        bool operator==(const const_iterator& rhs) {
            return (this->pos == rhs.pos);
        }
        bool operator!=(const const_iterator& rhs) {
            return (this->pos != rhs.pos);
        }
        int getPos() {
            return this->pos;
        }
        int getSize() {
            return p->size();
        }

    private:
        const deque* p;
        int pos;
};

/**
 * Reverse iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::reverse_iterator {
    public:
        reverse_iterator(deque* ptr, int i): p{ptr}, pos{i} {}
        reference operator*() {
            return p->arr[pos];
        }
        reverse_iterator& operator++() {
            pos = (pos + p->arr_size - 1) % p->arr_size;
            return *this;
        }
        reverse_iterator& operator--() {
            pos = (pos + 1) % p->arr_size;
            return *this;
        }
        bool operator==(const reverse_iterator& rhs) {
            return (this->pos == rhs.pos);
        }
        bool operator!=(const reverse_iterator& rhs) {
            return (this->pos != rhs.pos);
        }
        int getPos() {
            return this->pos;
        }
    
    private:
        deque* p;
        int pos;
};

/**
 * const reverse iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::const_reverse_iterator {
    public:
        const_reverse_iterator(const deque* ptr, int i): p{ptr}, pos{i} {}
        const_reference operator*() {
            return p->arr[pos];
        }
        const_reverse_iterator& operator++() {
            pos = (pos + p->arr_size - 1) % p->arr_size;
            return *this;
        }
        const_reverse_iterator& operator--() {
            pos = (pos + 1) % p->arr_size;
            return *this;
        }
        bool operator==(const const_reverse_iterator& rhs) {
            return (this->pos == rhs.pos);
        }
        bool operator!=(const const_reverse_iterator& rhs) {
            return (this->pos != rhs.pos);
        }
        int getPos() {
            return this->pos;
        }
    
    private:
        const deque* p;
        int pos;
};

/**
 * View iterator for iterating through a view of the deque.
 */
template<typename T>
class deque<T>::view_iterator {
    public:
        view_iterator(deque<T>* ptr, int i, int j): p{ptr}, front{i}, rear{j} {}
        deque<T>::iterator begin() {
            return {p, p->relativePosition(front)};
        }
        deque<T>::iterator end() {
            return {p, p->relativePosition(rear)};
        }
    private:
        deque<T>* p;
        int front;
        int rear;
};
/**
 * const view iterator for iterating through a view of the deque.
 */
template<typename T>
class deque<T>::const_view_iterator {
    public:
        const_view_iterator(const deque<T>* ptr, int i, int j): p{ptr}, front{i}, rear{j} {}
        deque<T>::const_iterator begin() {
            return {p, p->relativePosition(front)};
        }
        deque<T>::const_iterator end() {
            return {p, p->relativePosition(rear)};
        }
    private:
        const deque<T>* p;
        int front;
        int rear;
};

#endif  // __DEQUE_H
