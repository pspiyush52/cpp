#include "print.h"
#include "ordered_map.h"

int main(void)
{
    OrderedSMap<const char*, OrderedSMap<const char*, const char*>> members;
    auto insert = [&members](const char* name, const char* age, const char* occupation) {
        members.insert(name, {{"age", age}, {"occupation", occupation}});
    };
    insert("Niharika", "32", "Consultant");
    insert("Piyush", "28", "Student");
    insert("Prasham", "24", "Student");
    insert("Pranjai", "28", "Architect");
    insert("Ankit", "24", "Relationship Manager");
    insert("Anjali", "26", "Customer Service Associate");
    insert("Sunny", "34", "Tullu");

    // Display Piyush's age
    print(members["Piyush"]["age"]);

    // Display Niharika's occupation
    print(members["Niharika"]["occupation"]);

    // Check if Pranjai is a member and display his occupation
    if (members.contains("Pranjai")) {
        print("Pranjai is a member and he is an", members["Pranjai"]["occupation"]);
        print("He is", members["Pranjai"]["age"], "years old");
    }
    else {
        print("Pranjai is not a member");
    }
    
    return 0;
}
