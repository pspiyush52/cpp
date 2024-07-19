#ifndef __SMART_PTR_H
#define __SMART_PTR_H

template<typename T>
class sptr{
    public:
        sptr() = default;
        sptr(const sptr& s_ptr) = delete;
        sptr(sptr&& source_ptr);
        sptr(T obj);
        const T* get() const;
        const T* operator->() const;
        T& operator*();
        ~sptr();
    private:
        T* ptr{nullptr};
};

template<typename T>
sptr<T>::sptr(T obj):
    ptr(new T{obj}){}

template<typename T>
sptr<T>::sptr(sptr<T>&& source_ptr){
    if (ptr)
        delete ptr;
    ptr = source_ptr.ptr;
    source_ptr.ptr = nullptr;
}

template<typename T>
const T* sptr<T>::get() const{
    return ptr;
}

template<typename T>
const T* sptr<T>::operator->() const{
    return ptr;
}

template<typename T>
T& sptr<T>::operator*(){
    return *ptr;
}

template<typename T>
sptr<T>::~sptr(){
    delete ptr;
}

#endif  // __sptr