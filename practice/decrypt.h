#ifndef __DECRYPT_H
#define __DECRYPT_H

class Decrypt{
    public:
        void operator()(char& ch){
            ch -= 3;
        }
};

#endif  // __DECRYPT_H