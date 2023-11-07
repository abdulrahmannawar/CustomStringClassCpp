#pragma once

#include <iostream>

class my_string {
public:
    my_string(); 
    my_string(const char*);
    my_string(const my_string&);
    my_string& operator=(const my_string&);
    my_string& operator=(const char*);
    ~my_string();

    char get_char(const int) const;
    void set_char(const int, const char&);
    void print() const;

    friend std::ostream& operator<<(std::ostream&, const my_string&);

private:
    int length;
    char* data;

    void cleanup();
    bool is_valid_index(const int) const;
    void copy(const my_string&);
};