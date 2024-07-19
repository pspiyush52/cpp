#ifndef __CPAIR_H
#define __CPAIR_H

inline static int col(int x, int n){
    if (x == 1) return n;
    return (x & 1) ? col(3*x + 1, n + 1) : col(x/2, n + 1);
}
inline static int collatz(int x){
    return col(x, 0);
}

struct cpair{
    cpair(int X): x(X), c_x(collatz(X)){}
    // bool operator<(const cpair& rhs) const{
        // return (this->c_x < rhs.c_x);
    // }
    friend std::ostream& operator<<(std::ostream& output, const cpair& cp){
        output << "(x=" << cp.x << ", c(x)=" << cp.c_x << ')';
        return output;
    }
    int x;
    int c_x;
};

#endif  // __CPAIR_H