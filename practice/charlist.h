#ifndef __CHARLIST_H
#define __CHARLIST_H

#include <iostream>
#include <initializer_list>

class CharList {
    static inline const int DEFAULT_SIZE{4};
    static inline const int SHRINK{0};
    static inline const int EXPAND{1};
    public:
        class iterator {
            public:
                iterator(CharList* ptr, int i): p{ptr}, pos{i} {}
                char& operator*() {
                    return p->A[pos];
                }
                iterator& operator++() {
                    pos = (pos + 1) % p->arr_size;
                    return *this;
                }
                iterator& operator--() {
                    pos = (pos + p->arr_size - 1) % p->arr_size;
                    return *this;
                }
                bool operator==(iterator& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator==(iterator&& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator!=(iterator& rhs) {
                    return (this->pos != rhs.pos);
                }
                bool operator!=(iterator&& rhs) {
                    return (this->pos != rhs.pos);
                }
                int getPos() {
                    return this->pos;
                }
            
            private:
                CharList* p;
                int pos;
        };
        class const_iterator {
            public:
                const_iterator(const CharList* ptr, int i): p{ptr}, pos{i} {}
                const char& operator*() const {
                    return p->A[pos];
                }
                const_iterator& operator++() {
                    pos = (pos + 1) % p->arr_size;
                    return *this;
                }
                const_iterator& operator--() {
                    pos = (pos + p->arr_size - 1) % p->arr_size;
                    return *this;
                }
                bool operator==(const_iterator& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator==(const_iterator&& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator!=(const_iterator& rhs) {
                    return (this->pos != rhs.pos);
                }
                bool operator!=(const_iterator&& rhs) {
                    return (this->pos != rhs.pos);
                }

            private:
                const CharList* p;
                int pos;
        };
        class reverse_iterator {
            public:
                reverse_iterator(CharList* ptr, int i): p{ptr}, pos{i} {}
                char& operator*() {
                    return p->A[pos];
                }
                reverse_iterator& operator++() {
                    pos = (pos + p->arr_size - 1) % p->arr_size;
                    return *this;
                }
                reverse_iterator& operator--() {
                    pos = (pos + 1) % p->arr_size;
                    return *this;
                }
                bool operator==(reverse_iterator& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator==(reverse_iterator&& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator!=(reverse_iterator& rhs) {
                    return (this->pos != rhs.pos);
                }
                bool operator!=(reverse_iterator&& rhs) {
                    return (this->pos != rhs.pos);
                }
                int getPos() {
                    return this->pos;
                }
            
            private:
                CharList* p;
                int pos;
        };
        class const_reverse_iterator {
            public:
                const_reverse_iterator(const CharList* ptr, int i): p{ptr}, pos{i} {}
                const char& operator*() {
                    return p->A[pos];
                }
                const_reverse_iterator& operator++() {
                    pos = (pos + p->arr_size - 1) % p->arr_size;
                    return *this;
                }
                const_reverse_iterator& operator--() {
                    pos = (pos + 1) % p->arr_size;
                    return *this;
                }
                bool operator==(const_reverse_iterator& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator==(const_reverse_iterator&& rhs) {
                    return (this->pos == rhs.pos);
                }
                bool operator!=(const_reverse_iterator& rhs) {
                    return (this->pos != rhs.pos);
                }
                bool operator!=(const_reverse_iterator&& rhs) {
                    return (this->pos != rhs.pos);
                }
            
            private:
                const CharList* p;
                int pos;
        };

        CharList(int size) {
            size = (size < 0) ? DEFAULT_SIZE : size;
            this->make(size + 1);
        }
        CharList(): A{new char[DEFAULT_SIZE + 1]}, front{0}, n{0}, arr_size{DEFAULT_SIZE + 1}
        {
        }
        CharList(char ch, int count): CharList(count) {
            for (int i{}; i < count; ++i)
                this->append(ch);
        }
        CharList(const char* str): CharList() {
            for(; *str; ++str)
                this->append(*str);
        }
        CharList(const CharList& src) {
            if (this == &src)
                return;
            this->make(src.arr_size);
            const_iterator iter = src.begin();
            for (; iter != src.end(); ++iter)
                this->append(*iter);
        }
        CharList(CharList&& src) {
            this->A = src.A;
            this->front = src.front;
            this->arr_size = src.arr_size;
            this->n = src.n;
            src.invalidate();
        }
        CharList& operator=(const CharList& src) {
            if (this == &src)
                return *this;
            delete[] this->A;
            this->make(src.arr_size);
            for (const_iterator iter = src.begin(); iter != src.end(); ++iter)
                this->append(*iter);
            return *this;
        }
        CharList& operator=(CharList&& src) {
            if (this == &src)
                return *this;
            delete[] this->A;
            this->A = src.A;
            this->front = src.front;
            this->arr_size = src.arr_size;
            this->n = src.n;
            src.invalidate();
            return *this;
        }
        /**
         * Returns true if the list does not contain any characters.
         */
        constexpr bool isEmpty() const {
            return (!this->n);
        }
        /**
         * Returns the number of characters currently in the list.
         */
        constexpr int size() const {
            return this->n;
        }
        /**
         * Returns the maximum number of characters that the list can
         * hold before it has to expand.
         */
        constexpr int capacity() const {
            return (this->arr_size - 1);
        }
        /**
         * Appends a character at the end of the list.
         * @param ch The character that is to be appended at the end of the
         * list.
         * @note The amortized time complexity of this operation is O(n).
         */
        CharList& append(char ch) {
            if (this->isFull())
                this->alter(EXPAND);
            this->A[(this->front + this->n) % this->arr_size] = ch;
            ++(this->n);
            return *this;
        }
        /**
         * Inserts a character at the beginning of the list.
         * @param ch The character that is to be inserted at the beginning
         * of the list.
         * @note The amortized time complexity of this operation is O(n).
         */
        CharList& prepend(char ch) {
            if (this->isFull())
                this->alter(EXPAND);
            this->front = (this->front + this->arr_size - 1) % this->arr_size;
            this->A[this->front] = ch;
            ++(this->n);
            return *this;
        }
        /**
         * Inserts a character at the beginning of the list.
         * @param ch The character that is to be inserted at the beginning
         * of the list.
         * @note The amortized time complexity of this operation is O(n).
         */
        CharList& push_front(char ch) {
            return this->prepend(ch);
        }
        /**
         * Appends a character at the end of the list.
         * @param ch The character that is to be appended at the end of the
         * list.
         * @note The amortized time complexity of this operation is O(n).
         */
        CharList& push_back(char ch) {
            return this->append(ch);
        }
        /**
         * Deletes a character from the front of the list.
         */
        CharList& pop_front() {
            if (this->isVacant())
                this->alter(SHRINK);
            if (this->n) {
                this->front = (this->front + 1) % this->arr_size;
                --(this->n);
            }
            return *this;
        }
        /**
         * Deletes a character from the end of the list.
         */
        CharList& pop_back() {
            if (this->isVacant())
                this->alter(SHRINK);
            if (this->n)
                --(this->n);
            return *this;
        }
        /**
         * Returns a character at the specified index in the list without
         * bounds checking.
         * @param i The index of the element to be fetched.
         */
        char& operator[](int i) {
            return this->A[(this->front + i) % this->arr_size];
        }
        /**
         * Reverses the list.
         */
        CharList& reverse() {
            iterator iter = this->begin();
            reverse_iterator riter = this->rbegin();
            for (int i{}; i < this->n / 2; ++i) {
                swap(iter.getPos(), riter.getPos());
                ++iter;
                ++riter;
            }
            return *this;
        }

        iterator begin() {
            return {this, this->front};
        }
        iterator end() {
            return {this, (this->front + this->n) % this->arr_size};
        }
        const_iterator begin() const {
            return {this, this->front};
        }
        const_iterator end() const {
            return {this, (this->front + this->n) % this->arr_size};
        }
        const_iterator cbegin() const {
            return {this, this->front};
        }
        const_iterator cend() const {
            return {this, (this->front + this->n) % this->arr_size};
        }
        reverse_iterator rbegin() {
            return {this, (this->front + this->n - 1) % this->arr_size};
        }
        reverse_iterator rend() {
            int pos = (this->front) ? (this->front - 1) : this->arr_size - 1;
            return {this, pos};
        }
        const_reverse_iterator rbegin() const {
            return {this, (this->front + this->n - 1) % this->arr_size};
        }
        const_reverse_iterator rend() const {
            int pos = (this->front) ? (this->front - 1) : this->arr_size - 1;
            return {this, pos};
        }

        ~CharList() {
            if (this->A) {
                delete[] this->A;
                this->A = {};
            }
        }
        friend std::ostream& operator<<(std::ostream& out, const CharList& L);
        friend std::istream& operator>>(std::istream& in, CharList& L);
    
    protected:
        int numAt(int i) const {
            if (i >= this->n)
                return 0;
            return (this->A[(this->front + i) % this->arr_size] - 48);
        }
        void streamInsert(std::ostream& out) const {
            if (!this->isEmpty()) {
                for (const_iterator it = this->begin(); it != this->end(); ++it)
                    out << *it;
            }
        }
        void invalidate() {
            this->A = {};
            this->front = {};
            this->n = {};
            this->arr_size = {};
        }
    
    private:
        char* A{};
        int front{};
        int n{};
        int arr_size{};

        bool isFull() {
            return (this->n == this->arr_size - 1);
        }
        bool isVacant() {
            return (this->n == this->arr_size / 3);
        }
        void make(int size = DEFAULT_SIZE) {
            this->A = new char[size];
            this->arr_size = size;
        }
        void alter(int flag) {
            char* newArray{};
            int i{}, newSize{};
            switch (flag) {
                case EXPAND:
                    newSize = this->arr_size * 2;
                break;
                case SHRINK:
                    newSize = this->arr_size / 2;
                break;
            }
            newArray = new char[newSize];
            iterator iter = this->begin();
            for (; iter != this->end(); ++i, ++iter)
                newArray[i] = *iter;
            delete[] this->A;
            this->A = newArray;
            this->front = {};
            this->arr_size = newSize;
        }
        void swap(int i, int j) {
            char tmp{this->A[i]};
            this->A[i] = this->A[j];
            this->A[j] = tmp;
        }
};
std::ostream& operator<<(std::ostream& out, const CharList& L) {
    L.streamInsert(out);
    return out;
}
/**
 * Reads characters into the list up to the end line character('\n').
 * All characters before encountering '\n' will be read and inserted
 * into the list.
 */
std::istream& operator>>(std::istream& in, CharList& L) {
    L.front = {};
    L.n = {};
    int ch = in.get();
    while (ch != '\n') {
        L.append(ch);
        ch = in.get();
    }
    return in;
}

#endif  // __CHARLIST_H