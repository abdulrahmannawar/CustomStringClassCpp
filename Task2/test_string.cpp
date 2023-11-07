#include "my_string.hpp"
#include <iostream>

int main() {
    my_string s("Hello World");
    s.print();
    {
        my_string t = s;
        s.print();
        t.print();
        std::cout << s.get_char(1) << std::endl;
        s.print();
        t.print();
    }
    s.set_char(1, 'E');
    s.print();
}