#pragma once

#include <iostream>
#include <ostream>
#include <string>

using std::string;

/**
 * https://en.cppreference.com/w/cpp/language/rule_of_three
 */
class Company {
public:
    /**
     * Constructor with only one argument is risky because of possible implicit
     * conversion from one class to another. "explicit" keyword prevents that.
     */
    explicit Company(string _name);
    Company(string _name, int numOfEmpl);
    ~Company();

    static void panic();

    /**
     * @brief      Sets the employees.
     *
     * @param[in]  <unnamed>  Number of employees
     */
    void setEmployees(int) /*const*/;

    /**
     * Contant member function can be used by constant object.
     */
    void announceNumOfEmployees() const;

    /**
     * @brief      Less-than comparison operator. Takes only one argument
     *             because "a < b" could be written as "a.operator<(b)". If left
     *             argument does not support comparison with your class, e.g.
     *             integer can't be compared with Company, then the operation
     *             overload is not defined as part of a class and takes two
     *             arguments for left and right operand.
     *
     * @param[in]  aCompany  A company
     *
     * @return     The result of the less-than comparison
     */
    bool operator<(const Company& aCompany);

    /**
     * @brief      Overloading "<<", so the objects could be sent to the output
     *             stream. Is not really part of the class, so declared as a
     *             friend, but could be declared outside of the class as well.
     *
     * @param      stream    The output stream
     * @param[in]  aCompany  The company
     *
     * @return     The output stream
     */
    friend std::ostream& operator<<(std::ostream& stream, const Company& aCompany);

    string name;
private:
    /**
     * setEmployees() function can be made constant when the member variable
     * that it changes is set to "mutable".
     */
    /*mutable*/ int numberOfEmployees{9001};

    /**
     * Friend classes can access private members of this class. Friendship is
     * one way and not inheritable.
     */
    friend class Employee;
    friend class Scientist;
};