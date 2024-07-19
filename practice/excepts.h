#ifndef __EXCEPTS_H
#define __EXCEPTS_H

#include "arr_strings.h"

class ExceptionBase{
    public:
        ExceptionBase(const char* message) : warning_message(message){}
        ExceptionBase(const ExceptionBase& src) = default;
        ExceptionBase(ExceptionBase&& src) : warning_message(std::move(src.warning_message)){}
        const string& what() const { return warning_message; }
    protected:
        string warning_message;
};

class Warning : public ExceptionBase{
    public:
        Warning(const char* message) : ExceptionBase(message){}
};

class SmallError : public Warning{
    public:
        SmallError(const char* message) : Warning(message){}
};

class CriticalError : public SmallError{
    public:
        using SmallError::SmallError;
};

#endif  // __EXCEPTS_H