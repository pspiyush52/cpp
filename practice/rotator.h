#ifndef __ROTATOR_H
#define __ROTATOR_H

/**
 * This class does not create a copy of the container neither
 * does it alter the contents of the container in any way.
 * The array index operator [] of this class maps the index
 * i of the rotated array to the index j of the actual array
 * whose element would have been at index i if the array were
 * actually rotated. In this way it provides an illusion of
 * rotation without doing the actual rotation.
 * 
 * @note Requires the Container class to implement the array
 * index operator[].
 */
template<typename Container>
class Rotator {
    public:
        Rotator(Container& C): con{C}, con_size(std::size(con))
        {
        }
        Rotator(Container& C, int n): con{C}, con_size(std::size(con)) {
            if (n < 0)
                this->rotateBackwards(-n);
            else
                this->rotateForwards(n);
        }
        Rotator& rotateForwards(int n) {
            this->rotation = this->con_size - (n % this->con_size);
            return *this;
        }
        Rotator& rotateBackwards(int n) {
            this->rotation = n;
            return *this;
        }
        auto& operator[](int i) {
            return this->con[(i + this->rotation) % this->con_size];
        }
        const auto& operator[](int i) const {
            return this->con[(i + this->rotation) % this->con_size];
        }
        int size() const {
            return this->con_size;
        }
        int get(int i, int n) const {
            if (n > 0)
                return (i + n) % this->con_size;
            else
                return (i + this->con_size + (n % this->con_size)) % this->con_size;
        }
        template<typename U>
        friend std::ostream& operator<<(std::ostream& out, const Rotator<U>& r);
    private:
        Container& con;
        int con_size{};
        int rotation{};
};

template<typename U>
std::ostream& operator<<(std::ostream& out, const Rotator<U>& r) {
    out << "[";
    if (r.size()) {
        int i{};
        for (; i < r.size() - 1; ++i)
            out << r[i] << ", ";
        out << r[i];
    }
    out << "]";
    return out;
}

#endif  // __ROTATOR_H