#include "Company.hpp"
#include "Employee.hpp"
#include "Scientist.hpp"
#include <iostream>
#include <string>

using std::cout;
using std::string;

int main() {
    Company blackMesa{"Black Mesa"};
    blackMesa.announceNumOfEmployees();
    Company aperture{"Aperture", 3};
    aperture.announceNumOfEmployees();

    cout << "\n";

    // ---------------------------------

    /**
     * Default copy constructor initialises new object with data of old object.
     */
    Company apertureScience{aperture};

    /**
     * Changing the name of the new object.
     */
    cout << apertureScience.name << "\n";
    apertureScience.name = "Aperture Science";
    cout << apertureScience.name << "\n\n";

    /**
     * Changing the member variables of object that was copied and its copy does
     * not affect each other.
     */
    aperture.setEmployees(2);
    apertureScience.setEmployees(1000);
    aperture.announceNumOfEmployees();
    apertureScience.announceNumOfEmployees();

    cout << "\n";

    /**
     * Object can be a constant.
     */
    const Company mannCo{"Mann Co.", 9};
    /**
     * Constant objects can read non-constant member variables, but they can't
     * modify them. They also can't access non-constant member functions.
     */
    cout << mannCo.name << "\n";
    // mannCo.name = "Mann"; // ERROR: Trying to change a member variable of a constant object
    // mannCo.setEmployees(10); // ERROR: Calling non-constant member function from constant object
    mannCo.announceNumOfEmployees();

    // cout << aperture.numberOfEmployees; // ERROR: 'numberOfEmployees' is a private member of 'Company'

    cout << "\n";

    /**
     * Creating a new object of ~Employee~ Scientist type and passing another
     * object as an argument in the constructor.
     */
    /* Employee */ Scientist scientist{"Gordon Freeman", blackMesa};
    cout << scientist.name << " works with " << scientist.getNumCoworkers() << " people.\n";

    /**
     * Overloading the less-than operator, so objects of type Company could be
     * compared to each other. Operators greater-than, equal, not equal,
     * less-than or equal, greater-than or equal must be overloaded
     * independently, though C++20 have a spaceship operator that simplifies
     * comparison overloading.
     */
    if (aperture/*.getNumberOfEmployees()*/ < blackMesa/*.getNumberOfEmployees()*/) {
        cout << aperture/*.name*/ << " has less employees than " << blackMesa/*.name*/ << ".\n\n";
    }

    scientist.startResonanceCascade();
    cout << scientist.name << " works with " << scientist.getNumCoworkers() << " people.\n";
    blackMesa.announceNumOfEmployees();

    return 0;
}
