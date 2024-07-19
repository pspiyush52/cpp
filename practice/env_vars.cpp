/* 
 * The optional envp parameter is an array of strings representing the
 * variables set in the user's environment. This array is terminated by
 * a NULL entry. It can be declared as an array of pointers to char
 * (char *envp[]) or as a pointer to pointers to char (char **envp).
 * 
 * The environment block passed to main and wmain is a "frozen" copy of
 * the current environment.
 */
#include <iostream>

int main(int argc, char* argv[], char* envp[])
{
    for (int i{}; envp[i] != NULL; ++i)
        std::cout << (i + 1) << ": " << envp[i] << '\n';
    return 0;
}