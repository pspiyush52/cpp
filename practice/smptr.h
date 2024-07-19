#ifndef __SMPTR_H
#define __SMPTR_H

template<typename T>
class uptr{
    public:
        uptr(T* ptr) : __ptr(ptr){}
        uptr(const uptr& u) = delete;
        uptr(uptr&& u){
            this->__ptr= u.__ptr;
            u.__ptr = {};
        }
        uptr& operator=(const uptr& u) = delete;
        uptr& operator=(uptr&& u){
            delete this->__ptr;
            this->__ptr = u.__ptr;
            u.__ptr = {};
        }
        T& operator*(){
            return *(this->__ptr);
        }
        T* operator->(){
            return this->__ptr;
        }
        ~uptr(){
            delete this->__ptr;
            this->__ptr = {};
        }
    private:
        T* __ptr{};
};

template<typename T, typename... Arguments>
uptr<T> make_unique(Arguments&&... args){
    return {new T(std::forward<Arguments>(args)...)};
}

#endif  // __SMPTR_H
