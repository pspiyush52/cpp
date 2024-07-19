#ifndef __DEQUE_H
#define __DEQUE_H

#include "str_cont.h"
#include "exceptions.h"

deque::__deque_iterator::__deque_iterator(size_t pos, deque* d) : __pos(pos), __parent(d){}
deque::__deque_iterator& deque::__deque_iterator::operator++(){
    __parent->__incr(this->__pos);
    return *this;
}
deque::__deque_iterator deque::__deque_iterator::operator++(int){
    __parent->__incr(this->__pos);
    return *this;
}
deque::__deque_iterator& deque::__deque_iterator::operator--(){
    if (this->__pos)
        --this->__pos;
    else{
        this->__pos = __parent->__size - 1;
    }
    return *this;
}
deque::__deque_iterator deque::__deque_iterator::operator--(int){
    if (this->__pos)
        --this->__pos;
    else{
        this->__pos = __parent->__size - 1;
    }
    return *this;
}
char& deque::__deque_iterator::operator*(){
    return (__parent->__arr[this->__pos]);
}
deque::__deque_iterator deque::__deque_iterator::operator+(size_t i){
    size_t rel_pos{this->__rel_pos()};
    rel_pos += i;
    if (rel_pos >= __parent->size())
        this->__pos = __parent->__rear;
    else
        this->__pos = (this->__pos + i) % __parent->__size;
    return *this;
}
deque::__deque_iterator deque::__deque_iterator::operator-(size_t i){
    size_t rel_pos{this->__rel_pos()};
    if (i > rel_pos)
        this->__pos = __parent->__rear;
    else
        this->__pos = (this->__pos + __parent->__size - i) % __parent->__size;
    return *this;
}
bool deque::__deque_iterator::operator==(const __deque_iterator& rhs) const{
    return (this->__pos == rhs.__pos);
}
bool deque::__deque_iterator::operator!=(const __deque_iterator& rhs) const{
    return (!(this->__pos == rhs.__pos));
}
size_t deque::__deque_iterator::__get_pos(){
    return this->__pos;
}
size_t deque::__deque_iterator::__rel_pos(){
    if (this->__pos < __parent->__front)
        return (this->__pos - __parent->__front + __parent->__size);
    else
        return (this->__pos - __parent->__front);
}
deque::__const_deque_iterator::__const_deque_iterator(size_t pos, const deque* d) : __pos(pos), __parent(d){}
deque::__const_deque_iterator& deque::__const_deque_iterator::operator++(){
    __parent->__incr(this->__pos);
    return *this;
}
deque::__const_deque_iterator deque::__const_deque_iterator::operator++(int){
    __parent->__incr(this->__pos);
    return *this;
}
deque::__const_deque_iterator& deque::__const_deque_iterator::operator--(){
    if (this->__pos)
        --this->__pos;
    else{
        this->__pos = __parent->__size - 1;
    }
    return *this;
}
deque::__const_deque_iterator deque::__const_deque_iterator::operator--(int){
    if (this->__pos)
        --this->__pos;
    else{
        this->__pos = __parent->__size - 1;
    }
    return *this;
}
const char& deque::__const_deque_iterator::operator*() const{
    return (__parent->__arr[this->__pos]);
}
deque::__const_deque_iterator deque::__const_deque_iterator::operator+(size_t i){
    size_t rel_pos{this->__rel_pos()};
    rel_pos += i;
    if (rel_pos >= __parent->size())
        this->__pos = __parent->__rear;
    else
        this->__pos = (this->__pos + i) % __parent->__size;
    return *this;
}
deque::__const_deque_iterator deque::__const_deque_iterator::operator-(size_t i){
    size_t rel_pos{this->__rel_pos()};
    if (i > rel_pos)
        this->__pos = __parent->__rear;
    else
        this->__pos = (this->__pos + +__parent->__size - i) % __parent->__size;
    return *this;
}
bool deque::__const_deque_iterator::operator==(const __const_deque_iterator& rhs) const{
    return (this->__pos == rhs.__pos);
}
bool deque::__const_deque_iterator::operator!=(const __const_deque_iterator& rhs) const{
    return (!(this->__pos == rhs.__pos));
}
size_t deque::__const_deque_iterator::__get_pos() const{
    return this->__pos;
}
size_t deque::__const_deque_iterator::__rel_pos(){
    if (this->__pos < __parent->__front)
        return (this->__pos - __parent->__front + __parent->__size);
    else
        return (this->__pos - __parent->__front);
}
deque::deque() : __arr(new char[SIZE]), __size(SIZE){}
deque::deque(const deque& src){
    if (src.is_empty()){
        this->__make(SIZE);
    }
    else{
        this->__make(src.__size);
        const_iterator src_iter = src.begin(), src_end = src.end();
        char* iter = this->__arr;
        for (; src_iter != src_end; ++src_iter, ++iter)
            *iter = *src_iter;
        this->__rear = src.size();
    }
}
deque::deque(deque&& src){
    if (src.is_empty()){
        this->__make(SIZE);
        return;
    }
    delete[] this->__arr;
    this->__arr = src.__arr;
    this->__front = src.__front;
    this->__rear = src.__rear;
    this->__size = src.__size;
    src.__invalidate();
}
deque& deque::operator=(const deque& src){
    if (this == &src)
        return *this;
    delete[] this->__arr;
    this->__make(src.__size);
    const_iterator src_iter = src.begin(), src_end = src.end();
    iterator iter = this->begin();
    for (; src_iter != src_end; ++src_iter, ++iter)
        *iter = *src_iter;
    this->__rear = src.size();
    return *this;
}
deque& deque::operator=(deque&& src){
    if (this == &src)
        return *this;
    
    delete[] this->__arr;
    this->__arr = src.__arr;
    this->__front = src.__front;
    this->__rear = src.__rear;
    this->__size = src.__size;
    src.__invalidate();
    return *this;
}
bool deque::is_empty() const{
    return (this->__front == this->__rear);
}
bool deque::is_full() const{
    return (((this->__rear + 1) % this->__size) == this->__front);
}
size_t deque::capacity() const{
    return (this->__size - 1);
}
size_t deque::size() const{
    return ((this->__size + this->__rear - this->__front) % this->__size);
}
deque& deque::push_front(const char& item){
    if (this->is_full())
        this->__expand();
    
    if (this->__front)
        --this->__front;
    else
        this->__front = this->__size - 1;
    this->__arr[this->__front] =  item;
    return *this;
}
deque& deque::push_front(char&& item){
    if (this->is_full())
        this->__expand();
    
    if (this->__front)
        --this->__front;
    else
        this->__front = this->__size - 1;
    this->__arr[this->__front] = item;
    return *this;
}
deque& deque::push_back(const char& item){
    if (this->is_full())
        this->__expand();
    
    this->__arr[this->__rear] =  item;
    this->__incr(this->__rear);
    return *this;
}
deque& deque::push_back(char&& item){
    if (this->is_full())
        this->__expand();
    
    this->__arr[this->__rear] = item;
    this->__incr(this->__rear);
    return *this;
}
deque& deque::pop_front(){
    if (this->is_empty()){
        return *this;
    }
    this->__incr(this->__front);
    return *this;
}
deque& deque::pop_back(){
    if (this->is_empty()){
        return *this;
    }
    if (this->__rear)
        --this->__rear;
    else
        this->__rear = this->__size - 1;
    return *this;
}
deque& deque::pop_frontn(int n){
    for(; !this->is_empty() && (n > 0); --n)
        this->pop_front();
    return *this;
}
deque& deque::pop_backn(int n){
    for (; !is_empty() && (n > 0); --n)
        this->pop_back();
    return *this;
}
deque& deque::shrink_to_fit(){
    this->__shrink();
    return *this;
}
const deque& deque::shrink_to_fit() const{
    this->__shrink();
    return *this;
}
void deque::clear(){
    this->__front = 0;
    this->__rear = 0;
}
deque::iterator deque::begin(){
    return iterator(this->__front, this);
}
deque::iterator deque::end(){
    return iterator(this->__rear, this);
}
deque::const_iterator deque::begin() const{
    return const_iterator(this->__front, this);
}
deque::const_iterator deque::end() const{
    return const_iterator(this->__rear, this);
}
deque::const_iterator deque::cbegin() const{
    return const_iterator(this->__front, this);
}
deque::const_iterator deque::cend() const{
    return const_iterator(this->__rear, this);
}
deque::reverse_iterator deque::rbegin(){
    iterator iter = this->end();
    return reverse_iterator(--iter);
}
deque::reverse_iterator deque::rend(){
    return reverse_iterator(this->end());
}
deque::const_reverse_iterator deque::rbegin() const{
    const_iterator iter = this->end();
    return const_reverse_iterator(--iter);
}
deque::const_reverse_iterator deque::rend() const{
    return const_reverse_iterator(this->end());
}
deque::const_reverse_iterator deque::crbegin() const{
    const_iterator iter = this->end();
    return const_reverse_iterator(--iter);
}
deque::const_reverse_iterator deque::crend() const{
    return const_reverse_iterator(this->end());
}
char& deque::operator[](long long i){
    return (this->__arr[this->__rel_pos(i)]);
}
const char& deque::operator[](long long i) const{
    return (this->__arr[this->__rel_pos(i)]);
}
deque::~deque(){
    delete[] this->__arr;
    this->__invalidate();
}
void deque::__contents(){
    std::cout << *this;
    printf("\nArray size: %llu, Front: %llu, Rear: %llu", this->__size, this->__front, this->__rear);
}
deque::deque(long long size){
    if (size < SIZE)
        this->__make(SIZE);
    else
        this->__make(size);
}

