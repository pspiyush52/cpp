/*
 * The final specifier allows us to do one of two things:
 *     > Restrict how we override virtual methods in derived classes.
 *     > Restrict how we can derived from base classes.
 * 
 * So we can mark a virtual function as final to prevent it from being
 * overriden in any of the derived classes.
 * 
 * Also we can mark a class as final to disallow any class to inherit from it.
 */
#define sep std::cout << "===================================================\n";
#include "arr_string.h"
/*
 * The inheritance tree,
 * 
 *                         +--------employee--------+
 *                         |         (base)         |
 *                         |                        |
 *                         |                        |
 *                      manager                  sr_assoc
 *                                                  |
 *                                                  |
 *                                                  |
 *                                                assoc
 */
class employee {
    public:
        employee() = default;
        employee(const string& Name, const string& Emp_Id):
            name(new string(Name)), emp_id(new string(Emp_Id)){
                std::cout << "employee created at " << this << '\n';
            }
        employee(const char* Name, const char* Emp_Id):
            name(new string(Name)), emp_id(new string(Emp_Id)){}
        ~employee(){
            delete name;
            delete emp_id;
        }

        virtual void show() final {
            std::cout << "employee::show()\nName: " << *name << ", Employee ID: "
                << *emp_id << '\n';
        }
        virtual void print() const {
            std::cout << "employee::print()\nName: " << *name
                << "\nEmployee ID: " << *emp_id << '\n';
        }

    protected:
        string* name{};
        string* emp_id{};
};

class manager final : public employee {
    public:
        manager(const string& Name, const string& Emp_Id, unsigned int Team_Size):
            employee(Name, Emp_Id), team_size(Team_Size){}
        manager(const char* Name, const char* Emp_Id, unsigned int Team_Size):
            employee(Name, Emp_Id), team_size(Team_Size){}
        
        /*
            // Will result in a compiler error since the show virtual function is
            // marked final in the base class.
            
                void show(){
                    std::cout << "Designation: Manager\n";
                }
        */
        
        void print() const override {
            std::cout << "manager::print()\nName: " << *name
                << "\nCategory: Manager\nEmployee ID: " << *emp_id << '\n';
        }
    private:
        unsigned int team_size;
};

class sr_assoc : public employee {
    public:
        sr_assoc(const string& Name, const string& Emp_Id):
            employee(Name, Emp_Id){}
        sr_assoc(const char* Name, const char* Emp_Id):
            employee(Name, Emp_Id){}
        void print() const override final {
            std::cout << "sr_assoc::print()\nName: " << *name
                << "\nCategory: Associate\n" << "Employee ID: " << *emp_id
                    << '\n';
        }
};

class assoc : public sr_assoc {
    public:
        assoc(const string& Name, const string& Emp_Id):
            sr_assoc(Name, Emp_Id){}
        assoc(const char* Name, const char* Emp_Id):
            sr_assoc(Name, Emp_Id){}
        /*
            Not allowed since print has been marked final in the sr_assoc
            class from which assoc class is deriving.
            So a virtual function can be specified as final anywhere down the
            inheritance hierarchy and from that point on, that function cannot
            be overridden by further classes which derive from that particular
            class.

                void print() const override {
                    std::cout << "Name: " << *name << "\nCategory: Sr. Associate\n"
                        << "Employee ID: " << *emp_id << '\n';
                }
        */
};
/*
    Will result in a compiler error since the manager class is marked final
    which means no class can derived from it.

        class hr_manager : public manager{

        };
*/
int main(void)
{
    manager niharika{"Niharika Joshi", "MBOQ000635564V1", 20};
    manager biswas{"Bob Biswas", "FCIN000041877C2", 12};
    employee piyush{"Piyush Singh", "LLMV000096361S4"};
    employee pranjai{"Pranjai Bhatt", "PQGA000113148P7"};
    sr_assoc someone{"Not Me", "XXXX000874899Z0"};
    assoc random{"Random Human", "YWJP000003423R9"};

    employee* emp = &niharika;
    sep;
    emp->print();
    sep;
    emp->show();  // base show() will be called
    sep;
    emp = &piyush;
    emp->print();
    sep;
    emp->show();  // base show() will be called
    sep;
    emp = &someone;
    emp->print();
    sep;

    employee* employees[] = {&niharika, &piyush, &pranjai, &biswas, &someone, &random};
    std::cout << "\nLooping through employees array and calling print()\n\n";
    for (auto emp : employees)
        { emp->print(); newline; }
    sep;
    std::cout << "\nLooping through employees array and calling show()\n\n";
    for (auto emp : employees)
        { emp->show(); newline; }
    sep;

    return 0;
}