#include "Employee.hpp"

Employee::Employee(string _name, Company& _company)
  : name{_name},
    workplace{_company} {

}

int Employee::getNumCoworkers() {
    /**
     * Employee is a friend class of a Company and can access the private
     * members.
     */
    return workplace.numberOfEmployees;
}