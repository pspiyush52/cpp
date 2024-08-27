#include <iostream>
#include <string>

template<typename T>
class StudentList {
    static const int DEFAULT_SIZE{13};
    static const int SHRINK{};
    static const int EXPAND{1};
    typedef                             T                  value_type;
    typedef                   std::string                  string;
    typedef            unsigned long long                  hash_value_type;
    public:
        StudentList(): arr{new value_type*[DEFAULT_SIZE]}, n{}, arr_size{DEFAULT_SIZE} {
            for (int i{}; i < this->arr_size; ++i)
                this->arr[i] = {};
        }
        StudentList& insert(const char* studentName, const value_type& value) {
            hash_value_type i{}, loc{this->hashIndex(studentName, i)};
            for (; this->arr[loc] != nullptr; loc = this->hashIndex(studentName, ++i));
            this->arr[loc] = new value_type{value};
            return *this;
        }
        const value_type& find(const char* studentName) const {
            hash_value_type loc = this->retrieveIndex(studentName);
            return *(this->arr[loc]);
        }
        value_type& operator[](const char* str) {
            hash_value_type loc = this->retrieveIndex(str);
            return *(this->arr[loc]);
        }
        ~StudentList() {
            if (this->arr) {
                for (int i{}; i < this->arr_size; ++i) {
                    if (this->arr[i])
                        delete this->arr[i];
                }
                delete[] this->arr;
                this->arr = {};
            }
        }
        void __print_array() {
            int i{};
            std::cout << '[';
            for (; i < this->arr_size - 1; ++i) {
                if (this->arr[i])
                    std::cout << (*(this->arr[i]));
                else
                    std::cout << "null";
                std::cout << ", ";
            }
            if (this->arr[i])
                std::cout << (*(this->arr[i]));
            else
                std::cout << "null";
            std::cout << ']' << std::endl;
        }
    
    // private:
        value_type** arr;
        int n;
        int arr_size;

        static hash_value_type hash(const char* str, hash_value_type i) {
            hash_value_type h{i + 1};
            for (; *str; ++str) {
                h = (h == 0) ? 1 : h;
                h += (h * (*str));
            }
            return h;
        }
        hash_value_type hashIndex(const char* str, hash_value_type i) {
            return hash(str, i) % this->arr_size;
        }
        int retrieveIndex(const char* str) {
            hash_value_type i{}, loc{hashIndex(str, i)};
            for (; (this->arr[loc] == nullptr); loc = hashIndex(str, ++i));
            return loc;
        }
        bool isFull() {
            return (this->n == this->arr_size);
        }
        bool isVacant() {
            return (this->n <= this->arr_size / 3);
        }
        void alter(int flag) {
            value_type** newArray{};
            int newSize{};
            switch (flag) {
                case SHRINK:
                    newSize = this->arr_size / 2;
                    break;
                case EXPAND:
                    newSize = this->arr_size * 2;
                    break;
            }
            newArray = new string*[newSize];
            memcpy(newArray, this->arr, this->n);
            delete[] this->arr;
            this->arr = newArray;
            this->arr_size = newSize;
        }
};

int main(void)
{
    StudentList<int> l;
    const char* names[] = {
        "Birbal", "Tansen", "Todarmal", "Man Singh", "Faizi", "Abul Fazl"
    };
    for (int i{}; i < 6; ++i)
        l.insert(names[i], i);
    std::cout << l["Tansen"] << '\n';
    // l.__print_array();
    // l["Man Singh"] = 90;
    std::cout << l["Madhuban"] << '\n';
    // l.__print_array();
    // for (int i{}; i < 10; ++i) {
    //     std::cout << (StudentList<int>::hash("bob", i)) << ", ";
    //     std::cout << (StudentList<int>::hash("bob", i) % 13) << '\n';
    // }
    return 0;
}
