#include "Company.hpp"
#include <ostream>

using std::cout;

Company::Company(string _name) 
  : name{_name} {
    // cout << "Constructor called to create " << name << ".\n";
}

Company::Company(string _name, int _num)
  : name{_name},
    numberOfEmployees{_num} {
    // cout << "Constructor called to create " << name << " with " << numberOfEmployees << " employees.\n";
}

Company::~Company() {
    // cout << "Destructor is called on " << name << ".\n";
}

void Company::panic() {
    cout << "AAAHHH!!!\n";
}

void Company::setEmployees(int newValue) /*const*/ {
    if (newValue > 0) {
        numberOfEmployees = newValue;
    }
}

void Company::announceNumOfEmployees() const {
    cout << "There are " << numberOfEmployees << " employees in " << name << ".\n";
}

bool Company::operator<(const Company &aCompany) {
    // "this" pointer contains the address of the object it was called at.
    return /*this->*/numberOfEmployees < aCompany.numberOfEmployees;
}

/**
 * This operator overloading is not part of the class namespace.
 */
std::ostream& operator<<(std::ostream& stream, const Company& aCompany) {
    stream << aCompany.name << "[" << aCompany.numberOfEmployees << "]";
    return stream;
}