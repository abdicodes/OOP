#pragma once

#include "Company.hpp"
#include <string>

using std::string;

/**
 * @brief      This class describes an employee.
 */
class Employee {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  _name     The name
     * @param      _company  The company
     */
    Employee(string _name, Company& _company);
    /**
     * @brief      Gets the number of co-workers.
     *
     * @return     The number of co-workers.
     */
    int getNumCoworkers();

    string name;
    /**
     * Instead of storing the Company object, Employee uses reference in
     * constructor and as a member variable. This stops the object passed into
     * constructor from being copied, so the object could be directly modified
     * by Employee. It also takes less memory space.
     */
    Company& workplace;
};