#include "reference_count.hpp"
#include "my_string.hpp"

#include <iostream>

void int_test();
void double_test();
void my_string_test();

int main() {
    int_test();
    double_test();
    my_string_test();
    return 0;
}

void int_test() {
    ReferenceCounter<int> var1(new int(123)); // using constructor for initialisation
    std::cout << "var1<int> value: " << *var1 << std::endl; // using dereference to get only value of var1
    {
        ReferenceCounter<int> var2(var1); // using copy constructor for initialisation
        std::cout << "var1<int> ref_count after var2<int> creation: " << var1.get_refcount() << std::endl; // using method to get only value of ref_count
        { 
            ReferenceCounter<int> var3(var2);
            std::cout << "var1<int> value & ref_count after var3<int> creation: " << var1 << std::endl; // output both the value and ref_count of the var
            std::cout << "var2<int> value & ref_count after var3<int> creation: " << var2 << std::endl;
        }
        std::cout << "var1<int> value & ref_count after var3<int> destruction: " << var1 << std::endl;
    }
    std::cout << "var1<int> value & ref_count after var2<int> destruction: " << var1 << std::endl << std::endl;
}

void double_test() {
    ReferenceCounter<double> var1 = new double(123.456); // using assignment for initialisation
    std::cout << "var1<double> value: " << *var1 << std::endl; // using dereference to get only value of var1
    {
        ReferenceCounter<double> var2 = var1; // using assignment for initialisation
        std::cout << "var1<double> ref_count after var2<double> creation: " << var1.get_refcount() << std::endl; // using method to get only value of ref_count
        {
            ReferenceCounter<double> var3 = var2;
            std::cout << "var1<double> value & ref_count after var3<double> creation: " << var1 << std::endl; // output both the value and ref_count of the var
            std::cout << "var2<double> value & ref_count after var3<double> creation: " << var2 << std::endl;
        }
        std::cout << "var1<double> value & ref_count after var3<double> destruction: " << var1 << std::endl;
    }
    std::cout << "var1<double> value & ref_count after var2<double> destruction: " << var1 << std::endl << std::endl;
}

void my_string_test() {
    ReferenceCounter<my_string> var1 = new my_string("Hello, world!"); // using assignment for initialisation
    std::cout << "var1<my_string> value: " << *var1 << std::endl; // using dereference to get only value of var1
    {
        ReferenceCounter<my_string> var2 = var1; // using assignment for initialisation
        std::cout << "var1<my_string> ref_count after var2<my_string> creation: " << var1.get_refcount() << std::endl; // using method to get only value of ref_count
        {
            ReferenceCounter<my_string> var3(var2); // using copy constructor for initialisation
            std::cout << "var1<my_string> value & ref_count after var3<my_string> creation: " << var1 << std::endl;
            std::cout << "var1<my_string> value at index [2] using index operator[]: " << (*var1)[2] << std::endl; // using dereference + index operator of my_string
            std::cout << "var1<my_string> value at index [2] using ->get_char: " << var1->get_char(2) << std::endl; // using arrow operator of my_string to get_char
            std::cout << "var2<my_string> value & ref_count after var3<my_string> creation: " << var2 << std::endl;
        }
        std::cout << "var1<my_string> value & ref_count after var3<my_string> destruction: " << var1 << std::endl;
    }
    std::cout << "var1<my_string> value & ref_count after var2<my_string> destruction: " << var1 << std::endl << std::endl;
}