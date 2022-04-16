#include <iostream>
#include <string>
#include <utility>
#include <vector>

#define LOG(x) std::cout << x << '\n'

class Human {
public:
    // By declaring a function virtual, we mean that there is a possibility that
    // the function is overridden in derived classes.
    [[nodiscard]] virtual std::string name() const { return "Homo sapiens"; }
    [[nodiscard]] virtual bool is_student() const { return false; }
};

class Student : public Human {
public:
    Student(std::string name, unsigned int id) : m_name{std::move(name)}, m_student_id{id} {}
    // Override specifies that the overridden function with the same signature
    // exists and is virtual.
    [[nodiscard]] std::string name() const override { return "Student: " + m_name; }
    [[nodiscard]] unsigned int id() const { return m_student_id; }
    // Final specifies that this is the last override of the virtual functioon
    // and that the method couldn't be overridden by virtual function in the
    // classes derived from this one.
    [[nodiscard]] bool is_student() const final { return true; }

protected:
    std::string m_name;
    unsigned int m_student_id{0};
};

class CS_Student : public Student {
public:
    using Student::Student;
    [[nodiscard]] std::string name() const override { return "CS student: " + m_name; }
    // bool is_student() { return false; } // Shadows the virtual function
    // bool is_student() override { return false; } // ERROR: Non-virtual member function marked 'override' hides virtual member function
};

class British {
public:
    // If virtual function is assigned 0, it is called pure virtual function. If
    // the class has any pure virtual methods, it cannot be instantiated, and
    // any derived class must declare all pure virtual functions from base
    // class.
    [[nodiscard]] virtual std::string species() const = 0;
    [[nodiscard]] virtual bool british_init() const = 0;

protected:
    bool m_is_british{true};
};

class Professor final : public Human, public British {
public:
    explicit Professor(std::string name) : m_name{std::move(name)} {}
    [[nodiscard]] std::string name() const override { return "Professor: " + m_name; }

    // Pure virtual functions of the base class must be overridden in derived class.
    [[nodiscard]] std::string species() const final { return Human::name(); }
    [[nodiscard]] bool british_init() const override { return m_is_british; }

private:
    std::string m_name;
};

void check_for_type(Human* person) {
    if (dynamic_cast<Professor*>(person) != nullptr) {
        LOG("Professor - " << person->name());
    } else if (dynamic_cast<CS_Student*>(person) != nullptr) {
        LOG("CS_Student - " << person->name() << " | ID: " << dynamic_cast<CS_Student*>(person)->id());
    } else if (dynamic_cast<Student*>(person) != nullptr) {
        LOG("Student - " << person->name()  << " | ID: " << dynamic_cast<Student*>(person)->id());
    } else {
        LOG("Unknown type.");
    }
}

int main() {
    Human human;
    Student alex{"Alex", 12345678};

    LOG(human.name());
    LOG(alex.name());

    // A way to access shadowed members.
    // LOG(alex.Human::name());

    // Creates a Human pointer to Student.
    Human* student = &alex;
    // Creates a Human instance without any Student-specific members.
    Human student1 = alex;

    // If class method not marked as virtual, the pointer to the base class will
    // use the method from the base class. Otherwise it will try to determine
    // what type the variable actually is and use the correct method.
    LOG(student->name());
    LOG(student1.name());

    CS_Student tamer{"Tamer", 87654321};

    LOG(tamer.name());
    LOG(tamer.id());

    Human* test = new CS_Student{"Test student", 42};
    LOG(test->name());

    Professor myk{"Matthew Yee-King"};
    LOG(myk.name());
    LOG(std::boolalpha << myk.is_student());

    Human* human_myk = &myk;
    LOG(human_myk->name());

    // Derived class cannot be directly deduced from the pointer to the base class.
    // Professor* prof = human_myk;

    // dynamic_cast converts pointers up and down in the inheritance hierarchy
    // auto* impostor = dynamic_cast<Student*>(human_myk); // returns nullptr
    auto* impostor = dynamic_cast<Professor*>(human_myk);

    if (impostor != nullptr) {
        LOG(impostor->name());
    } else {
        LOG("No impostors found.");
    }

    // Cannot create an instance of the class with pure virtual functions.
    // British brit;

    LOG(myk.species());
    LOG(std::boolalpha << myk.british_init());

    // Can create a pointer to the base class that points at the reference of
    // derived class even if base class has pure virtual functions.
    British* brit = &myk;
    LOG(brit->species());
    LOG(std::boolalpha << brit->british_init());

    // LOG(brit->name()); // ERROR: No member named 'name' in 'British'

    // Creating a vector of objects of derived types with base type.
    std::vector<Human*> classroom;
    classroom.push_back(&alex);
    classroom.push_back(&tamer);
    classroom.push_back(test);
    classroom.push_back(&myk);
    classroom.push_back(human_myk);
    classroom.push_back(impostor);
    classroom.push_back(new Human);
    classroom.push_back(new Student{"Student", 123});
    classroom.push_back(new CS_Student{"Computer Science Student", 0b001});
    classroom.push_back(new Professor{"Robert Zimmer"});

    for (Human* person : classroom) {
        check_for_type(person);
    }

    return 0;
}
