/* NON-FUNCTIONING PROGRAM FOR STRCMP */

#include <iostream>
#include <cstring> // for strcmp
#include "../Task1/my_string.hpp"

int main() {
    // Test case 1: Both strings are the same
    const char* str1 = "Hello World!";
    my_string str2 = "Hello World!";
    const char* str3 = "Hello World!";
    std::cout << "Test 1 result: " << my_string::my_strcmp(str1, str2) << " Expected: " << strcmp(str1, str3) << std::endl;

    // Test case 2: str1 is lexicographically less than str2
    str1 = "Hello World!";
    str2 = "Hello World!!";
    str3 = "Hello World!!";
    std::cout << "Test 2 result: " << my_string::my_strcmp(str1, str2) << " Expected: " << strcmp(str1, str3) << std::endl;

    // Test case 3: str1 is lexicographically greater than str2
    str1 = "Hello World!!";
    str2 = "Hello World!";
    str3 = "Hello World!";
    std::cout << "Test 3 result: " << my_string::my_strcmp(str1, str2) << " Expected: " << strcmp(str1, str3) << std::endl;

    return 0;
}