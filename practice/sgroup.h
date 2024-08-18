#ifndef __SGROUP_H
#define __SGROUP_H

/**
 * The only purpose of this class is to group objects of type T which are
 * created on the stack into one list. It is a loose association of objects
 * and does not provide creation or destruction facilities. Objects of this
 * class can be used to pass multiple objects as parameters to a function.
 */
template<typename T>
class SGroup {
    public:
        typedef               T**                 iterator;
        SGroup() = default;
        SGroup(std::initializer_list<T*> args) {
            for (auto arg : args)
                this->append(arg);
        }
        SGroup& append(T* ptr) {
            if (this->isFull())
                this->expand();
            this->arr[(this->cur)++] = ptr;
            return *this;
        }
        constexpr int len() const {
            return this->cur;
        }
        iterator begin() {
            return this->arr;
        }
        iterator end() {
            return this->arr + this->cur;
        }
        ~SGroup() {
            if (this->arr) {
                delete[] this->arr;
                this->arr = {};
            }
        }

    private:
        T** arr{new T*[8]};
        int cur{};
        int size{8};
        bool isFull() const {
            return (this->cur == this->size);
        }
        void expand() {
            T** newArray = new T*[2 * this->size];
            memcpy(newArray, this->arr, this->size * sizeof(T*));
            delete[] this->arr;
            this->arr = newArray;
            this->size *= 2;
        }
};

#endif  // __SGROUP_H
