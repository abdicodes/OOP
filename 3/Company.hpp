// Non-standard directive to the compiler to make sure that the file would be
// included only once.
#pragma once

// #ifndef company_hpp
// #define company_hpp

// #endif

#include <string>
#include <iostream>

// cout isn't used in the header, but it'll be automatically added to the cpp
// file that includes this header.
using std::cout;
using std::string;

/**
 * @brief      This class describes a company.
 */
class Company {
public:
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  _name  The name
     */
    Company(string _name);
    /**
     * @brief      Constructs a new instance.
     *
     * @param[in]  _name      The name
     * @param[in]  numOfEmpl  The number of employees
     */
    Company(string _name, unsigned int numOfEmpl);
    /**
     * @brief      Destroys the object.
     */
    ~Company();

    /**
     * @brief      PANIC!!!111
     *
     *             Static members are tied to the class, not to the objects
     *             created by the class.
     */
    static void panic();

    /**
     * @brief      The company makes an announcement about the number of
     *             employees.
     */
    void announceNumOfEmployees();

    string name;
private:
    unsigned int numberOfEmployees{9001};
};