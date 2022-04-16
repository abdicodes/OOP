#include <iostream>

using std::cout;
using std::endl;
// using namespace std;

// [return type] [function name]([arguments]) {
//     [body of the function]
//     return [return type]
// }

/**
 * @brief      Sums two integers.
 *
 * @param[in]  a     First integer
 * @param[in]  b     Second integer
 *
 * @return     The sum of two integers.
 */
int sumTwoNumbers(int a, int b) {
    return a + b;
}

/**
 * @brief      Adds 10 to the integer. This function overloads
 *             sumTwoNumbers(int, int).
 *
 * @param[in]  a     Integer
 *
 * @return     The sum of an initeger and 10.
 */
int sumTwoNumbers(int a) {
    return a + 10;
}

/**
 * @brief      Sums two floats. Another function overloading.
 *
 * @param[in]  a     First float
 * @param[in]  b     Second float
 *
 * @return     The sum of two floats.
 */
float sumTwoNumbers(float a, float b) {
    return a + b;
}


/**
 * @brief      Function prototype. Unlike JS, C++ does not have function
 *             hoisting. Function prototype "promises" to the compiler that
 *             there will be a function with that name, parameters, and return
 *             type. The parameters require only the type, their name could be
 *             any or skipped all together.
 *
 * @param[in]  <unnamed>  { parameter_description }
 *
 * @return     { description_of_the_return_value }
 */
int second(int);
// int second(int someVariableNameThatIsDifferentFromTheOneUsedLater);

/**
 * @brief      Mutually recursive function calling for the function that was
 *             defined later in the file. No error thrown because second(int)
 *             has a function prototype.
 *
 * @param[in]  i     Some number
 *
 * @return     Zero if i is less than or equal to zero.
 */
int first(int i) {
    if (i <= 0) {
        return 0;
    }
    cout << "first i is " << i << "\n";
    return second(i - 2);
}

/**
 * @brief      Second function relying on the first.
 *
 * @param[in]  i     Some number
 *
 * @return     See first(int).
 */
int second(int i) {
    if (i <= 0) {
        return 0;
    }
    cout << "second i is " << i << "\n";
    return first(i + 1);
}

// Global variable
int x{5};

/**
 * @brief      Automatically determines the return type. If the function has
 *             several returns, all of them must return the same type.
 *
 * @return     True.
 */
auto typeOfReturn() {
    if (x == 5) {
        return true;
    } else {
        // return 5; // ERROR: Auto determined the return type as bool from line 106.
        return false;
    }
}

/**
 * @brief      Static variables are not destroyed when functions stops.
 *
 * @return     Incremented static variable.
 */
int increment() {
    static int i{0};
    return ++i;
}

/**
 * @brief      Pass-by-value.
 *
 * @param[in]  j     Copy of an integer
 *
 * @return     Modified copy.
 */
int modifyValue(int j) {
    j += 100;
    cout << "modifyValue: " << j << "\n";
    return j;
}

/**
 * @brief      Pass-by-pointer.
 *
 * @param      j     Pointer to the variable
 *
 * @return     Dereferenced pointer after modifying the variable its pointing at.
 */
void modifyValueByPointer(int* j) {
    *j += 100;
    cout << "modifyValueByPointer: " << *j;
    // return *j;
}

/**
 * @brief      Pass-by-reference. 
 *
 * @param      j        A reference to the variable
 * @param[in]  summand  Parameter with default value
 *
 * @return     j
 */
void modifyValueByReference(int& j, const int& summand = 100) {
    j += summand;
    cout << "modifyValueByReference: " << j;
    // return j;
}

/**
 * @brief      Main function.
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     Zero, if successfully completed.
 */
int main(int argc, char const *argv[]) {
    for (int i{}; i < argc; ++i)
        std::cout << argv[i] << std::endl;

    int sum{sumTwoNumbers(5, 6)};
    cout << "Sum is " << sum << endl;
    float sumf{sumTwoNumbers(1.2f, 3.3f)};
    cout << "Sumf is " << sumf << endl << endl;

    cout << "Start first()..." << endl << first(10) << endl 
         << "first() and second() have finished" << endl << endl;

    cout << "Static i: " << increment() << endl;
    cout << "Static i: " << increment() << endl;
    cout << "Static i: " << increment() << endl << endl;

    int val{5};
    int modifiedValue{modifyValue(val)};

    cout << "Val is " << val
         << " and modified val is " << modifiedValue << endl << endl;

    double pi = 3.14;
    // "*" is an indirection operator or dereference operator
    // "&" gives address of the variable in memory
    double* pPi = &pi;
    // Pointer to different types are different.
    auto typeOfPointer = &pi;
    cout << "Type of variable typeOfPointer: " << typeid(typeOfPointer).name() << endl << endl;

    cout << "pi value: " << pi << endl;
    cout << "Address of pi: " << &pi << endl;
    cout << "pPi value: " << pPi << endl;
    cout << "Address of pPi: " << &pPi << endl;
    cout << "Dereferencing pPi pointer: " << *pPi << endl << endl;

    cout << "Value at the start: " << val << endl;
    cout << "Function call: ";
    modifyValueByPointer(&val);
    cout << endl;
    cout << "Changed value: " << val << endl;
    cout << "Function call: ";
    modifyValueByReference(val, 50);
    cout << endl;
    cout << "Changed value: " << val << endl;

    double tmp{1.23};

    // A pointer to constant.
    // Can't modify the variable it points at, but can point at another variable.
    const double* pointerToConst{&pi};
    // *pointerToConst = 1.23; // ERROR: Tries to modify a constant value.
    pointerToConst = &tmp;

    // A constant pointer.
    // Can modify the variable, but cannot point at something else.
    double* const constantPointer{&pi};
    // constantPointer = &tmp; // ERROR: Tries to change the pointer.
    *constantPointer = 1.23;

    // Constant pointer to a constant
    const double* const constantPointerToConstant{&pi};

    return 0;
}