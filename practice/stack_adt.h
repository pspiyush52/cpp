#ifndef __STACK_ADT
#define __STACK_ADT

template<typename T>
class StackBase{
    public:
        virtual bool is_empty() = 0;
        virtual bool is_full() = 0;
        virtual StackBase& push(const T& item) = 0;
        virtual StackBase& push(T&& item) = 0;
        virtual StackBase& pop() = 0;
        virtual const T& top() = 0;
    
    private:
        virtual void stream_insert(std::ostream& output) = 0;
    
        template<typename U>
        friend std::ostream& operator<<(std::ostream& output, StackBase<U>& s);
};

template<typename U>
std::ostream& operator<<(std::ostream& output, StackBase<U>& s){
    s.stream_insert(output);
    return output;
}

#endif  // __STACK_ADT