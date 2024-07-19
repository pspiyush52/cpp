#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <stdexcept>
#include <ios>

class IndexError : public std::out_of_range{
    public:
        IndexError() : std::out_of_range("Index value out of bounds"){}
        IndexError(const char* msg) : std::out_of_range(msg){}
};

class ListEmpty : public std::out_of_range{
    public:
        ListEmpty() : std::out_of_range("List empty"){}
        ListEmpty(const char* msg) : std::out_of_range(msg){}
};

class ArgError : public std::invalid_argument {
    public:
        ArgError() : std::invalid_argument("Invalid argument"){}
        ArgError(const char* msg) : std::invalid_argument(msg){}
};

class ValueError : public std::domain_error{
    public:
        ValueError() : std::domain_error("Invalid value"){}
        ValueError(const char* msg) : std::domain_error(msg){}
};

class FileIOError : public std::ios_base::failure {
    public:
        FileIOError() : std::ios_base::failure("Invalid file stream object"){}
        FileIOError(const char* msg) : std::ios_base::failure(msg){}
};

class FileInputError : public FileIOError {
    public:
        FileInputError() : FileIOError("Invalid input file stream object"){}
        FileInputError(const char* msg) : FileIOError(msg){}
};

class FileOutputError : public FileIOError {
    public:
        FileOutputError() : FileIOError("Invalid output file stream object"){}
        FileOutputError(const char* msg) : FileIOError(msg){}
};

#endif  // __EXCEPTIONS_H