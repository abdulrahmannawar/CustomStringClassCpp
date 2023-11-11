#include "my_string.hpp"

#include <iostream>
#include <cstring>
#include <stdexcept> /* for exceptions */

/* Default constructor - initialises data to null and length to 0 */
my_string::my_string(): data(nullptr), length(0) {}

/* Constructor overload - creates a string by allocating memory for the data pointer. */
/* Check if str is not null */
/* Then copy the contents of 'str' into data */
my_string::my_string(const char* str): data(nullptr), length(0) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
    else throw std::invalid_argument("String is null.");
}

/* Copy constructor - initialises a new string and copies the contents of 'rhs' to it. */
my_string::my_string(const my_string& rhs) {
    copy(rhs);
}

/* Copy assignment - update the current object with the contents of 'rhs' through copying. */
/* Check for is no self-assignment occurs */
/* Returns a dereferenced pointer to the current object to allow for method chaining. ie. s = t = u; */
my_string& my_string::operator=(my_string const& rhs) {
    if (this != &rhs) 
        copy(rhs);

    return *this; 
}

/* Copy assignment operator overload - update the current string with the contents of char* 'rhs' through copying. */
/* if data is not null, deallocate memory of data */
/* Then copy the contents of 'rhs' into data including length */
/* Returns a dereferenced pointer to the current object to allow for method chaining. ie. s = t = u; */
my_string& my_string::operator=(const char* rhs) {
    if (data) {
        delete[] data;
    } 

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

/* Tried to implement strcmp replica but it didn't work */
// int my_string::my_strcmp(const char* str1, const my_string& str2) {
//     int i = 0;
//     while (str1[i] != '\0' && str2.get_char(i) != '\0') {
//         if (str1[i] != str2.get_char(i)) {
//             return (str1[i] < str2.get_char(i)) ? -1 : 1;
//         }
//         i++;
//     }

//     if (str1[i] == '\0' && str2.get_char(i) == '\0') {
//         return 0;
//     } else if (str1[i] == '\0') {
//         return -1;
//     } else {
//         return 1;
//     }
// }

/* Returns the character at the specified index 'i'. */
/* Throws an exception if the index is out of range with a message */
char my_string::get_char(const int i) const {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");
    
    return data[i];
}

/* Sets the character at the specified index 'i' to the specified character 'c'. */
/* Throws an exception if the index is out of range with a message */
void my_string::set_char(const int i, const char& c) {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");
    
    data[i] = c;
}

/* Prints the string to the console. */
void my_string::print() const {
    std::cout << data << std::endl;
}

/* Returns true if the specified index 'i' is valid (i.e. greater than 0 and less than the length of the string) */
bool my_string::is_valid_index(const int i) const {
    return (i >= 0 && i < length);
}

/* Copies (shallow copy) the data and length from 'rhs' string into the current string. */
void my_string::copy(const my_string& rhs) {
    data = rhs.data;
    length = rhs.length;
}
