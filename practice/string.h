#ifndef __STRING_H
#define __STRING_H

#include <fstream>
#include <cctype>
#include <initializer_list>
#include "print.h"
#include "compact_string.h"

class String {
    static const std::size_t DEFAULT_SIZE{8};
    static const std::size_t SHRINK{};
    static const std::size_t EXPAND{1};
    struct Tautology {
        bool operator()(const char&) {
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
    static std::size_t max(std::size_t x, std::size_t y) {
        return (x > y) ? x : y;
    }
    typedef int (*check_fun)(int);
    
    public:
        typedef                         char                      value_type;
        typedef                  value_type*                      pointer;
        typedef                  value_type&                      reference;
        typedef            const value_type*                      const_pointer;
        typedef            const value_type&                      const_reference;
        typedef                deque<String>                      StringList;
        class iterator {
            public:
                iterator(String* ptr, std::size_t i): p{ptr}, pos{i} {}
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
                std::size_t getPos() {
                    return this->pos;
                }
            
            private:
                String* p;
                std::size_t pos;
        };
        class const_iterator {
            public:
                const_iterator(const String* ptr, std::size_t i): p{ptr}, pos{i} {}
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
                std::size_t getPos() {
                    return this->pos;
                }
                std::size_t getSize() {
                    return p->size();
                }

            private:
                const String* p;
                std::size_t pos;
        };
        class reverse_iterator {
            public:
                reverse_iterator(String* ptr, std::size_t i): p{ptr}, pos{i} {}
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
                std::size_t getPos() {
                    return this->pos;
                }
            
            private:
                String* p;
                std::size_t pos;
        };
        class const_reverse_iterator {
            public:
                const_reverse_iterator(const String* ptr, std::size_t i): p{ptr}, pos{i} {}
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
                std::size_t getPos() {
                    return this->pos;
                }
            
            private:
                const String* p;
                std::size_t pos;
        };
        class view_iterator {
            public:
                view_iterator(String* ptr, std::size_t i, std::size_t j): p{ptr}, front{i}, rear{j} {}
                String::iterator begin() {
                    return {p, p->__relativePosition(front)};
                }
                String::iterator end() {
                    return {p, p->__relativePosition(rear)};
                }
            private:
                String* p;
                std::size_t front;
                std::size_t rear;
        };
        class const_view_iterator {
            public:
                const_view_iterator(const String* ptr, std::size_t i, std::size_t j): p{ptr}, front{i}, rear{j} {}
                String::const_iterator begin() {
                    return {p, p->__relativePosition(front)};
                }
                String::const_iterator end() {
                    return {p, p->__relativePosition(rear)};
                }
            private:
                const String* p;
                std::size_t front;
                std::size_t rear;
        };
    
    public:
        String() : arr{new value_type[DEFAULT_SIZE + 1]}, front{}, cur{}, arr_size{DEFAULT_SIZE + 1} {}
        String(std::size_t size) {
            this->__initialize(max(size, DEFAULT_SIZE) + 1);
        }
        String(std::size_t size, value_type default_value): String(2 * size) {
            for (std::size_t i{}; i < size; ++i)
                this->arr[i] = default_value;
            if (size >= 0)
                this->cur = size;
        }
        String(const String& src, std::size_t from, std::size_t to) {
            if ((from >= src.size()) || (to <= from)) {
                this->__initialize(DEFAULT_SIZE + 1);
            }
            else {
                std::size_t src_size{src.size()}, dsize{};
                to = (to > src_size) ? (src_size - 1) : to;
                dsize = to - from + 1;
                this->__initialize(2 * dsize + 1);
                this->cur = dsize;
                for (std::size_t i{}; i < dsize; ++i, ++from)
                    this->arr[i] = src[from];
            }
        }
        String(const_iterator& from, const_iterator& to): String(2 * from.getSize()) {
            std::size_t i{};
            for (; from != to; ++from, ++i)
                this->arr[i] = *from;
            this->cur = i;
        }
        String(const_iterator&& from, const_iterator&& to): String(from, to) {}
        String(const char* str): String() {
            for (; *str; ++str)
                this->push_back(*str);
        }
        String(const CompactString& src): String(src.size() * 2) {
            CompactString::const_iterator it = src.cbegin();
            size_t i{};
            for (; it != src.cend(); ++it, ++i)
                this->arr[i] = *it;
            this->cur = i;
        }
        String(const String& src): String(src.size() * 2) {
            const_iterator iter = src.cbegin();
            std::size_t i{};
            for (; iter != src.cend(); ++iter, ++i)
                this->arr[i] = *iter;
            this->cur = i;
        }
        String(String&& src) noexcept {
            this->__set(src.arr, src.front, src.cur, src.arr_size);
            src.__invalidate();
        }
        String& operator=(const String& src) noexcept {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->__initialize(src.size() * 2);
                const_iterator iter = src.cbegin();
                std::size_t i{};
                for (; iter != src.cend(); ++iter, ++i)
                    this->arr[i] = *iter;
                this->cur = i;
            }
            return *this;
        }
        String& operator=(String&& src) noexcept {
            if (this != &src) {
                if (this->arr)
                    delete[] this->arr;
                this->__set(src.arr, src.front, src.cur, src.arr_size);
                src.__invalidate();
            }
            return *this;
        }

