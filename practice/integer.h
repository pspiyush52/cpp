#ifndef __INTEGER_H
#define __INTEGER_H

#include "charlist.h"

int max(int x, int y) { return (x > y) ? x : y; }
int min(int x, int y) { return (x < y) ? x : y; }

class Integer : private CharList {
    public:
        Integer() = default;
        Integer(const char* num): CharList{} {
            const char* ptr = num;
            for (; *ptr; ++ptr);
            for (--ptr; ptr >= num; --ptr)
                this->append(*ptr);
        }
        Integer(const CharList& cl): CharList(std::move(cl)) {}
        int at(int i) const {
            return this->numAt(i);
        }
        Integer operator<<(int i) {
            if (i <= 0)
                return *this;
            Integer Z{*this};
            for (; i; --i)
                Z.prepend('0');
            return Z;
        }
        Integer& operator<<=(int i) {
            if (i <= 0)
                return *this;
            for(; i; --i)
                this->prepend('0');
            return *this;
        }
        Integer operator>>(int i) {
            if (i <= 0)
                return *this;
            Integer Z{*this};
            for (; i; --i)
                Z.pop_front();
            return Z;
        }
        Integer& operator>>=(int i) {
            if (i > 0) {
                for (; i; --i)
                    this->pop_front();
            }
            return *this;
        }
        Integer operator+(const Integer& Y) {
            int len = max(this->size(), Y.size());
            int carry = {}, s = {};
            Integer Z;
            for (int i{}; i < len; ++i) {
                s = this->numAt(i) + Y.numAt(i) + carry;
                Z.append((s % 10) + 48);
                carry = s / 10;
            }
            if (carry > 0)
                Z.append(carry + 48);
            return Z;
        }
        Integer& operator+=(const Integer& Y) {
            int len = max(this->size(), Y.size());
            int carry = {}, s = {};
            for (int i{}; i < len; ++i) {
                s = this->numAt(i) + Y.numAt(i) + carry;
                (*this)[i] = (s % 10) + 48;
                carry = s / 10;
            }
            if (carry > 0)
                this->append(carry + 48);
            return *this;
        }
        Integer operator*(const Integer& Y) const {
            Integer Z{};
            for (int i{}; i < this->size(); ++i) {
                Integer t = std::move(Y.digitMul(this->numAt(i)) <<= i);
                Z = Z + t;
            }
            return Z;
        }
        int size() const {
            return CharList::size();
        }
        friend std::ostream& operator<<(std::ostream& out, const Integer& i);
        friend std::istream& operator>>(std::istream& in, Integer& i);
    
    private:
        Integer digitMul(int n) const {
            Integer R;
            int carry{}, r{}, i{};
            for (; i < this->size(); ++i) {
                r = this->numAt(i) * n + carry;
                R.append((r % 10) + 48);
                carry = r / 10;
            }
            if (carry > 0)
                R.append(carry + 48);
            return R;
        }
        void streamInsert(std::ostream& out) const {
            if (this->isEmpty())
                out << '0';
            else {
                for (const_reverse_iterator it = this->rbegin(); it != this->rend(); ++it)
                    out << *it;
            }
        }
};
std::ostream& operator<<(std::ostream& out, const Integer& i) {
    i.streamInsert(out);
    return out;
}
std::istream& operator>>(std::istream& in, Integer& i) {
    int ch = in.get();
    while (ch != '\n') {
        i.prepend(ch);
        ch = in.get();
    }
    return in;
}

#endif  // __INTEGER_H
