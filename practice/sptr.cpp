#include "string.h"

template<typename obj_type>
struct sptr{
    sptr(obj_type* obj){
        this->__ptr = obj;
    }
    obj_type& operator*(){
        return (*(this->__ptr));
    }
    template<typename T>
    friend sptr<obj_type> make_sptr(T args...){
        return obj_type{args};
    }
    ~sptr(){
        delete this->__ptr;
        this->__ptr = nullptr;
    }

    private:
        obj_type* __ptr;
};
template<typename T, typename... Args>
sptr<T> make_sptr(Args&&... args){
    return (new T(std::forward<Args>(args)...));
}

int main(void)
{
    sptr<string> name = make_sptr<string>("Name", 3);
    std::cout << *name ;
    return 0;
}