#include "my_string.hpp"
#include <iostream>

int main() {
    // my_string s("Hello World"); // using constructor for initialisation
    my_string s = "Hello"; // using assignment for initialisation
    s.print();
    s = "Hello World"; // using assignment for REDEFINITON
    s.print();
    {
        my_string t = s;
        s.print();
        t.print();
        std::cout << s.get_char(1) << ": Using get_char" << std::endl;
        std::cout << s[1] << ": Using index operator[]" << std::endl;
        s.print();
        t.print();
    }
    std::cout << "\nUsing set_char:" << std::endl;
    s.set_char(1, 'E'); 
    s.print();

    std::cout << "Using index operator[]:" << std::endl;
    s[1] = 'E'; 
    s.print();
}