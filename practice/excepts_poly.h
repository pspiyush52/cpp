#ifndef __EXCEPTS_POLY_H
#define __EXCEPTS_POLY_H

#include "arr_strings.h"

class ExceptionBase{
    public:
        ExceptionBase(const char* message, size_t line_num) : warning_message(message), l_num(line_num){}
        ExceptionBase(const ExceptionBase& src) = default;
        ExceptionBase(ExceptionBase&& src) : warning_message(std::move(src.warning_message)){}
        virtual const string what() const { return ("Exception: " + warning_message); }
        friend inline void show_ex(ExceptionBase& ex, const char* filename);
    protected:
        string warning_message;
        size_t l_num;
};

class Warning : public ExceptionBase{
    public:
        Warning(const char* message, size_t line_num) : ExceptionBase(message, line_num){}
        const string what() const override { return ("Warning: " + warning_message); }
};

class SmallError : public Warning{
    public:
        SmallError(const char* message, size_t line_num) : Warning(message, line_num){}
        const string what() const override { return ("SmallError: " + warning_message); }
};

class CriticalError : public SmallError{
    public:
        using SmallError::SmallError;
        const string what() const override { return ("CriticalError: " + warning_message); }
};

inline void show_ex(ExceptionBase& ex, const char* filename){
    std::cout << "In file \"" << filename << "\"\nException occurred at line "
        << ex.l_num << ":\n  " << ex.what() << '\n';
}

#endif  // __EXCEPTS_POLY_H