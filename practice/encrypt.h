#ifndef __ENCRYPT_H
#define __ENCRYPT_H

class Encrypt{
    public:
        void operator()(char& ch){
            ch += 3;
        }
};

#endif  // __ENCRYPT_H