        constexpr bool isEmpty() const noexcept {
            return (!this->cur);
        }
        constexpr std::size_t size() const noexcept {
            return this->cur;
        }
        constexpr std::size_t capacity() const noexcept {
            return (this->arr_size) ? (this->arr_size - 1) : 0;
        }

        void swap(String& rhs) noexcept {
            value_type* larr = this->arr;
            size_t lfront = this->front;
            size_t lcur = this->cur;
            size_t larr_size = this->arr_size;
            this->__set(rhs.arr, rhs.front, rhs.cur, rhs.arr_size);
            rhs.__set(larr, lfront, lcur, larr_size);
        }
        
        String& push_front(value_type item) {
            if (this->__isFull())
                this->__alter(EXPAND);
            this->front = (this->front + this->arr_size - 1) % this->arr_size;
            this->arr[this->front] = item;
            ++(this->cur);
            return *this;
        }
        String& push_front(const char* str) {
            const char* ptr = str;
            for (; *ptr; ++ptr);
            for (--ptr; ptr >= str; --ptr)
                this->push_front(*ptr);
            return *this;
        }
        String& push_front(const String& d) {
            const_reverse_iterator it = d.crbegin();
            for (; it != d.crend(); ++it)
                this->push_front(*it);
            return *this;
        }
        template<ReverseIterable Container>
        String& push_front(const Container& c) {
            static_assert(
                std::is_convertible_v<typename Container::value_type, typename String::value_type>,
                "Contents of the Container cannot be interpreted as characters\n"
            );
            auto it = std::rbegin(c);
            auto rend = std::rend(c);
            for (; it != rend; ++it)
                this->push_front(*it);
            return *this;
        }
        String& push_back(value_type item) {
            if (this->__isFull())
                this->__alter(EXPAND);
            this->arr[(this->front + this->cur) % this->arr_size] = item;
            ++(this->cur);
            return *this;
        }
        String& push_back(const char* str) {
            for (; *str; ++str)
                this->push_back(*str);
            return *this;
        }
        String& push_back(const String& d) {
            const_iterator it = d.cbegin();
            for (; it != d.cend(); ++it)
                this->push_back(*it);
            return *this;
        }
        String& push_back(const std::initializer_list<value_type>& args) {
            auto it = args.begin();
            for (; it != args.end(); ++it)
                this->push_back(*it);
            return *this;
        }
        template<ForwardIterable Container>
        String& push_back(const Container& c) {
            static_assert(
                std::is_convertible_v<typename Container::value_type, typename String::value_type>,
                "Contents of the Container cannot be interpreted as characters\n"
            );
            auto it = std::begin(c);
            auto end = std::end(c);
            for (; it != end; ++it)
                this->push_back(*it);
            return *this;
        }
        
