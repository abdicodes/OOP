#include <iostream>
#include <string>
// Header files contain declarations of the class members, whereas cpp file
// containts the implementation.
#include "Company.hpp"

using std::cout;
using std::string;

int main() {
    // The scope defined by curly brackets.
    // The class objects are destroyed at the end of the scope.
    {
        Company blackMesa{"Black Mesa"};
        blackMesa.announceNumOfEmployees();
        // Static method does not need an object ot be instantiated.
        Company::panic();
        // It can be called from the object, but they are still tied to the
        // class.
        blackMesa.panic();
    }
    Company aperture{"Aperture", 3};
    aperture.announceNumOfEmployees();
    return 0;
}