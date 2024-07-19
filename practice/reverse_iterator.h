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

#endif  // __REVERSE_ITERATOR_H