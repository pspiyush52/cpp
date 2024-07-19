#ifndef __A_H
#define __A_H

class B;

class A{
    public:
        A(int num);
        A(const A& obj);
        A(const B& obj);
        A& operator=(const B& obj);
        operator B();
        int get() const;
    
    private:
        int data;
};

#endif  // __A_H