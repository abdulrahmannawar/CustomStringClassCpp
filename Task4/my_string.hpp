#pragma once

#include <iostream>

class my_string {
public:
    my_string();                            /* Default constructor */
    my_string(const char*);                 /* Constructor overload */
    my_string(const my_string&);            /* Copy constructor */
    my_string& operator=(const my_string&); /* Copy assignment operator overload */
    my_string& operator=(const char*);      /* Assignment operator overload */
    char& operator[](const int);            /* Index operator overload */
    ~my_string();                           /* Destructor */

    char get_char(const int) const;         /* Get character at index */
    void set_char(const int, const char&);  /* Set character at index */
    void print() const;                     /* Print string */

    friend std::ostream& operator<<(std::ostream&, const my_string&);   /* Output operator overload */

private:
    int length; /* Length of string */
    char* data; /* Pointer to string data */

    void cleanup();                         /* Helper method to deallocate memory for data */
    bool is_valid_index(const int) const;   /* Helper method to check if the index is valid */
    void copy(const my_string&);            /* Helper method to copy (shallow copy) data and length from another object/instance (rhs) to the current object/instance */
};