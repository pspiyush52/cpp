#include "print.h"
#include "frand.h"
#include "llist.h"

class Bool {
    public:
        static const Bool True;
        static const Bool False;
        Bool& operator=(const Bool& src){
            this->val = src.val;
            return *this;
        }
        bool operator==(const Bool& rhs) {
            return this->val == rhs.val;
        }
        bool operator!=(const Bool& rhs) {
            return this->val != rhs.val;
        }
    private:
        int val{};
        Bool(int b): val(b) {}
};
const Bool Bool::True{1};
const Bool Bool::False{0};

int main(void)
{
    // LList<int> nums;
    // rng r;
    // repeat(12) nums.append(r.randint(100));
    // print(nums);
    // print(nums.sort());
    
    Bool c{Bool::True};
    c = Bool::False;
    if (c == Bool::True)
        print("True");
    else
        print("False");
    return 0;
}
