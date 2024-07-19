#ifndef __STREAM_INSERTABLE_H
#define __STREAM_INSERTABLE_H

#include <iostream>
#include <string_view>
/*
 * This is an interface which allows deriving classes to print their objects
 * on the console.
 */
class StreamInsertable{
    public:
        friend std::ostream& operator<<(std::ostream& output, const StreamInsertable& obj);
    protected:
        virtual void stream_insert(std::ostream& output) const = 0;
};

inline std::ostream& operator<<(std::ostream& output, const StreamInsertable& obj){
    obj.stream_insert(output);
    return output;
}

namespace st{
    template<typename T>
    class StreamInsertable{
        public:
            virtual void stream_insert(std::ostream& output) const = 0;
            virtual void stream_insert_s(std::ostream& output) const = 0;
    };
    // For all other types
    template<typename U>
    std::ostream& operator<<(std::ostream& output, const StreamInsertable<U>& obj){
        obj.stream_insert(output);
        return output;
    }

    // For types which have strings to display
    template<typename U>
    requires std::is_convertible_v<U, std::string_view>
    std::ostream& operator<<(std::ostream& output, const StreamInsertable<U>& obj){
        obj.stream_insert_s(output);
        return output;
    }

}

#endif  // __STREAM_INSERTABLE_H