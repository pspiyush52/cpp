#ifndef __DEFS_H
#define __DEFS_H

#include <stdio.h>

#ifndef repeatu
#define repeatu(N) for (unsigned int i = 0; i < N; ++i)
#endif

#ifndef repeats
#define repeats(N) for (size_t i = 0; i < N; ++i)
#endif

#ifndef repeat
#define repeat(N) for (int i = 0; i < N; ++i)
#endif

#ifndef repeat_from
#define repeat_from(from, to, i) for (i = from; i < to; ++i)
#endif

#ifndef repeat_with
#define repeat_with(N, i) for (i = 0; i < N; ++i)
#endif

#ifndef repeat_until
#define repeat_until(N) while(!(N))
#endif

#ifndef newline
#define newline putchar('\n')
#endif

#ifndef newl
#define newl '\n'
#endif

#ifndef begin_main
#define begin_main int main(int argc, char* argv[]){
#endif

#ifndef end_main
#define end_main return 0;}
#endif

#ifndef begin_if
#define begin_if(E) if((E)) {
#endif

#ifndef end_if
#define end_if }
#endif

#ifndef sep
/// Draw a dashed line on the console output ending with a newline character.
#define sep std::cout << "===============================================================================================================================\n"
#endif

#ifdef _GLIBCXX_MEMORY
template<typename T>
using u_ptr = std::unique_ptr<T>;

template<typename T>
using s_ptr = std::shared_ptr<T>;

template<typename T>
using w_ptr = std::weak_ptr<T>;
#endif  // _GLIBCXX_MEMORY

#endif  // __DEFS_H