        String& prepend(value_type item) {
            return this->push_front(item);
        }
        String& prepend(const char* str) {
            return this->push_front(str);
        }
        String& prepend(const String& d) {
            return this->push_front(d);
        }
        template<ReverseIterable Container>
        String& prepend(const Container& c) {
            return this->push_front<Container>(c);
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        String& append(value_type item) {
            return this->push_back(item);
        }
        String& append(const char* str) {
            return this->push_back(str);
        }
        String& append(const String& d) {
            return this->push_back(d);
        }
        template<ForwardIterable Container>
        String& append(const Container& c) {
            return this->push_back<Container>(c);
        }
        
        String& pop_front() {
            if (this->__isVacant())
                this->__alter(SHRINK);
            if (this->cur) {
                this->front = ((this->front + 1) % this->arr_size);
                --(this->cur);
            }
            return *this;
        }
        String& pop_back() {
            if (this->__isVacant())
                this->__alter(SHRINK);
            if (this->cur)
                --(this->cur);
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
        String& shrink_to_fit() {
            if (this->isEmpty()) {
                delete[] this->arr;
                this->__initialize(DEFAULT_SIZE + 1);
            }
            else {
                std::size_t newSize = this->cur + 1;
                pointer newArray = new value_type[newSize];
                pointer ptr = newArray;
                iterator iter = this->begin();
                for (; iter != this->end(); ++iter, ++ptr)
                    *ptr = *iter;
                delete[] this->arr;
                this->__set(newArray, {}, this->cur, newSize);
            }
            return *this;
        }
        /**
         * Modifies the items of the list which satisfy the Predicate
         * according to the function like entity mod_fun.
         * @param mod_fun Function like entity that can accept an item of the
         * list and returns an item of the same type. So if the deque holds
         * std::size_t values then the mod_fun must have a signature: std::size_t mod_fun(int).
         * The value returned by mod_fun will replace the original value
         * present in the deque.
         * @param pred Function like entity that can accept an item of the
         * list and returns a boolean result that will decide whether that
         * item gets modified or not;
         */
        template<typename Modifier, typename Predicate = Tautology>
        String& modify(Modifier mod_fun = {}, Predicate pred = {}) {
            for (auto iter = this->begin(); iter != this->end(); ++iter)
                if (pred(*iter))
                    *iter = mod_fun(*iter);
            return *this;
        }
        String& setValue(value_type val) {
            String& self{*this};
            for (std::size_t i{}; i < self.size(); ++i)
                self[i] = val;
            return *this;
        }
        /**
         * Reverses the string.
         */
        String& reverse() {
            reverse_iterator riter = this->rbegin();
            iterator iter = this->begin();
            for (std::size_t i{}; i < (this->cur / 2); ++i) {
                this->__swap(iter.getPos(), riter.getPos());
                ++riter;
                ++iter;
            }
            return *this;
        }
        String reversed() const {
            const_reverse_iterator it = this->crbegin();
            String tmp(this->size());
            for (; it != this->crend(); ++it)
                tmp.push_back(*it);
            return tmp;
        }

        bool similar(const char* str) const {
            const_iterator it = this->cbegin();
            for (; it != this->cend() && *str; ++it, ++str)
                if (std::tolower(*it) != std::tolower(*str))
                    return false;
            if (it != this->cend() || *str)
                return false;
            return true;
        }
        bool similar(const String& str) const {
            if (this->size() != str.size())
                return false;
            const_iterator it = this->cbegin();
            const_iterator s_it = str.cbegin();
            for (; it != this->cend(); ++it, ++s_it)
                if (std::tolower(*it) != std::tolower(*s_it))
                    return false;
            if (it != this->cend() || s_it != str.cend())
                return false;
            return true;
        }
        bool similar(const CompactString& rhs) const {
            if (this->size() != rhs.size())
                return false;
            const_iterator it = this->cbegin();
            CompactString::const_iterator rit = rhs.cbegin();
            for (; it != this->cend(); ++it, ++rit)
                if (std::tolower(*it) != std::tolower(*rit))
                    return false;
            if (it != this->cend() || rit != rhs.cend())
                return false;
            return true;
        }
        String& replace(char toReplace, char replacementChar) {
            for (iterator it = this->begin(); it != this->end(); ++it)
                if (*it == toReplace)
                    *it = replacementChar;
            return *this;
        }
        
        bool isAlpha() const {
            return this->__checkString(std::isalpha);
        }
        bool isAlnum() const {
            return this->__checkString(std::isalnum);
        }
        bool isNumeric() const {
            return this->__checkString(std::isdigit);
        }

        String first_word() const {
            const_iterator it = this->__skipwf();
            String tmp{};
            for (; it != this->cend() && !__isWhiteSpace(*it); ++it)
                tmp.push_back(*it);
            return tmp;
        }
        String last_word() const {
            const_reverse_iterator it = this->__skipwr();
            String tmp{};
            for (; it != this->crend() && !__isWhiteSpace(*it); ++it)
                tmp.push_front(*it);
            return tmp;
        }
        String get_lower() const {
            return this->__getModifiedString(std::tolower);
        }
        String get_upper() const {
            return this->__getModifiedString(std::toupper);
        }
        String& to_lower() {
            return this->__modifyString(std::tolower);
        }
        String& to_upper() {
            return this->__modifyString(std::toupper);
        }
        String& capitalize() {
            iterator it = this->__skipwf();
            if (it != this->end())
                *it = std::toupper(*it);
            return *this;
        }
        String& title() {
            iterator it = this->__skipwf();
            if (it != this->end()) {
                *it = std::toupper(*it);
                for (++it; it != this->end(); ++it) {
                    if(__isWhiteSpace(*it)) {
                        for (; it != this->end() && __isWhiteSpace(*it); ++it);
                        *it = std::toupper(*it);
                    }
                    else
                        *it = std::tolower(*it);
                }
            }
            return *this;
        }
        String& collapse() {
            if (this->isEmpty())
                return *this;
            iterator it = this->__skipwf();
            iterator end = this->end();
            if (it == end) {
                delete[] this->arr;
                this->__initialize(DEFAULT_SIZE + 1);
                return *this;
            }
            for (--end; end != it && __isWhiteSpace(*end); --end);
            std::size_t i{};
            for (++end; it != end; ++it) {
                if (__isWhiteSpace(*it)) {
                    for (; it != end && __isWhiteSpace(*it); ++it);
                    this->arr[i] = ' ';
                    i = (i + 1) % this->arr_size;
                }
                this->arr[i] = *it;
                i = (i + 1) % this->arr_size;
            }
            this->front = 0;
            this->cur = i;
            return *this;
        }
        String collapsed() const {
            if (this->isEmpty())
                return {};
            String tmp{};
            const_iterator it = this->__skipwf();
            const_iterator end = this->cend();
            if (it == end)
                return {};
            for (--end; end != it && __isWhiteSpace(*end); --end);
            for (++end; it != end; ++it) {
                if (__isWhiteSpace(*it)) {
                    for (; it != end && __isWhiteSpace(*it); ++it);
                    tmp.push_back(' ');
                }
                tmp.push_back(*it);
            }
            return tmp;
        }
        
        std::size_t search(value_type key) const {
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                if (*it == key)
                    return it.getPos();
            return -1;
        }
        std::size_t search(value_type key, std::size_t fromPosition) const {
            if (this->__isOutOfBounds(fromPosition))
                throw IndexError();
            const_iterator it{this, this->__relativePosition(fromPosition)};
            for (; it != this->cend(); ++it)
                if (*it == key)
                    return it.getPos();
            return -1;
        }
        
        view_iterator sliceView(std::size_t i, std::size_t j) {
            if (__isOutOfBounds(i) || __isOutOfBounds(j) || (i >= j))
                throw IndexError();
            return {this, i, j};
        }
        view_iterator sliceView(std::size_t i) {
            if (__isOutOfBounds(i))
                throw IndexError();
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        const_view_iterator sliceView(std::size_t i, std::size_t j) const {
            if (__isOutOfBounds(i) || __isOutOfBounds(j) || (i >= j))
                throw IndexError();
            return {this, i, j};
        }
        const_view_iterator sliceView(std::size_t i) const {
            if (__isOutOfBounds(i))
                throw IndexError();
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        String slice(std::size_t i, std::size_t j) const {
            if (__isOutOfBounds(i) || __isOutOfBounds(j) || (i >= j))
                throw IndexError();
            String res;
            const_iterator it{this, __relativePosition(i)}, end{this, __relativePosition(j)};
            for (; it != end; ++it)
                res.append(*it);
            return res;
        }
        String slice(std::size_t j) const {
            if (__isOutOfBounds(j))
                throw IndexError();
            String res{};
            const_iterator it{this, __relativePosition(0)}, end{this, __relativePosition(j)};
            for (; it != end; ++it)
                res.append(*it);
            return res;
        }
        String from_pos(std::size_t pos) const {
            if (__isOutOfBounds(pos))
                throw IndexError();
            const_iterator it{this, __relativePosition(pos)};
            String res{};
            for (; it != this->end(); ++it)
                res.append(*it);
            return res;
        }
        String nlast(std::size_t n) const {
            if (n > this->cur)
                throw ArgError();
            return this->from_pos(this->cur - n);
        }
        String& lstrip() {
            if (this->isEmpty())
                return *this;
            iterator it = this->begin();
            std::size_t count{};
            for (; it != this->end() && __isWhiteSpace(*it); ++it, ++count);
            if (it == this->end()) {
                delete[] this->arr;
                this->__initialize(DEFAULT_SIZE + 1);
                return *this;
            }
            this->front = it.getPos();
            this->cur -= count;
            return *this;
        }
        String& rstrip() {
            if (this->isEmpty())
                return *this;
            iterator end = {this, __relativePosition(this->cur - 1)}, begin = this->begin();
            std::size_t count{};
            for (--begin; end != begin && __isWhiteSpace(*end); --end, ++count);
            if (end == begin) {
                delete[] this->arr;
                this->__initialize(DEFAULT_SIZE + 1);
                return *this;
            }
            this->cur -= count;
            return *this;
        }
        String& strip() {
            return this->lstrip().rstrip();
        }

        std::size_t stoi() const {
            try {
                return static_cast<int>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        long stol() const {
            try {
                return static_cast<long>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        long long stoll() const {
            try {
                return static_cast<long long>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        unsigned int stoui() const {
            try {
                return static_cast<unsigned int>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        unsigned long stoul() const {
            try {
                return static_cast<unsigned long>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        unsigned long long stoull() const {
            try {
                return static_cast<unsigned long long>(this->stod());
            } catch(ValueError&) {
                throw ValueError("Invalid character encountered in integer literal");
            }
        }
        double stod() const {
            if (this->isEmpty())
                return 0;
            double num{};
            bool isNegative{};
            const_iterator it = this->cbegin(), end = this->cend();
            if (*it == '-') {
                isNegative = true;
                ++it;
            }
            else if (*it == '+') {
                isNegative = false;
                ++it;
            }
            for (; it != end && *it != '.'; ++it) {
                if (std::isdigit(*it))
                    num = ((num * 10) + *it - '0');
                else
                    throw ValueError();
            }
            if (it != end) {
                ++it;
                for (double div{10}; it != end; ++it, div *= 10) {
                    if (std::isdigit(*it))
                        num += ((*it - '0') / div);
                    else
                        throw ValueError();
                }
            }
            return isNegative ? -num : num;
        }
        float stof() const {
            if (this->isEmpty())
                return 0;
            float num{};
            bool isNegative{};
            const_iterator it = this->cbegin(), end = this->cend();
            if (*it == '-') {
                isNegative = true;
                ++it;
            }
            else if (*it == '+') {
                isNegative = false;
                ++it;
            }
            for (; it != end &&  *it != '.'; ++it) {
                if (std::isdigit(*it))
                    num = ((num * 10) + *it - '0');
                else
                    throw ValueError();
            }
            if (it != end) {
                ++it;
                for (float div{10}; it != end; ++it, div *= 10) {
                    if (std::isdigit(*it))
                        num += ((*it - '0') / div);
                    else
                        throw ValueError();
                }
            }
            return isNegative ? -num : num;
        }
        long double stold() const {
            if (this->isEmpty())
                return 0;
            long double num{};
            bool isNegative{};
            const_iterator it = this->cbegin(), end = this->cend();
            if (*it == '-') {
                isNegative = true;
                ++it;
            }
            else if (*it == '+') {
                isNegative = false;
                ++it;
            }
            for (; it != end &&  *it != '.'; ++it) {
                if (std::isdigit(*it))
                    num = ((num * 10) + *it - '0');
                else
                    throw ValueError();
            }
            if (it != end) {
                ++it;
                for (long double div{10}; it != end; ++it, div *= 10) {
                    if (std::isdigit(*it))
                        num += ((*it - '0') / div);
                    else
                        throw ValueError();
                }
            }
            return isNegative ? -num : num;
        }
        explicit operator int() const {
            return this->stoi();
        }
        explicit operator long() const {
            return this->stol();
        }
        explicit operator long long() const {
            return this->stoll();
        }
        explicit operator unsigned int() const {
            return this->stoui();
        }
        explicit operator unsigned long() const {
            return this->stoul();
        }
        explicit operator unsigned long long() const {
            return this->stoull();
        }
        explicit operator float() const {
            return this->stof();
        }
        explicit operator double() const {
            return this->stod();
        }
        explicit operator long double() const {
            return this->stold();
        }
        operator bool() const {
            return (this->cur);
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
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            else
                return {this, this->front};
        }
        reverse_iterator rend() {
            if (this->cur)
                return {this, (this->front + this->arr_size - 1) % this->arr_size};
            else
                return {this, this->front};
        }
        const_reverse_iterator rbegin() const {
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            else
                return {this, this->front};
        }
        const_reverse_iterator rend() const {
            if (this->cur)
                return {this, (this->front + this->arr_size - 1) % this->arr_size};
            else
                return {this, this->front};
        }
        const_reverse_iterator crbegin() const {
            if (this->cur)
                return {this, (this->front + this->cur - 1) % this->arr_size};
            else
                return {this, this->front};
        }
        const_reverse_iterator crend() const {
            if (this->cur)
                return {this, (this->front + this->arr_size - 1) % this->arr_size};
            else
                return {this, this->front};
        }

        view_iterator operator()(std::size_t i, std::size_t j) {
            if (__isOutOfBounds(i) || __isOutOfBounds(j) || (i >= j))
                throw IndexError();
            return {this, i, j};
        }
        view_iterator operator()(std::size_t i) {
            if (__isOutOfBounds(i))
                throw IndexError();
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        const_view_iterator operator()(std::size_t i, std::size_t j) const {
            if (__isOutOfBounds(i) || __isOutOfBounds(j) || (i >= j))
                throw IndexError();
            return {this, i, j};
        }
        const_view_iterator operator()(std::size_t i) const {
            if (__isOutOfBounds(i))
                throw IndexError();
            if (i >= this->cur - 1)
                return {this, 0, this->cur - 1};
            return {this, 0, i};
        }
        /**
         * Returns a reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        reference operator[](std::size_t i) {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Returns a const reference to an object at index i in the list.
         * @note The operator[] does not perform bounds checking.
         */
        const_reference operator[](std::size_t i) const {
            return this->arr[(this->front + i) % this->arr_size];
        }
        /**
         * Insert an item at the back of the list.
         * Similar to the push() operation of a Stack.
         * @note This method delegates to the push_back() method.
         */
        String& operator+=(value_type item) {
            return this->push_back(item);
        }
        /**
         * Inserts all the items from a String containing the same type of
         * items at the back of the list.
         * @note This method delegates to the push_back() method.
         */
        String& operator+=(const String& d) {
            return this->push_back(d);
        }
        String& operator+=(const char* str) {
            return this->push_back(str);
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
        String& operator+=(const Container& c) {
            return this->push_back<Container>(c);
        }

        String operator+(value_type ch) const {
            String tmp{*this};
            tmp.push_back(ch);
            return tmp;
        }
        String operator+(const char* str) const {
            String tmp{*this};
            tmp.push_back(str);
            return tmp;
        }
        String operator+(const String& str) const {
            String tmp{*this};
            tmp.push_back(str);
            return tmp;
        }
        friend String operator+(const char* lhs, const String& rhs) {
            String res{lhs};
            res.push_back(rhs);
            return res;
        }

        std::strong_ordering operator<=>(const String& rhs) const {
            const_iterator it = this->cbegin();
            const_iterator rit = rhs.cbegin();
            int diff{};
            for (; it != this->cend() && rit != rhs.cend() && (diff == 0); ++it, ++rit) {
                diff = static_cast<int>(*it) - static_cast<int>(*rit);
            }
            if (diff == 0) {
                if (it != this->cend())
                    return std::strong_ordering::greater;
                else if (rit != rhs.cend())
                    return std::strong_ordering::less;
                else
                    return std::strong_ordering::equal;
            }
            else if (diff < 0)
                return std::strong_ordering::less;
            else
                return std::strong_ordering::greater;
        }
        std::strong_ordering operator<=>(const CompactString& rhs) const {
            const_iterator it = this->cbegin();
            CompactString::const_iterator rit = rhs.cbegin();
            int diff{};
            for (; it != this->cend() && rit != rhs.cend() && (diff == 0); ++it, ++rit) {
                diff = static_cast<int>(*it) - static_cast<int>(*rit);
            }
            if (diff == 0) {
                if (it != this->cend())
                    return std::strong_ordering::greater;
                else if (rit != rhs.cend())
                    return std::strong_ordering::less;
                else
                    return std::strong_ordering::equal;
            }
            else if (diff < 0)
                return std::strong_ordering::less;
            else
                return std::strong_ordering::greater;
        }
        friend std::strong_ordering operator<=>(const CompactString& lhs, const String& rhs) {
            CompactString::const_iterator lit = lhs.cbegin();
            const_iterator rit = rhs.cbegin();
            int diff{};
            for (; lit != lhs.cend() && rit != rhs.cend() && (diff == 0); ++lit, ++rit)
                diff = static_cast<int>(*lit) - static_cast<int>(*rit);
            if (diff == 0) {
                if (lit != lhs.cend())
                    return std::strong_ordering::greater;
                else if (rit != rhs.cend())
                    return std::strong_ordering::less;
                else
                    return std::strong_ordering::equal;
            }
            else if (diff < 0)
                return std::strong_ordering::less;
            else
                return std::strong_ordering::greater;
        }
        std::strong_ordering operator<=>(const char* rhs) const {
            if (rhs == nullptr)
                return std::strong_ordering::greater;
            const_iterator it = this->cbegin();
            int diff{};
            for (; it != this->cend() && *rhs && (diff == 0); ++it, ++rhs)
                diff = static_cast<int>(*it) - static_cast<int>(*rhs);
            if (diff == 0) {
                if (it != this->cend())
                    return std::strong_ordering::greater;
                else if (*rhs)
                    return std::strong_ordering::less;
                else
                    return std::strong_ordering::equal;
            }
            else if (diff < 0)
                return std::strong_ordering::less;
            else
                return std::strong_ordering::greater;
        }
        friend std::strong_ordering operator<=>(const char* lhs, const String& rhs) {
            if (lhs == nullptr)
                return std::strong_ordering::less;
            const_iterator rit = rhs.cbegin();
            int diff{};
            for (; *lhs && rit != rhs.cend() && (diff == 0); ++lhs, ++rit)
                diff = static_cast<int>(*lhs) - static_cast<int>(*rit);
            if (diff == 0) {
                if (*lhs)
                    return std::strong_ordering::greater;
                else if (rit != rhs.cend())
                    return std::strong_ordering::less;
                else
                    return std::strong_ordering::equal;
            }
            else if (diff < 0)
                return std::strong_ordering::less;
            else
                return std::strong_ordering::greater;
        }

        bool operator==(const String& rhs) const {
            if (this->size() != rhs.size())
                return false;
            const_iterator it = this->cbegin();
            const_iterator rit = rhs.cbegin();
            for (; it != this->cend(); ++it, ++rit)
                if (*it != *rit)
                    return false;
            return true;
        }

        bool operator==(const CompactString& rhs) const {
            if (this->size() != rhs.size())
                return false;
            const_iterator it = this->cbegin();
            CompactString::const_iterator rit = rhs.cbegin();
            for (; it != this->cend(); ++it, ++rit)
                if (*it != *rit)
                    return false;
            return true;
        }
        friend bool operator==(const CompactString& lhs, const String& rhs) {
            if (lhs.size() != rhs.size())
                return false;
            CompactString::const_iterator lit = lhs.cbegin();
            const_iterator rit = rhs.cbegin();
            for (; lit != lhs.cend(); ++lit, ++rit)
                if (*lit != *rit)
                    return false;
            return true;
        }

        bool operator==(const char* rhs) const {
            if (rhs == nullptr)
                return false;
            const_iterator it = this->cbegin();
            for (; it != this->cend() && *rhs; ++it, ++rhs)
                if (*it != *rhs)
                    return false;
            if (it != this->cend() || *rhs)
                return false;
            return true;
        }
        friend bool operator==(const char* lhs, const String& rhs) {
            if (lhs == nullptr)
                return false;
            const_iterator rit = rhs.begin();
            for (; *lhs && rit != rhs.cend(); ++lhs, ++rit)
                if (*lhs != *rit)
                    return false;
            if (*lhs || rit != rhs.cend())
                return false;
            return true;
        }

        // DBG
        /**
         * Displays the values for the front, rear, current size, and total
         * capacity of the String.
         * @note The rear is calculated and not stored.
         */
        void __print_status() const {
            printf("(Front: %lld, Rear: %lld, Cur: %lld, size: %lld)\n", front, (front + cur) % (arr_size + 1), cur, arr_size);
        }
        /**
         * Prints the contents of the entire containing array.
         */
        void __print_array() const {
            std::cout << '[';
            for (std::size_t i{}; i < this->arr_size; ++i)
                std::cout << this->arr[i] << ", ";
            std::cout << this->arr[this->arr_size] << ']';
        }

        ~String() {
            if (this->arr) {
                delete[] this->arr;
                this->__invalidate();
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const String& d);
        friend std::istream& operator>>(std::istream& in, String& str) {
            str.__initializeForReading();
            for (char ch = in.get(); ch != '\n'; ch = in.get())
                str.push_back(ch);
            return in;
        }
        friend std::ifstream& operator>>(std::ifstream& in, String& s) {
            if (!in)
                throw FileInputError();
            s.__initializeForReading();
            for (char ch = in.get(); !in.eof(); ch = in.get())
                s.push_back(ch);
            in.clear();
            return in;
        }
        bool getline(std::ifstream& file) {
            this->__initializeForReading();
            for (char ch = file.get(); ch != '\n' && file; ch = file.get())
                this->push_back(ch);
            return static_cast<bool>(file);
        }
        static bool getline(std::ifstream& file, String& str) {
            str.__initializeForReading();
            for (char ch = file.get(); ch != '\n' && file; ch = file.get())
                str.push_back(ch);
            return static_cast<bool>(file);
        }
        String& get(std::istream& in) {
            this->__initializeForReading();
            for (char ch = in.get(); ch != 4; ch = in.get())
                this->push_back(ch);
            return *this;
        }
        StringList split(char delim = ' ') const {
            if (this->isEmpty())
                return {};
            StringList parts{};
            for (const_iterator it = this->cbegin(), end = this->cend(); it != end; ++it) {
                String part{};
                for (; it != end && *it != delim; ++it)
                    part.push_back(*it);
                parts.push_back(static_cast<String&&>(part));
                if (it == end)
                    break;
            }
            return parts;
        }
        StringList split(std::size_t pos, char delim = ' ') const {
            if (this->isEmpty() || pos >= this->size())
                return {};
            StringList parts{};
            for (const_iterator it = const_iterator(this, this->__relativePosition(pos)), end = this->cend(); it != end; ++it) {
                String part{};
                for (; it != end && *it != delim; ++it)
                    part.push_back(*it);
                parts.push_back(static_cast<String&&>(part));
                if (it == end)
                    break;
            }
            return parts;
        }
        static StringList split(const char* str, char delim = ' ') {
            return String(str).split(delim);
        }
        static StringList split(const char* str, size_t pos, char delim) {
            return String(str).split(pos, delim);
        }
        static StringList split(const CompactString& str, char delim = ' ') {
            return String(str).split(delim);
        }
        static StringList split(const CompactString& str, size_t pos, char delim) {
            return String(str).split(pos, delim);
        }
    
    private:
        value_type* arr{};
        std::size_t front{};
        std::size_t cur{};
        std::size_t arr_size{};

        void streamInsert(std::ostream& out) const {
            if (this->cur) {
                std::size_t i{this->front}, count{};
                for (; count < this->cur; ++count, i = (i + 1) % this->arr_size)
                    out << this->arr[i];
            }
            else if (this->arr == nullptr)
                out << "null";
        }
        constexpr bool __isFull() const {
            return (this->cur == this->arr_size - 1);
        }
        constexpr bool __isVacant() const {
            return (this->cur == this->arr_size / 3);
        }
        bool __isOutOfBounds(std::size_t index) const {
            return ((this->cur == 0) || (index > this->cur - 1));
        }
        bool __checkString(check_fun p) const {
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                if (!p(*it))
                    return false;
            return true;
        }
        String& __modifyString(int (*mod_fun)(int)) {
            iterator it = this->begin();
            for (; it != this->end(); ++it)
                *it = mod_fun(*it);
            return *this;
        }
        String __getModifiedString(int (*mod_fun)(int)) const {
            String tmp{};
            const_iterator it = this->cbegin();
            for (; it != this->cend(); ++it)
                tmp.push_back(mod_fun(*it));
            return tmp;
        }
        const_iterator __skipwf() const {
            const_iterator it = this->cbegin();
            for (; it != this->cend() && __isWhiteSpace(*it); ++it);
            return it;
        }
        const_reverse_iterator __skipwr() const {
            const_reverse_iterator it = this->crbegin();
            for (; it != this->crend() && __isWhiteSpace(*it); ++it);
            return it;
        }
        iterator __skipwf() {
            iterator it = this->begin();
            for (; it != this->end() && __isWhiteSpace(*it); ++it);
            return it;
        }
        reverse_iterator __skipwr() {
            reverse_iterator it = this->rbegin();
            for (; it != this->rend() && __isWhiteSpace(*it); ++it);
            return it;
        }
        /**
         * Set the value of all member variables one by one in sequence.
         * @param arr
         * @param front
         * @param cur
         * @param arr_size
         */
        void __set(pointer _arr, std::size_t _front, std::size_t _cur, std::size_t _arr_size) noexcept {
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
        void __initialize(std::size_t _size) {
            this->__set(new value_type[_size], 0, 0, _size);
        }
        /**
         * Resets the front and cur attributes so that the string can be
         * treated as an empty string. This method is for use before reading
         * characters from the input stream like in the getline() method or
         * using the stream extraction operator ">>".
         * @param alloc If true then the current array is deleted and a new
         * array with the default size is freshly allocated. Default value is
         * false.
         */
        void __initializeForReading(bool alloc = false) {
            if (alloc) {
                delete[] this->arr;
                this->__initialize(DEFAULT_SIZE + 1);
            }
            else {
                this->front = 0;
                this->cur = 0;
            }
        }
        /**
         * Grows or shrinks the containing array according to the value of the
         * flag parameter.
         * @param flag Must be one out of the two static constants defined in
         * the class, deque::EXPAND or deque::SHRINK.
         */
        void __alter(std::size_t flag) {
            pointer newArray{};
            std::size_t i{}, newSize{};
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
            this->__set(newArray, {}, this->cur, newSize);
        }
        void __invalidate() {
            this->__set({}, {}, {}, {});
        }
        /**
         * Swap elements at indices i and j in the containing array.
         */
        void __swap(std::size_t i, std::size_t j) {
            value_type tmp{this->arr[i]};
            this->arr[i] = this->arr[j];
            this->arr[j] = tmp;
        }
        /**
         * Returns the actual index at which the element at index i in the
         * list will be located in the containing array.
         * @param i The index of the list item whose actual position in the
         * containing array is required.
         */
        std::size_t __relativePosition(std::size_t i) const {
            return (this->front + i) % this->arr_size;
        }
        static bool __isWhiteSpace(char ch) {
            switch (ch){
                case ' ':
                case '\t':
                case '\f':
                case '\n':
                case '\r':
                case '\v':
                    return true;
                default:
                    return false;
            }
        }
};

template<std::integral T>
String toString(T x) {
    if (x == 0)
        return {"0"};
    String s{};
    T num = (x < 0) ? -x : x;
    for (; num; num /= 10)
        s.push_front(static_cast<char>('0' + (num % 10)));
    if (x < 0)
        s.push_front('-');
    return s;
}
String input(const char* prompt) {
    String res{};
    std::cout << prompt;
    std::cin >> res;
    return res;
}
inline std::ostream& operator<<(std::ostream& out, const String& d) {
    d.streamInsert(out);
    return out;
}
String operator ""_s(const char* str, unsigned long long n) {
    return String{str};
}

#endif  // __STRING_H
