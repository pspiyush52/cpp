#include "arr_strings.h"
#include "defs.h"

void say_name(const string& name){
    std::cout << "Your name is " << name << '\n';
    if (name.similar("niHarIKA"))
    {
        string tmp{name};
        std::cout << "Your full name is " << (name + " Singh").to_upper() << '\n';
    }
}

int main(void)
{
    fmt::line('.');
    string str{"this"};
    std::cout << "\nstr: " << str << '\n';
    std::cout << std::boolalpha << "str.similar(\"This\"): " << str.similar("This") << "\n\n";
    fmt::line('.');

    string s{"somewhere"};

    std::cout << "\ns: " << s << '\n';
    fmt::print_u("Assigning s = \"somewhere across the galaxy\"", '-');

    s = "somewhere across the galaxy";
    std::cout << "After assignment s: " << s << '\n';
    std::cout << "Number of times \'a\' occurs in s: " << s.count('a') << "\n\n";
    fmt::line('.');

    std::cout << "\nAfter moving str to s using assignment: ";
    std::cout << "s = std::move(str)\n";
    s = std::move(str);
    std::cout << "s after the move: " << s << '\n';
    std::cout << "After moving str.is_empty(): " << str.is_empty() << "\n\n";
    fmt::line('.');

    newline;
    fmt::print_u("say_name(\"Niharika\"):", '*');
    say_name("Niharika");
    newline;
    fmt::print_u("say_name(\"Piyush\"):", '*');
    say_name("Piyush");
    newline; fmt::line('.');

    string str2{"Tu hai "};
    string str3{""};

    // When we assign from a temporary object the compiler automatically calls
    // the method which moves the object rather than the one which copies it.
    // This prevents unnecessary copies in our program.
    std::cout << "\nstr2: " << str2 << '\n';
    std::cout << "str3.is_empty(): " << str3.is_empty() << '\n';
    std::cout << "(str3 = (str2 + \"ekdam nalla\")): " << (str3 = (str2 + "ekdam nalla")) << '\n';
    std::cout << "str3.is_empty(): " << str3.is_empty() << "\n\n";
    fmt::line('.');

    arr::Array<string> str_arr{s, str2, str3};
    std::cout << "\narr::Array<string> str_arr{s, str2, str3}\n";
    std::cout << "str_arr: " << str_arr << "\n\n";
    fmt::line('.');
    
    return 0;
}