#ifndef __VIEW_H
#define __VIEW_H

#include <iostream>

struct __unchanged{
    template<typename T>
	bool operator()(const T& x) const { return true; }
};

template<typename Container, typename Predicate>
class View;

template<typename Container, typename Predicate>
class __container_view_iterator{
    public:
        __container_view_iterator(const typename Container::iterator& iter) : __iter(iter), __end(iter){}
        __container_view_iterator(const typename Container::iterator& iter, const typename Container::iterator& end) : __iter(iter), __end(end){
            while ((__iter != __end) && !View<Container, Predicate>::__pred(*__iter))
                ++__iter;
        }
        typename Container::value_type& operator*(){
            return *__iter;
        }
        __container_view_iterator& operator++(){
            ++__iter;
            while ((__iter != __end) && !View<Container, Predicate>::__pred(*__iter))
                ++__iter;
            return *this;
        }
        __container_view_iterator operator++(int){
            __container_view_iterator tmp(*this);
            ++__iter;
            while ((__iter != __end) && !View<Container, Predicate>::__pred(*__iter))
                ++__iter;
            return tmp;
        }
        bool operator==(__container_view_iterator& rhs){
            return (this->__iter == rhs.__iter);
        }
        bool operator==(__container_view_iterator&& rhs){
            return (this->__iter == rhs.__iter);
        }
    
    private:
        typename Container::iterator __iter;
        typename Container::iterator __end;
};

template<typename Container, typename Predicate = __unchanged>
class View{
    friend class __container_view_iterator<Container, Predicate>;
	public:
        typedef __container_view_iterator<Container, Predicate> iterator;
        typedef typename Container::value_type value_type;
        View(Container& C) : __container_ref(C){}
        View(Container&& C) : View(C){}
        View(Container& C, Predicate& pred) : View(C){}
        View(Container& C, Predicate&& pred) : View(C){}
        View(Container&& C, Predicate& pred) : View(C){}
        View(Container&& C, Predicate&& pred) : View(C){}
        iterator begin(){
            return iterator(std::begin(__container_ref), std::end(__container_ref));
        }
        iterator end(){
            return iterator(std::end(__container_ref));
        }

        template<typename __container, typename __predicate>
        friend std::ostream& operator<<(std::ostream& output, View<__container, __predicate>& C);

        template<typename __container, typename __predicate>
        friend std::ostream& operator<<(std::ostream& output, View<__container, __predicate>&& C);

        template<typename __container, typename __predicate>
        friend View<__container, __predicate> operator|(__container& C, __predicate& pred);

        template<typename __container, typename __predicate>
        friend View<__container, __predicate> operator|(__container&& C, __predicate& pred);

        template<typename __container, typename __predicate>
        friend View<__container, __predicate> operator|(__container& C, __predicate&& pred);

        template<typename __container, typename __predicate>
        friend View<__container, __predicate> operator|(__container&& C, __predicate&& pred);

        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend View<View<__container1, __predicate1>, __predicate2>
        operator|(View<__container1, __predicate1>&& lhs, View<__container2, __predicate2>&& rhs);
        
        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend View<View<__container1, __predicate1>, __predicate2>
        operator|(View<__container1, __predicate1>& lhs, View<__container2, __predicate2>& rhs);

        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend View<View<__container1, __predicate1>, __predicate2>
        operator|(View<__container1, __predicate1>& lhs, View<__container2, __predicate2>&& rhs);

        template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
        friend View<View<__container1, __predicate1>, __predicate2>
        operator|(View<__container1, __predicate1>&& lhs, View<__container2, __predicate2>& rhs);

