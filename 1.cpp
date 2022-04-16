#include <iostream>
#include <cmath> // For power function
#include <climits> // For CHAR_BIT constant
// #include <numbers> // For pi constant // Requires C++20 or newer

int main() {
    /**
     * C++ is a strongly typed language. 
     * 
     * Example of some types used in C++:
     *
     * "int", "long int", "long long int" are integer types of different size; Can be "unsigned"
     *
     * "float", "double", "long double" — numbers with fractional part, their
     * number of digits of precision is approx. 7, 15, 18 respectively
     * 
     * "bool" for booleans
     * 
     * ...and many others.
     */

    /**
     * Three ways to initialise a variable in C++:
     */
    int myInt{0}; // Braced initializer
    int myIntFuncNot(0); // Functional notation
    int myIntAssNot = 0; // Assignment notation
    int hex = 0xFF; // Hexadecimal numbers start with 0x
    int oct = 0100; // Octal numbers start with 0
    int bin = 0b10000000000; // Binary numbers start with 0b

    /**
     * << is used to insert the value in the character output stream
     */
    std::cout << "Your hex value is " << hex << std::endl;
    /**
     * Both std::endl and "\n" can be used to add a new line to the output.
     */
    std::cout << "Your octal value is " << oct << "\n";
    std::cout << "Your binary value is " << bin << "\n";

    /**
     * C way to write data.
     */
    printf("Hex value is %d\n\n", hex);

    /**
     * Constants can be declared with const keyword.
     */
    const int NINE{9};
    const int TWO{2};

    /**
     * The integer divided by integer will output an integer.
     */
    std::cout << "9 / 2 = " << NINE / TWO << std::endl;
    std::cout << "9 mod 2 = " << NINE % TWO << std::endl;
    std::cout << "1 / 3.0 = " << 1 / 3.0f << std::endl << std::endl;

    float myFloat{0.1234567890123456789};
    double myDouble{0.1234567890123456789};
    long double myLongDouble{0.1234567890123456789};

    printf("Float: %.20f\n", myFloat);
    printf("Double: %.20f\n", myDouble);
    printf("Long double: %.20Lf\n\n", myLongDouble);

    std::cout << "Integer is " << sizeof(int) << " bytes" << std::endl;
    int maxInt = std::pow(2, sizeof(int) * CHAR_BIT) / 2 - 1;
    std::cout << "Max integer is " << maxInt << "\n";
    std::cout << "Integer overflow: " << maxInt + 1 << "\n"; // Integer overflow

    unsigned int maxUnsignInt = maxInt * 2 + 1;
    std::cout << "Max unsigned integer is " << maxUnsignInt << "\n";
    std::cout << "Unsigned integer overflow: " << maxUnsignInt + 1 << "\n"; // Unsigned integer overflow, returns to 0

    long int myLongInt;
    char myChar{127};

    /**
     * auto keyword is used to force compiler to figure the type of the
     * variable. The variable must be initialised during the declaration.
     *
     * "f" letter specifies floats, "l" — long, "ll" — long long, "u" — unsigned
     */
    auto autoVariable = 1ull;
    std::cout << "Size of the autoVariable is " << sizeof(autoVariable) << " bytes\n\n";

    bool isTrue = true;
    if (isTrue) {
        std::cout << "isTrue is " << isTrue << "\n" << std::endl;
    }

    /**
     * Creates an array of five integer elements and initialises the first four
     * elements with the values in the brackets.
     */
    int myArray[5]{9, 7, 5, 3};

    for (int i = 0; i < 5; ++i) {
        printf("%d element is %d\n", i + 1, myArray[i]);
    }

    /**
     * C++ will send a warning if -Warray-bound is specified, but there will be
     * no error if you try to access the garbage outside of the array.
     */
    std::cout << myArray[100] << "\n\n";

    int i{10};
    while (i --> 0) {
        std::cout << "i: " << i << std::endl;
    }

    // pi const
    // std::cout << std::numbers::pi << std::endl; // Requires C++20

    return 0;
}