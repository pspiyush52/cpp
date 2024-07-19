#ifndef __ITERATE_H
#define __ITERATE_H

template<typename Container>
class copy{
    public:
        copy(const Container& c) : __c(c){}
        template<typename cont>
        cont& operator>>(cont& c){
            auto iter = std::cbegin(this->__c);
            auto end = std::cend(this->__c);
            auto citer = std::begin(c);
            auto cend = std::end(c);
            for (; (iter != end) && (citer != cend); ++iter, ++citer)
                *citer = *iter;
            return c;
        }

    private:
        const Container& __c;
};

#endif  // __ITERATE_H