#ifndef __DEQUE_H
#define __DEQUE_H

#include <iostream>
#include <cstddef>
#include <initializer_list>
#include <concepts>
#include "..\practice\print.h"
#include "..\practice\exceptions.h"

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
    static size_t max(size_t x, size_t y) {
        return (x > y) ? x : y;
    }
    static size_t min(size_t x, size_t y) {
        return (x < y) ? x : y;
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
        deque(): arr{new value_type[DEFAULT_SIZE + 1]}, front{}, cur{}, arr_size{DEFAULT_SIZE + 1} {}
        deque(size_t size) {
            this->initialize(max(size, DEFAULT_SIZE) + 1);
        }
        deque(size_t size, const value_type& default_value): deque(2 * size) {
            for (size_t i{}; i < size; ++i)
                this->arr[i] = default_value;
            if (size != 0)
                this->cur = size;
        }
        deque(const deque& src, size_t from, size_t to) {
            if ((from >= src.size()) || (to <= from)) {
                this->initialize(DEFAULT_SIZE + 1);
            }
            else {
                size_t src_size{src.size()}, dsize{};
                to = (to > src_size) ? (src_size - 1) : to;
                dsize = to - from + 1;
                this->initialize(2 * dsize + 1);
                this->cur = dsize;
                for (size_t i{}; i < dsize; ++i, ++from)
                    this->arr[i] = src[from];
            }
        }
        // Needs revising
        deque(const_iterator& from, const_iterator& to): deque(from.getSize()) {
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
            size_t i{};
            for (; iter != src.cend(); ++iter, ++i)
                this->arr[i] = *iter;
            this->cur = i;
        }
        deque(deque&& src) noexcept {
            this->set(src.arr, src.front, src.cur, src.arr_size);
            src.invalidate();
        }
        deque& operator=(const deque& src) {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->initialize(src.size() * 2);
                const_iterator iter = src.cbegin();
                size_t i{};
                for (; iter != src.cend(); ++iter, ++i)
                    this->arr[i] = *iter;
                this->cur = i;
            }
            return *this;
        }
        deque& operator=(deque&& src) noexcept {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->set(src.arr, src.front, src.cur, src.arr_size);
                src.invalidate();
            }
            return *this;
        }

        constexpr operator bool() const noexcept {
            return (!(this->cur));
        }
        constexpr bool isEmpty() const noexcept {
            return (!this->cur);
        }
        constexpr size_t size() const noexcept {
            return this->cur;
        }
        constexpr size_t capacity() const noexcept {
            return this->arr_size ? (this->arr_size - 1) : 0;
        }
        
        /**
         * Returns a modifiable reference to the first element of the list.
         * @note It will still return a reference to an item of the list even
         * if the list is empty so it might contain some garbage value.
         */
        reference getFront() noexcept {
            return this->arr[this->front];
        }
        /**
         * Returns a non-modifiable reference to the first element of the
         * list.
         * @note It will still return a reference to an item of the list even
         * if the list is empty so it might contain some garbage value.
         */
        const_reference getFront() const noexcept {
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
            this->arr[this->front] = static_cast<value_type&&>(item);
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
            this->arr[(this->front + this->cur) % this->arr_size] = static_cast<value_type&&>(item);
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
        deque& push_back(const std::initializer_list<value_type>& args) {
            auto it = args.begin();
            for (; it != args.end(); ++it)
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
            return this->push_front(item);
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
            return this->push_back(item);
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
         * This method removes an item from the front of the list.
         * Similar to the dequeue() operation of a Queue.
         */
        deque& pop_front() {
            if (this->isEmpty())
                throw DequeEmpty();
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
            if (this->isEmpty())
                throw DequeEmpty();
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
            this->arr[this->front] = static_cast<value_type&&>(value_type{args...});
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
            this->arr[(this->front + this->cur) % this->arr_size] = static_cast<T&&>(value_type{args...});
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
                size_t newSize = this->cur + 1;
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
        deque& modify(Modifier mod_fun = {}, Predicate pred = {}) noexcept {
            for (auto iter = this->begin(); iter != this->end(); ++iter)
                if (pred(*iter))
                    mod_fun(*iter);
            return *this;
        }
        deque& setValue(const value_type& val) noexcept {
            deque& self{*this};
            for (size_t i{}; i < self.size(); ++i)
                self[i] = val;
            return *this;
        }
        /**
         * Reverses the list.
         */
        deque& reverse() noexcept {
            reverse_iterator riter = this->rbegin();
            iterator iter = this->begin();
            for (size_t i{}; i < (this->cur / 2); ++i) {
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
        size_t search(const key_tp& key, Projection p = {}) const noexcept {
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                if (p(*it) == key)
                    return it.getPos();
            return ULLONG_MAX;
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
        size_t search(const key_tp& key, size_t fromPosition, Projection p = {}) const noexcept {
            if (fromPosition >= this->cur - 1)
                return ULLONG_MAX;
            const_iterator it{this, this->relativePosition(fromPosition)};
            for (; it != this->cend(); ++it)
                if (p(*it) == key)
                    return it.getPos();
            return ULLONG_MAX;
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
        view_iterator sliceView(size_t i, size_t j) noexcept {
            if (this->isEmpty() || isOutOfBounds(i) || (i >= j))
                return {this, 0, 0};
            return {this, i, min(j, this->cur)};
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
        view_iterator sliceView(size_t i) noexcept {
            if (this->isEmpty())
                return {this, 0, 0};
            return {this, 0, min(i, this->cur)};
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
        const_view_iterator sliceView(size_t i, size_t j) const noexcept {
            if (this->isEmpty() || isOutOfBounds(i) || (i >= j))
                return {this, 0, 0};
            return {this, i, min(j, this->cur)};
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
        const_view_iterator sliceView(size_t i) const noexcept {
            if (this->isEmpty())
                return {this, 0, 0};
            return {this, 0, min(i, this->cur)};
        }
        /**
         * Returns a new list containing the items from the existing list from
         * index i up to but not including index j.
         * @note Returns an empty list if the index values are not valid.
         */
        deque slice(size_t i, size_t j) const {
            if (this->isEmpty() || isOutOfBounds(i) || (i >= j))
                return {};
            deque res;
            const_iterator it{this, relativePosition(i)}, end{this, relativePosition(min(j, this->cur))};
            for (; it != end; ++it)
                res.append(*it);
            return res;
        }
        /**
         * Returns a new list containing the items from the existing list from
         * index 0 up to but not including index j.
         * @note Returns an empty list if the index values are not valid.
         */
        deque slice(size_t i) const {
            if (isOutOfBounds(i))
                return {*this};
            deque res;
            const_iterator it = this->cbegin(), end{this, relativePosition(min(i, this->cur))};
            for (; it != end; ++it)
                res.append(*it);
            return res;
        }

        iterator begin() noexcept {
            return {this, this->front};
        }
        iterator end() noexcept {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        const_iterator begin() const noexcept {
            return {this, this->front};
        }
        const_iterator end() const noexcept {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        const_iterator cbegin() const noexcept {
            return {this, this->front};
        }
        const_iterator cend() const noexcept {
            return {this, (this->front + this->cur) % this->arr_size};
        }
        reverse_iterator rbegin() noexcept {
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            return this->rend();
        }
        reverse_iterator rend() noexcept {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
        }
        const_reverse_iterator rbegin() const noexcept {
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            return this->rend();
        }
        const_reverse_iterator rend() const noexcept {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
        }
        const_reverse_iterator crbegin() const noexcept {
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            return this->crend();
        }
        const_reverse_iterator crend() const noexcept {
            int pos = (this->front + this->arr_size - 1) % this->arr_size;
            return {this, pos};
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
        view_iterator operator()(size_t i, size_t j) noexcept {
            if (this->isEmpty() || isOutOfBounds(i) || (i >= j))
                return {this, 0, 0};
            return {this, i, min(j, this->cur)};
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
        view_iterator operator()(size_t i) noexcept {
            if (this->isEmpty())
                return {this, 0, 0};
            return {this, 0, min(i, this->cur)};
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
        const_view_iterator operator()(size_t i, size_t j) const noexcept {
            if (this->isEmpty() || isOutOfBounds(i) || (i >= j))
                return {this, 0, 0};
            return {this, i, min(j, this->cur)};
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
        const_view_iterator operator()(size_t i) const noexcept {
            if (this->isEmpty())
                return {this, 0, 0};
            return {this, 0, min(i, this->cur)};
        }
        /**
         * Returns a reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        reference operator[](size_t i) noexcept {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Returns a const reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        const_reference operator[](size_t i) const noexcept {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(const value_type& item) {
            return this->push_back(item);
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(value_type&& item) {
            return this->push_back(item);
        }
        /**
         * Inserts all the items from a deque containing the same type of
         * items at the back of the list.
         * @note This method delegates to the push_back() method.
         */
        deque& operator+=(const deque& d) {
            return this->push_back(d);
        }
        
        // DBG
        /**
         * Displays the values for the front, rear, current size, and total
         * capacity of the deque.
         * @note The rear is calculated and not stored.
         */
        void __print_status() const noexcept {
            printf("(Front: %llu, Rear: %llu, Cur: %llu, size: %llu)\n", front, (front + cur) % (arr_size + 1), cur, arr_size);
        }
        /**
         * Prints the contents of the entire containing array.
         */
        void __print_array() const noexcept {
            std::cout << '[';
            for (size_t i{}; i < this->arr_size; ++i)
                std::cout << this->arr[i] << ", ";
            std::cout << this->arr[this->arr_size] << ']';
        }

        ~deque() noexcept {
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
        size_t Front() const {
            return this->front;
        }
        size_t Cur() const {
            return this->cur;
        }
        void setFront(size_t f) {
            this->front = f;
        }
        void setCur(size_t c) {
            this->cur = c;
        }

    private:
        value_type* arr{};
        size_t front{};
        size_t cur{};
        size_t arr_size{};

        void streamInsert(std::ostream& out) const noexcept {
            out << '[';
            if (this->cur) {
                size_t i{this->front}, count{};
                for (; count < this->cur - 1; ++count, i = (i + 1) % this->arr_size)
                    out << this->arr[i] << ", ";
                out << this->arr[i];
            }
            else if (this->arr == nullptr)
                out << "null";
            out << ']';
        }
        constexpr bool isFull() const noexcept {
            return (this->cur == this->arr_size - 1);
        }
        constexpr bool isVacant() const noexcept {
            return (this->cur == this->arr_size / 3);
        }
        bool isOutOfBounds(size_t index) const noexcept {
            return (index > this->cur - 1);
        }
        /**
         * Set the value of all member variables one by one in sequence.
         * @param arr
         * @param front
         * @param cur
         * @param arr_size
         */
        void set(pointer _arr, size_t _front, size_t _cur, size_t _arr_size) noexcept {
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
        void initialize(size_t _size) {
            this->set(new value_type[_size], 0, 0, _size);
        }
        /**
         * Grows or shrinks the containing array according to the value of the
         * flag parameter.
         * @param flag Must be one out of the two static constants defined in
         * the class, deque::EXPAND or deque::SHRINK.
         */
        void alter(size_t flag) {
            pointer newArray{};
            size_t i{}, newSize{};
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
            this->set({}, {}, {}, {});
        }
        /**
         * Swap elements at indices i and j in the containing array.
         */
        void swap(size_t i, size_t j) noexcept {
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
        size_t relativePosition(size_t i) const noexcept {
            return (this->front + i) % this->arr_size;
        }
};

template<typename U>
inline std::ostream& operator<<(std::ostream& out, const deque<U>& d) {
    d.streamInsert(out);
    return out;
}

template<typename T>
void det(const deque<T>& d) noexcept {
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
        iterator(deque* ptr, size_t i): p{ptr}, pos{i} {}
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
        constexpr size_t getPos() {
            return this->pos;
        }
    
    private:
        deque* p;
        size_t pos;
};

/**
 * const iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::const_iterator {
    public:
        const_iterator(const deque* ptr, size_t i): p{ptr}, pos{i} {}
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
        constexpr size_t getPos() {
            return this->pos;
        }
        constexpr size_t getSize() {
            return p->size();
        }

    private:
        const deque* p;
        size_t pos;
};

/**
 * Reverse iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::reverse_iterator {
    public:
        reverse_iterator(deque* ptr, size_t i): p{ptr}, pos{i} {}
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
        constexpr size_t getPos() {
            return this->pos;
        }
    
    private:
        deque* p;
        size_t pos;
};

/**
 * const reverse iterator for the deque class.
 * @note Iterator type: Bidirectional
 */
template<typename T>
class deque<T>::const_reverse_iterator {
    public:
        const_reverse_iterator(const deque* ptr, size_t i): p{ptr}, pos{i} {}
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
        constexpr size_t getPos() {
            return this->pos;
        }
    
    private:
        const deque* p;
        size_t pos;
};

/**
 * View iterator for iterating through a view of the deque.
 */
template<typename T>
class deque<T>::view_iterator {
    public:
        view_iterator(deque<T>* ptr, size_t i, size_t j): p{ptr}, front{i}, rear{j} {}
        deque<T>::iterator begin() {
            return {p, p->relativePosition(front)};
        }
        deque<T>::iterator end() {
            return {p, p->relativePosition(rear)};
        }
    private:
        deque<T>* p;
        size_t front;
        size_t rear;
};
/**
 * const view iterator for iterating through a view of the deque.
 */
template<typename T>
class deque<T>::const_view_iterator {
    public:
        const_view_iterator(const deque<T>* ptr, size_t i, size_t j): p{ptr}, front{i}, rear{j} {}
        deque<T>::const_iterator begin() {
            return {p, p->relativePosition(front)};
        }
        deque<T>::const_iterator end() {
            return {p, p->relativePosition(rear)};
        }
    private:
        const deque<T>* p;
        size_t front;
        size_t rear;
};

#endif  // __DEQUE_H
