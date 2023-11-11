#include "my_string.hpp"

#include <iostream>
#include <cstring>
#include <stdexcept> /* for exceptions */

/* Default constructor - initialises : the data pointer to nullptr, the length to 0 and allocates memory to ref_count with a value of 1. */
my_string::my_string(): data(nullptr), length(0), ref_count(new int(1)) {}

/* Constructor overload - checks if 'str' is not null. */
/* Copies the contents of 'str' into data */
my_string::my_string(const char* str): data(nullptr), length(0), ref_count(nullptr) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
        ref_count = new int(1);
    } else throw std::invalid_argument("String is null.");
}

/* Copy constructor - initialises a new string and copies the contents of 'rhs' to it. */
my_string::my_string(const my_string& rhs) {
    copy(rhs);
    (*ref_count)++;
}

/* Copy assignment - update the current object with the contents of 'rhs' through copying. */
/* Check for is no self-assignment occurs */
/* Returns a dereferenced pointer to the current object to allow for method chaining. ie. s = t = u; */
my_string& my_string::operator=(my_string const& rhs) {
    if (this != &rhs) { // check if no self-assignment occurs
        cleanup();
        copy(rhs);
        (*ref_count)++;
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

    if (rhs) {
        length = std::strlen(rhs);
        data = new char[length + 1];
        std::strcpy(data, rhs);
    }

    return *this;
}

/* Index operator overload - returns the character at the specified index 'i'. */
char& my_string::operator[](const int i) {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");
    
    return data[i];
}

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

/* Prints the string and the ref_count */
void my_string::print() const {
    std::printf("%s [%d]\n", data, *ref_count);
}

/* Helper method to deallocate memory if the ref_count is 0. i.e all objects are destroyed */
void my_string::cleanup() {
    if (ref_count && --(*ref_count) == 0) {
        print(); /* Demonstrates a ref_count of 0 */
        delete ref_count;
        delete[] data;
    }
}

/* Helper method to check if the index is valid. */
bool my_string::is_valid_index(const int i) const {
    return (i >= 0 && i < length);
}

/* Helper method to copy (shallow copy) the data, length and ref_count from another object/instance. */
void my_string::copy(const my_string& rhs) {
    data = rhs.data;
    length = rhs.length;
    ref_count = rhs.ref_count;
    
}