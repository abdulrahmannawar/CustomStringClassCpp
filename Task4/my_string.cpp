#include "my_string.hpp"

#include <iostream>
#include <cstring>
#include <stdexcept> /* for exceptions */

/* Default constructor - initialises data to null and length to 0 */
my_string::my_string(): data(nullptr), length(0) {}

/* Constructor overload - checks if 'str' is not null. */
/* Copies the contents of 'str' into data */
my_string::my_string(const char* str): data(nullptr), length(0) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    } else throw std::invalid_argument("String is null.");
}

/* Copy constructor - initialises a new string and copies the contents of 'rhs' to it. */
my_string::my_string(const my_string& rhs) {
    copy(rhs);
}

/* Copy assignment - update the current object with the contents of 'rhs' through copying. */
/* Check for is no self-assignment occurs */
/* Returns a dereferenced pointer to the current object to allow for method chaining. ie. s = t = u; */
my_string& my_string::operator=(my_string const& rhs) {
    if (this != &rhs) {
        cleanup();
        copy(rhs);
    }
    return *this;
}

/* Copy assignment operator overload - update the current string with the contents of char* 'rhs' through copying. */
/* if data is not null, deallocate memory of data */
/* Then copy the contents of 'rhs' into data including length */
/* Returns a dereferenced pointer to the current object to allow for method chaining. ie. s = t = u; */
my_string& my_string::operator=(const char* rhs) {
    if (data != nullptr) 
        delete[] data;

    length = std::strlen(rhs);
    data = new char[length + 1];
    std::strcpy(data, rhs);

    return *this;
}

/* Destructor - calls helper method cleanup() */
my_string::~my_string() {
    cleanup();
}

/* Returns the character at the specified index 'i'. */
/* Throws an error if index is out of range */
char my_string::get_char(const int i) const {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");
    
    return data[i];
}

/* Sets the character at the specified index 'i' to the specified character 'c'. */
/* Throws an error if index is out of range */
void my_string::set_char(const int i, const char& c) {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");
    
    data[i] = c;
}

/* Prints the string to the console. */
void my_string::print() const {
    std::printf("%s\n", data);
}

/* Outputs the data of the my_string object to the ostream. */
std::ostream& operator<<(std::ostream& os, const my_string& rhs) {
    os << rhs.data;
    return os;
}

/* Helper method to deallocate memory for data */
void my_string::cleanup() {
    delete[] data;
}

/* Helper method to check if the index is valid. */
bool my_string::is_valid_index(const int i) const {
    return (i >= 0 && i < length);
}

/* Helper method to copy (shallow copy) data and length from another object/instance (rhs) to the current object/instance */
void my_string::copy(const my_string& rhs) {
    data = rhs.data;
    length = rhs.length;
}