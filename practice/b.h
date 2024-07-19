#ifndef __B_H
#define __B_H

class A;

class B{
    public:
        B(int num);
        B(const B& obj);
        B(const A& obj);
        B& operator=(const A& obj);
        // operator A();
        int get() const;
    
    private:
        int data;
};

#endif  // __B_H