        template<typename __container, typename __predicate, typename __predicate2>
        friend View<View<__container, __predicate>, __predicate2>
        operator|(View<__container, __predicate>&& lhs, __predicate2&& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend View<View<__container, __predicate>, __predicate2>
        operator|(View<__container, __predicate>& lhs, __predicate2& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend View<View<__container, __predicate>, __predicate2>
        operator|(View<__container, __predicate>&& lhs, __predicate2& pred);

        template<typename __container, typename __predicate, typename __predicate2>
        friend View<View<__container, __predicate>, __predicate2>
        operator|(View<__container, __predicate>& lhs, __predicate2&& pred);

        template<typename __container1, typename __container2, typename __predicate>
        friend __container1& operator>>(View<__container2, __predicate>& view, __container1& container);

        template<typename __container1, typename __container2, typename __predicate>
        friend __container1& operator>>(View<__container2, __predicate>&& view, __container1& container);

	private:
        Container& __container_ref;
        static inline Predicate __pred{};
};

template<typename __container, typename __predicate>
inline std::ostream& operator<<(std::ostream& output, View<__container, __predicate>& C){
    if (C.begin() == C.end())
        return output;
    
    using __cv = typename View<__container, __predicate>::iterator;

    __cv iter = C.begin();
    __cv __begin = C.begin(), leading = ++__begin;
    output << '[';
    for (; leading != C.end(); ++iter, ++leading)
        std::cout << *iter << ", ";
    output << *iter << ']';
    return output;
}

template<typename __container, typename __predicate>
inline std::ostream& operator<<(std::ostream& output, View<__container, __predicate>&& C){
    return operator<<(output, C);
}

template<typename __container, typename __predicate>
View<__container, __predicate> operator|(__container& C, __predicate& pred){
    return View(C, pred);
}

template<typename __container, typename __predicate>
View<__container, __predicate> operator|(__container&& C, __predicate& pred){
    return View(C, pred);
}

template<typename __container, typename __predicate>
View<__container, __predicate> operator|(__container& C, __predicate&& pred){
    return View(C, pred);
}

template<typename __container, typename __predicate>
View<__container, __predicate> operator|(__container&& C, __predicate&& pred){
    return View(C, pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline View<View<__container1, __predicate1>, __predicate2>
operator|(View<__container1, __predicate1>&& lhs, View<__container2, __predicate2>&& rhs){
    return View(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline View<View<__container1, __predicate1>, __predicate2>
operator|(View<__container1, __predicate1>& lhs, View<__container2, __predicate2>& rhs){
    return View(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline View<View<__container1, __predicate1>, __predicate2>
operator|(View<__container1, __predicate1>& lhs, View<__container2, __predicate2>&& rhs){
    return View(lhs, rhs.__pred);
}

template<typename __container1, typename __predicate1, typename __container2, typename __predicate2>
inline View<View<__container1, __predicate1>, __predicate2>
operator|(View<__container1, __predicate1>&& lhs, View<__container2, __predicate2>& rhs){
    return View(lhs, rhs.__pred);
}

template<typename __container, typename __predicate, typename __predicate2>
View<View<__container, __predicate>, __predicate2> operator|(View<__container, __predicate>&& lhs, __predicate2&& pred){
    return View(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
View<View<__container, __predicate>, __predicate2> operator|(View<__container, __predicate>& lhs, __predicate2& pred){
    return View(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
View<View<__container, __predicate>, __predicate2> operator|(View<__container, __predicate>&& lhs, __predicate2& pred){
    return View(lhs, pred);
}

template<typename __container, typename __predicate, typename __predicate2>
View<View<__container, __predicate>, __predicate2> operator|(View<__container, __predicate>& lhs, __predicate2&& pred){
    return View(lhs, pred);
}

template<typename __container1, typename __container2, typename __predicate>
__container1& operator>>(View<__container2, __predicate>& view, __container1& container){
    using view_iterator = View<__container2, __predicate>::iterator;

    view_iterator viter = view.begin();
    auto citer = container.begin();
    for (; citer != container.end(); ++citer, ++viter){
        if (viter == view.end())
            break;
        *citer = *viter;
    }
    return container;
}

template<typename __container1, typename __container2, typename __predicate>
__container1& operator>>(View<__container2, __predicate>&& view, __container1& container){
    using view_iterator = View<__container2, __predicate>::iterator;

    view_iterator viter = view.begin();
    auto citer = container.begin();
    for (; citer != container.end(); ++citer, ++viter){
        if (viter == view.end())
            break;
        *citer = *viter;
    }
    return container;
}

#endif  // __VIEW_H