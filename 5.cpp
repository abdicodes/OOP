#include <fstream>
#include <iostream>
#include <exception>
#include <string>

using std::cout;

/**
 * @brief      "noexcept" function shouldn't throw any exceptions. They should
 *             be dealt with inside the function.
 */
void functionWithNoExceptions() noexcept {
    throw 42;
};

int main() {
    /**
     * Code in "try" block may through an exception. "catch" looks for exception
     * of particular type and executes only if an exception of that type was
     * thrown in "try" block.
     */
    try {
        throw "My exception"; // Throws string exception.
    } catch (const char* message) {
        cout << message << "\n";
    }

    try {
        int i{42};
        throw i; // Throws an integer variable.
        // Code in try-block immediately stops execution the moment an exception
        // is thrown.
        throw 42;    // Throws integer.
        throw 42L;   // Throws long.
        throw 42ULL; // Throws unsigned long long.
    } catch (int i) { // Catches integers.
        cout << "Suspicious integer: " << i << ".\n";
    } catch (long i) { //Catches longs.
        cout << "Integer " << i << " is actually long.\n";
    } catch (...) { // Catches everything that wasn't caught before.
        cout << "The exception actually was of unknown type.\n";
    }

    /**
     * Usually classes are thrown as exceptions. <exception> header describes
     * standard class for exceptions: std::exception. Standard exceptions are
     * usually divided into logic and runtime errors.
     */
    try {
        throw std::logic_error("Beyond computer logic."); // std::logic is a class derived from std::exception
    } catch (const std::exception& e) { // Derived classes can be be caught by their base classes.
        std::cerr << typeid(e).name() << ": " << e.what() << "\n"; // std::cerr is a stream for error messages.
        // return 1; 
        // throw; // Re-throws an error.
    }

    try {
        throw std::out_of_range("What range?");
    } catch (const std::out_of_range& orr) {
        std::cerr << typeid(orr).name() << ": " << orr.what() << "\n";
    }

    /**
     * If "noexcept" function does throw an exception, it won't be caught. The
     * application will be terminated.
     */
    try {
        // functionWithNoExceptions();
    } catch (...) {
        cout << "I caught something!\n";
    }

    cout << "\n";

    // {
    /**
     * Opens a file "file.txt" for writing.
     */
    std::ofstream o_file{"file.txt"};

    /**
     * Writes into the file.
     */
    o_file << "Hello,\nWorld!\nHello,\nWorld!\nHello,\nWorld!\n";
    /**
     * Files opened for writing must be closed. They're automatically closed
     * when the end of block is reached.
     */
    // }
    o_file.close();

    /**
     * Opens a file for reading.
     */
    std::ifstream i_file{"file.txt"};
    std::string line;

    if (i_file.is_open()) {
        while (std::getline(i_file, line)) {
            cout << line << " ";
        }
    } else {
        cout << "Nope\n";
    }

    cout << "\n";

    /**
     * ofstream and ifstream are part of fstream.
     */
    std::fstream f_file;
    /**
     * Opens a file for writing in append mode.
     */
    f_file.open("file.txt", std::fstream::out | std::fstream::app);
    f_file << "My\nNew\nLines\n.\n";
    f_file.close();

    /**
     * Opens a file for reading.
     */
    f_file.open("file.txt", std::fstream::in);

    if (f_file.is_open()) {
        while (std::getline(f_file, line)) {
            cout << line << " ";
        }
    } else {
        cout << "Nope\n";
    }

    cout << "\n";

    return 0;
}