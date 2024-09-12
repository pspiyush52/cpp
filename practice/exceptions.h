#ifndef __EXCEPTIONS_H
#define __EXCEPTIONS_H

#include <stdexcept>
#include <ios>

class IndexError : public std::exception {
    public:
        IndexError() : msg("Index out of bounds"){}
        IndexError(const char* msg) : msg(msg){}
        virtual const char* what() const noexcept {
            return msg;
        }
    private:
        const char* msg;
};

class NullStateException : public std::exception {
    public:
        NullStateException() {
            this->msg = "Null object";
        }
        NullStateException(const char* message): msg{message} {}
        virtual const char* what() const noexcept {
            return msg;
        }
    private:
        const char* msg;
};

class SizeError : public std::exception {
    public:
        SizeError(const char* message) : msg{message} {}
        virtual const char* what() const noexcept {
            return msg;
        }
    private:
        const char* msg;
};

class ListEmpty : public SizeError {
    public:
        ListEmpty() : SizeError("List empty"){}
        ListEmpty(const char* message) : SizeError(message){}
};

class DequeEmpty : public SizeError {
    public:
        DequeEmpty(): SizeError("Deque empty") {}
        DequeEmpty(const char* message): SizeError(message) {}
};

class StringEmpty : public SizeError {
    public:
        StringEmpty(): SizeError("String empty") {}
        StringEmpty(const char* message): SizeError(message) {}
};

class SetEmptyError : public SizeError {
    public:
        SetEmptyError() : SizeError("Set empty"){}
        SetEmptyError(const char* msg) : SizeError(msg){}
};

class ArgError : public std::invalid_argument {
    public:
        ArgError() : std::invalid_argument("Invalid argument"){}
        ArgError(const char* msg) : std::invalid_argument(msg){}
};

class ValueError : public std::domain_error {
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