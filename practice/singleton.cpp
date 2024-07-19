#include <iostream>

class Printer {
    public:
        static Printer getPrinter() {
            return instance;
        }
        void print(const char* str) {
            std::cout << str << '\n';
        }
    private:
        Printer() {}
        static Printer instance;
};

int main(void) {
    Printer p = Printer::getPrinter();
    p.print("Using printer");
    return 0;
}
