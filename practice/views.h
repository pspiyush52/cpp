#ifndef __VIEWS_H
#define __VIEWS_H

#include <iostream>

template<typename T>
struct __views_unchanged{
	bool operator()(const T& x){ return true; }
};

template<typename Container, typename Predicate>
class Views;

template<typename Container, typename Predicate>
class __container_views_iterator{
    public:
        __container_views_iterator(const typename Container::iterator& iter, const typename Container::iterator& end, Predicate& pred):
            __iter(iter), __end(end), __pred(pred){
                while ((__iter != __end) && !__pred(*__iter))
                    ++__iter;
            }
        __container_views_iterator(const typename Container::iterator& iter, Predicate& pred) : __iter(iter), __end(iter), __pred(pred){}
        Container::value_type& operator*(){
            return *__iter;
        }
        __container_views_iterator& operator++(){
            ++__iter;
            while ((__iter != __end) && !__pred(*__iter))
                ++__iter;
            return *this;
        }
        __container_views_iterator operator++(int){
            __container_views_iterator tmp(*this);
            ++__iter;
            while ((__iter != __end) && !__pred(*__iter))
                ++__iter;
            return tmp;
        }
        bool operator==(__container_views_iterator& rhs){
            return (this->__iter == rhs.__iter);
        }
        bool operator==(__container_views_iterator&& rhs){
            return (this->__iter == rhs.__iter);
        }
    
    private:
        typename Container::iterator __iter;
        typename Container::iterator __end;
        Predicate& __pred;
};

template<typename Container, typename Predicate = __views_unchanged<typename Container::value_type>>
class Views{
    friend class __container_views_iterator<Container, Predicate>;
	public:
        typedef __container_views_iterator<Container, Predicate> iterator;
        typedef typename Container::value_type value_type;
        Views(Container& C) : __container_ref(C), __pred{}{}
        Views(Container&& C) : Views(C){}
        Views(Container& C, Predicate& pred) : __container_ref(C), __pred(std::move(pred)){}
        Views(Container& C, Predicate&& pred) : __container_ref(C), __pred(std::move(pred)){}
        Views(Container&& C, Predicate& pred) : __container_ref(C), __pred(std::move(pred)){}
        Views(Container&& C, Predicate&& pred) : __container_ref(C), __pred(std::move(pred)){}
        iterator begin(){
            return iterator(std::begin(__container_ref), std::end(__container_ref), __pred);
        }
        iterator end(){
            return iterator(std::end(__container_ref), __pred);
        }

        template<typename __container, typename __predicate>
        friend std::ostream& operator<<(std::ostream& output, Views<__container, __predicate>& C);
        template<typename __container, typename __predicate>
        friend std::ostream& operator<<(std::ostream& output, Views<__container, __predicate>&& C);

        template<typename __container, typename __predicate>
        friend Views<__container, __predicate> operator|(__container& C, __predicate& pred);

        template<typename __container, typename __predicate>
        friend Views<__container, __predicate> operator|(__container&& C, __predicate& pred);

        template<typename __container, typename __predicate>
        friend Views<__container, __predicate> operator|(__container& C, __predicate&& pred);

        template<typename __container, typename __predicate>
        friend Views<__container, __predicate> operator|(__container&& C, __predicate&& pred);
        
        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend Views<Views<__container1, __predicate1>, __predicate2>
        operator|(Views<__container1, __predicate1>&& lhs, Views<__container2, __predicate2>&& rhs);
        
        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend Views<Views<__container1, __predicate1>, __predicate2>
        operator|(Views<__container1, __predicate1>& lhs, Views<__container2, __predicate2>& rhs);

        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend Views<Views<__container1, __predicate1>, __predicate2>
        operator|(Views<__container1, __predicate1>& lhs, Views<__container2, __predicate2>&& rhs);

        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend Views<Views<__container1, __predicate1>, __predicate2>
        operator|(Views<__container1, __predicate1>&& lhs, Views<__container2, __predicate2>& rhs);

