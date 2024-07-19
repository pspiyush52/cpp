#include "iterator.h"

int main(void)
{
    List<int> numlist{12, 54, 1, 2, 31, 17};
    std::cout << "List of ints: " << numlist << '\n';
    for (int& num : numlist)
        num += 12;
    std::cout << "List of ints: " << numlist << '\n';

    const List<const char*> names{
        "Niharika Joshi", "Piyush Singh", "Pranjai Bhatt",
        "Ankit Singh", "Pratima Punj"
    };
    std::cout << "Names: " << names << '\n';
    // Using the const iterator(will work even for non-const objects)
    List<const char*>::const_iterator begin = names.cbegin();
    while (begin != names.cend())
        std::cout << *begin++ << '\n';
    
    std::cout << "Names[4]: " << names[4] << '\n';
    try{
        std::cout << "Names[5]: " << names[5] << '\n';
    }catch(const IndexError& ex){
        ex.describe();
    }
    
    return 0;
}
/**
 * ============================== ITERATORS ==============================
 * 
 * Input iterators are iterators that can be used in sequential input
 * operations, where each value pointed by the iterator is read only once
 * and then the iterator is incremented.
 * It is used to read data from containers. They are single pass.
 * Supported operations:
 *          1. iterator new_it(it);
 *             new_it = it;
 *             i.e., must be copy-constructible, copy-assignable and
 *             destructible.
 *          2. it_1 == it_2;
 *             it_1 != it_2;
 *          3. *it (read);  // dereferenceable as rvalue
 *          4. it-> (read)
 *          5. ++it; it++;  // incrementable
 *             *it++;  // dereferenceable with ++
 * 
 * Output iterators are iterators that can be used in sequential output
 * operations, where each element pointed by the iterator is written a
 * value only once and then the iterator is incremented.
 * It is used to write data into containers. They are single pass.
 * Supported operations:
 *          1. iterator new_it(it);
 *             new_it = it;
 *             i.e., must be copy-constructible, copy-assignable and
 *             destructible.
 *          2. *it = t;  // dereferenceable as an lvalue.
 *             It shall only be dereferenced as the left side of an
 *             assignment statement. Once dereferenced, its iterator may
 *             no longer be dereferenceable.
 *          3. ++it; it++;  // incrementable
 *             *it++;  // dereferenceable with ++
 * 
 * Forward iterators are iterators that can be used to access the
 * sequence of elements in a range in the direction that goes from its
 * beginning towards its end.
 * Performing operations on a forward iterator that is dereferenceable
 * never makes its iterator value non-dereferenceable i.e., they are
 * multi-pass iterators.
 * This enables algorithms that use this category of iterators to use
 * multiple copies of an iterator to pass more than once by the same
 * iterator values.
 * Supported operations:
 *          1. iterator it_1;
 *             iterator it_2(it_1);
 *             it_2 = it_1;
 *             i.e., they must be default-constructible, copy-
 *             constructible, copy-assignable and destructible.
 *          2. it_1 == it_2;
 *             it_1 != it_2;
 *          3. Can be dereferenced as an rvalue or lvalue(non-constant
 *             iterators).
 *             *it_1; it_1->m;
 *             *it_1 = t;
 *          4. ++it; it++;  // incrementable
 *             *it++;  // dereferenceable with ++
 * 
 * Bidirectional iterators are iterators that can be used to access the
 * sequence of elements in a range in both directions(forward and
 * backward).
 * Bidirectional iterators have the same properties as forward iterators,
 * with the only difference that they can also be decremented.
 * Supported operations:
 *          1. iterator it_1;
 *             iterator it_2(it_1);
 *             it_2 = it_1;
 *             i.e., they must be default-constructible, copy-
 *             constructible, copy-assignable and destructible.
 *          2. it_1 == it_2;
 *             it_1 != it_2;
 *          3. Can be dereferenced as an rvalue or lvalue(non-constant
 *             iterators).
 *             *it_1; it_1->m;
 *             *it_1 = t;
 *          4. ++it; it++;  // incrementable
 *             *it++;  // dereferenceable with ++
 *          5. --it; it--;  // decrementable
 *             *it--;   // dereferenceable with --
 * 
 * Random-access iterators are iterators that can be used to access
 * elements at an arbitrary offset position relative to the element they
 * point to, offering the same functionality as pointers.
 * All pointer types are also valid random-access iterators.
 * Supported operations:
 *          1. iterator it_1;
 *             iterator it_2(it_1);
 *             it_2 = it_1;
 *             i.e., they must be default-constructible, copy-
 *             constructible, copy-assignable and destructible.
 *          2. it_1 == it_2;
 *             it_1 != it_2;
 *          3. Can be dereferenced as an rvalue or lvalue(non-constant
 *             iterators).
 *             *it_1; it_1->m;
 *             *it_1 = t;
 *          4. ++it; it++;  // incrementable
 *             *it++;  // dereferenceable with ++
 *          5. --it; it--;  // decrementable
 *             *it--;   // dereferenceable with --
 *          6. Supports arithmetic operators + and - b/w and iterator and
 *             an integer value, or subtracting an integer from another,
 *                  it_1 + n;
 *                  n + it_1;
 *                  it_1 - n;
 *                  it_2 - it_1;
 *             where n is an integer.
 *          7. Can be compared with inequality relational operators (<, >
 *             <= and >=),
 *                  it_1 < it_2;
 *                  it_1 > it_2;
 *                  it_1 <= it_2;
 *                  it_1 >= it_2;
 *          8. Supports compound assignment operations += and -=,
 *                  it += n;
 *                  it -= n;
 *          9. Supports the offset dereference operator([]),
 *                  it[n];
 */