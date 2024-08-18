#ifndef __REVERSE_ITERATOR_H
#define __REVERSE_ITERATOR_H

/**
 * @brief Take a random access iterator of type _iterator_type
 * and generates a reverse iterator out of it.
*/
template<typename _iterator_type, typename _value_type>
class __reverse_iterator{
    public:
        __reverse_iterator(const _iterator_type& iter):
            __riter(iter){}
        
        _value_type& operator*(){
            return (*(this->__riter));
        }

        __reverse_iterator& operator++(){
            --(this->__riter);
            return *this;
        }
        
        __reverse_iterator operator++(int){
            --(this->__riter);
            return *this;
        }

        __reverse_iterator operator+(int i){
            return (this->__riter - i);
        }

        __reverse_iterator operator-(int i){
            return (this->__riter + i);
        }

        std::strong_ordering operator<=>(const __reverse_iterator& rhs) const{
            using so = std::strong_ordering;
            if (this->__riter < rhs.__riter)
                return so::greater;
            if (this->__riter > rhs.__riter)
                return so::less;
            else
                return so::equal;
        }
        
        bool operator==(const __reverse_iterator& rhs) const{
            return (this->__riter == rhs.__riter);
        }
        
        bool operator!=(const __reverse_iterator& rhs) const{
            return (!(this->__riter == rhs.__riter));
        }
    
    private:
        _iterator_type __riter;
};

template<typename _iterator_type, typename _value_type>
class __const_reverse_iterator{
    public:
        __const_reverse_iterator(const _iterator_type& iter):
            __riter(iter){}
        
        const _value_type& operator*(){
            return (*(this->__riter));
        }

        __const_reverse_iterator& operator++(){
            --(this->__riter);
            return *this;
        }
        
        __const_reverse_iterator operator++(int){
            --(this->__riter);
            return *this;
        }

        __const_reverse_iterator operator+(int i){
            return (this->__riter - i);
        }

        __const_reverse_iterator operator-(int i){
            return (this->__riter + i);
        }

        std::strong_ordering operator<=>(const __const_reverse_iterator& rhs) const{
            using so = std::strong_ordering;
            if (this->__riter < rhs.__riter)
                return so::greater;
            if (this->__riter > rhs.__riter)
                return so::less;
            else
                return so::equal;
        }

        bool operator==(const __const_reverse_iterator& rhs) const{
            return (this->__riter == rhs.__riter);
        }
        
        bool operator!=(const __const_reverse_iterator& rhs) const{
            return (!(this->__riter == rhs.__riter));
        }

    private:
        _iterator_type __riter;
};

template<typename iter_tp>
class BidirectionalReverseIterator {
    typedef                        BidirectionalReverseIterator                   self;
    typedef                                               self&                   reference;
    public:
        typedef                    typename iter_tp::value_type                   value_type;
        BidirectionalReverseIterator(const iter_tp& iter): it{iter} {}
        typename iter_tp::value_type& operator*() {
            return (*it);
        }
        reference operator++() {
            --it;
            return *this;
        }
        self operator++(int) {
            self tmp{it};
            --it;
            return tmp;
        }
        reference operator--() {
            ++it;
            return *this;
        }
        self operator--(int) {
            self tmp{it};
            --it;
            return tmp;
        }
        bool operator==(const self& rhs) {
            return (it == rhs.it);
        }
        bool operator!=(const self& rhs) {
            return (it != rhs.it);
        }
    
    private:
        iter_tp it;
};

template<typename iter_tp>
class ConstIterator {
    typedef           ConstIterator            self;
    public:
        ConstIterator(const iter_tp& iter): it{iter} {}
        const typename iter_tp::value_type& operator*() {
            return (*it);
        }
        self& operator++() {
            ++it;
            return *this;
        }
        self operator++(int) {
            self tmp{it};
            ++it;
            return tmp;
        }
        self& operator--() {
            --it;
            return *this;
        }
        self operator--(int) {
            self tmp{it};
            --it;
            return tmp;
        }
        bool operator==(const self& rhs) {
            return (this->it == rhs.it);
        }
        bool operator!=(const self& rhs) {
            return (this->it != rhs.it);
        }
    
    private:
        iter_tp it;
};

template<typename T>
class PointerIterator {
    public:
        typedef                        T                          value_type;
        PointerIterator(T* p): ptr{p} {}
        T& operator*() {
            return *(this->ptr);
        }
        PointerIterator& operator++() {
            ++(this->ptr);
            return *this;
        }
        PointerIterator operator++(int) {
            PointerIterator tmp{*this};
            ++(this->ptr);
            return tmp;
        }
        PointerIterator& operator--() {
            --(this->ptr);
            return *this;
        }
        PointerIterator operator--(int) {
            PointerIterator tmp{*this};
            --(this->ptr);
            return tmp;
        }
        bool operator==(const PointerIterator& rhs) {
            return (this->ptr == rhs.ptr);
        }
        bool operator!=(const PointerIterator& rhs) {
            return (this->ptr != rhs.ptr);
        }
    private:
        T* ptr;
};

#endif  // __REVERSE_ITERATOR_H