        template<typename __container, typename __predicate, typename __predicate2>
        friend Views<Views<__container, __predicate>, __predicate2>
        operator|(Views<__container, __predicate>&& lhs, __predicate2&& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend Views<Views<__container, __predicate>, __predicate2>
        operator|(Views<__container, __predicate>& lhs, __predicate2& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend Views<Views<__container, __predicate>, __predicate2>
        operator|(Views<__container, __predicate>&& lhs, __predicate2& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend Views<Views<__container, __predicate>, __predicate2>
        operator|(Views<__container, __predicate>& lhs, __predicate2&& pred);

        template<typename __container1, typename __container2, typename __predicate>
        friend __container1& operator>>(Views<__container2, __predicate>& view, __container1& container);

        template<typename __container1, typename __container2, typename __predicate>
        friend __container1& operator>>(Views<__container2, __predicate>&& view, __container1& container);

	private:
        Container& __container_ref;
        Predicate&& __pred;
};

template<typename __container, typename __predicate>
inline std::ostream& operator<<(std::ostream& output, Views<__container, __predicate>& C){
    if (C.begin() == C.end())
        return output;
    
    using __cv = typename Views<__container, __predicate>::iterator;

    __cv iter = C.begin();
    __cv __begin = C.begin(), leading = ++__begin;
    output << '[';
    for (; leading != C.end(); ++iter, ++leading)
        std::cout << *iter << ", ";
    output << *iter << ']';
    return output;
}

template<typename __container, typename __predicate>
inline std::ostream& operator<<(std::ostream& output, Views<__container, __predicate>&& C){
    return operator<<(output, C);
}

template<typename __container, typename __predicate>
Views<__container, __predicate> operator|(__container& C, __predicate& pred){
    return Views(C, pred);
}

template<typename __container, typename __predicate>
Views<__container, __predicate> operator|(__container&& C, __predicate& pred){
    return Views(C, pred);
}

template<typename __container, typename __predicate>
Views<__container, __predicate> operator|(__container& C, __predicate&& pred){
    return Views(C, pred);
}

template<typename __container, typename __predicate>
Views<__container, __predicate> operator|(__container&& C, __predicate&& pred){
    return Views(C, pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline Views<Views<__container1, __predicate1>, __predicate2>
operator|(Views<__container1, __predicate1>&& lhs, Views<__container2, __predicate2>&& rhs){
    return Views(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline Views<Views<__container1, __predicate1>, __predicate2>
operator|(Views<__container1, __predicate1>& lhs, Views<__container2, __predicate2>& rhs){
    return Views(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline Views<Views<__container1, __predicate1>, __predicate2>
operator|(Views<__container1, __predicate1>& lhs, Views<__container2, __predicate2>&& rhs){
    return Views(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline Views<Views<__container1, __predicate1>, __predicate2>
operator|(Views<__container1, __predicate1>&& lhs, Views<__container2, __predicate2>& rhs){
    return Views(lhs, rhs.__pred);
}

template<typename __container, typename __predicate, typename __predicate2>
Views<Views<__container, __predicate>, __predicate2> operator|(Views<__container, __predicate>&& lhs, __predicate2&& pred){
    return Views(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
Views<Views<__container, __predicate>, __predicate2> operator|(Views<__container, __predicate>& lhs, __predicate2& pred){
    return Views(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
Views<Views<__container, __predicate>, __predicate2> operator|(Views<__container, __predicate>&& lhs, __predicate2& pred){
    return Views(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
Views<Views<__container, __predicate>, __predicate2> operator|(Views<__container, __predicate>& lhs, __predicate2&& pred){
    return Views(lhs, pred);
}

template<typename __container1, typename __container2, typename __predicate>
__container1& operator>>(Views<__container2, __predicate>& views, __container1& container){
    using views_iterator = Views<__container2, __predicate>::iterator;

    views_iterator viter = views.begin();
    auto citer = container.begin();
    for (; citer != container.end(); ++citer, ++viter){
        if (viter == views.end())
            break;
        *citer = *viter;
    }
    return container;
}

template<typename __container1, typename __container2, typename __predicate>
__container1& operator>>(Views<__container2, __predicate>&& views, __container1& container){
    using views_iterator = Views<__container2, __predicate>::iterator;

    views_iterator viter = views.begin();
    auto citer = container.begin();
    for (; citer != container.end(); ++citer, ++viter){
        if (viter == views.end())
            break;
        *citer = *viter;
    }
    return container;
}

#endif  // __VIEWS_H