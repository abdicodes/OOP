#include "Company.hpp"

// Comments and documentation usually go into the header. 

Company::Company(string _name) 
  : name{_name} {
    cout << "Constructor called to create " << name << ".\n";
}

Company::Company(string _name, unsigned int _num)
  : name{_name},
    numberOfEmployees{_num} {
    cout << "Constructor called to create " << name << " with " << numberOfEmployees << " employees.\n";
}

Company::~Company() {
    cout << "Destrcutor is called on " << name << ".\n";
}

void Company::panic() {
    cout << "AAAHHH!!!\n";
}

void Company::announceNumOfEmployees() {
    cout << "There are " << numberOfEmployees << " employees in " << name << ".\n";
}