void deque::__make(size_t size){
    this->__arr = new char[size];
    this->__size = size;
    this->__front = this->__rear = 0;
}
void deque::__expand(){
    char* new_arr = new char[this->__size * 2], *ptr = new_arr;
    for (iterator iter = this->begin(), end = this->end(); iter != end; ++iter)
        *ptr++ = *iter;
    delete[] this->__arr;
    this->__arr = new_arr;
    this->__front = 0;
    this->__rear = this->__size - 1;
    this->__size *= 2;
}
void deque::__invalidate(){
    this->__arr = nullptr;
    this->__size = 0;
    this->__front = 0;
    this->__rear = 0;
}
void deque::__incr(size_t& val) const{
    val = ((val + 1) % this->__size);
}
void deque::__set_front(iterator iter){
    this->__front = iter.__get_pos();
}
void deque::__set_front(const_iterator iter) const{
    this->__front = iter.__get_pos();
}
void deque::__set_rear(iterator iter){
    this->__rear = iter.__get_pos();
}
void deque::__set_rear(const_iterator iter) const{
    this->__rear = iter.__get_pos();
}
size_t deque::__rel_pos(size_t i) const{
    if (i < this->__front)
        return (i - this->__front + this->__size);
    else
        return (i - this->__front);
}
void deque::__shrink() const{
    if (this->is_full())
        return;
    size_t new_size = this->size() + 1;
    char* arr = new char[new_size], *ptr = arr;
    for (const_iterator iter = this->cbegin(), end = this->cend(); iter != end; ++iter, ++ptr)
        *ptr = *iter;
    delete[] this->__arr;
    this->__arr = arr;
    this->__front = 0;
    this->__rear = new_size - 1;
    this->__size = new_size;
}
std::ostream& operator<<(std::ostream& output, const deque& d){
    if (d.is_empty()){
        output << "[]";
    }
    else{
        output << '[';
        typename deque::const_iterator iter = d.begin(), before_end = d.end();
        --before_end;
        for (; iter != before_end; ++iter)
            output << *iter << ", ";
        output << *iter << ']';
    }
    return output;
}

#endif  // __DEQUE_H