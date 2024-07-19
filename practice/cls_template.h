#ifndef __CLS_TEMPLATE_H
#define __CLS_TEMPLATE_H

template<typename T, typename U = T>
class pair{
    public:
        pair(const T& first, const U& second):
            __first(first), __second(second){}
        T first(){ return this->__first; }
        U second(){ return this->__second; }
    private:
        T __first;
        U __second;
};

#endif  // __CLS_TEMPLATE_H