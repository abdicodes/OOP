#pragma once

#include "Employee.hpp"

/**
 * @brief      This class describes a scientist. Base class can be called with
 *             access specifiers (default is "private"). "public" specifier
 *             means that public and protected members of the base class have
 *             the access specifier in derived class.
 */
class Scientist : public Employee {
public:
    /**
     * Using all Employee constructors for Scientist class.
     */
    using Employee::Employee;
    /**
     * @brief      Starts a resonance cascade. This function is not accessible
     *             by Employee objects.
     */
    void startResonanceCascade();
};