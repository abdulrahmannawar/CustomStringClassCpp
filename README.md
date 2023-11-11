<h1 id="top">Advanced Systems Programming - Worksheet 1</h1>

<h2>Contents</h2>
<ul>
    <li><a href="#description">Description</a></li>
    <li><a href="#dependencies">Dependencies</a></li>
    <li><a href="#compiling">Compiling and Running the Files</a></li>
    <li><a href="#tasks">Tasks</a></li>
    <li><a href="#task1-3_file">Tasks 1-3 test file</a></li>
    <li><a href="#task4_file">Task 4 test file</a></li>
    <li><a href="#extra">Extra</a></li>
</ul>

<h2 id="description">Description</h2>

The first aim of this project is to create a smaller scale, but functioning, user-created C-Style string class.<br>

The second aim is to create and demonstrate how reference counting in regards to memory manipulation works.

<h2 id="dependencies">Dependencies</h2>

<ul>
<li><a href="https://releases.llvm.org/download.html">Clang</a>: For compiling the source files (USING C++17).
<li><a href="https://ftp.gnu.org/gnu/make/">GNU Make</a>: For building and running the project.</li>
</ul>

<h2 id="compiling">Compiling and Running the Files</h2>
<p style="font-style: italic; font-size: 12px;">NOTE: ENSURE DEPENDENCIES ARE INSTALLED IF NOT USING CSCTCLOUD</p>
<li>First to build the src files, run in the terminal (in root directory):<br><br>

```bash
make
```

<br>
<li>Then to run a task, run in the terminal (in root directory):</li><br>

```bash
make run <Folder Name>
```
Example:

    make run Task2


<h2 id="tasks">Tasks</h2>
<li><a href="#task1">Task 1</a></li>
<li><a href="#task2">Task 2</a></li>
<li><a href="#task3">Task 3</a></li>
<li><a href="#task4">Task 4</a></li>


<h3 id="task1">Task 1</h3>
Task 1 aims to create a simple replica of the C-style string class. It provides basic string manipulation operations (such as reassignment), and aims to demonstrate basic dynamic memory allocation and operator overloading.<br><br>

<h4>Default Constructor</h4>

```cpp
my_string::my_string(): data(nullptr), length(0) {}
```
The default constructor initialises the <strong>my_string</strong>'s member variable 'data' as a nullptr and its length to 0. This is to ensure that the objects state pre-initialisation is stable and is successfully created.<br><br>

<h4>Constructor Overload</h4>

```cpp
my_string::my_string(const char* str): data(nullptr), length(0) {
    if (str) {
        length = std::strlen(str);
        data = new char[length + 1];
        std::strcpy(data, str);
    }
    else throw std::invalid_argument("String is null.");
}
```

This constructor creates a <strong>my_string</strong> object from a C-style string. It dynamically allocates memory for the character data (data), copies the input string (str), and updates the length accordingly.
A check for a null string is performed to handle the case where the input string is null, throwing an invalid_argument exception.<br><br>

<h4>Copy Constructor</h4>

```cpp
my_string::my_string(const my_string& rhs) {
    copy(rhs);
}
```

The copy constructor is responsible for initializing a new <strong>my_string</strong> object by copying the contents of another <strong>my_string</strong> object (rhs).
To avoid code duplication and aim for readability, the actual copying logic is implemented in the private copy helper method.<br><br>

<h4>Copy Assignment Operator</h4>

```cpp
my_string& my_string::operator=(const my_string& rhs) {
    if (this != &rhs) 
        copy(rhs);

    return *this; 
}
```

The copy assignment operator does the same thing that the copy constructor does but through the '=' operator. It checks for self-assignment (this != &rhs) to prevent unnecessary work and potential issues with dynamic memory. The dereferenced 'this' being returned allows for method chaining. i.e. my_string s = u = t;<br><br>

<h4>Copy Assignment Using char*</h4>

```cpp
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
```

This overload allows updating the <strong>my_string</strong> object with the contents of a C-style string (rhs) through copying after allocating memory for 'data'.
If the current object (data) already has allocated memory, it deallocates it before copying the new content.<br><br>

<h4>Index Operator Overload</h4>

```cpp
char& my_string::operator[](const int i) {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");

    return data[i];
}
```

The index operator[] is overloaded to provide access to individual characters within the string using '[]'. The reason it returns a character reference is to allow modification. i.e. s[1] = 'E';
It also performs bounds checking first to ensure that the index is valid, throwing an out_of_range exception if not.<br><br>

<h4>Destructor</h4>

```cpp
~my_string() = default;
```

The Destructor for Task 1 was left empty.<br><br>

<h4>Get Character at Index</h4>

```cpp
char my_string::get_char(const int i) const {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");

    return data[i];
}
```

This method retrieves the character at the specified index with bounds checking, ensuring the index is valida nd throwing an error otherwise.<br><br>

<h4>Set Character at Index</h4>

```cpp
void my_string::set_char(const int i, const char& c) {
    if (!is_valid_index(i))
        throw std::out_of_range("Index is out of range.");

    data[i] = c;
}
```

Similar to the function above. However this method uses the specified character to to replace the character at the specified index.<br><br>

<h4>Printing Data</h4>

```cpp
void my_string::print() const {
    std::cout << data << std::endl;
}
```

The print method outputs the 'data' string to the console.

<h4>Helper Methods</h4>
A helper method is any method used to help in the execution of other methods of the class. Helper methods are typically used only inside the scope of the class and are set to private.<br><br>

<h5>Checking Index Validity</h5>

```cpp
bool my_string::is_valid_index(const int i) const {
    return (i >= 0 && i < length);
}
```

This method checks whether a given index is valid within the bounds of the string, preventing out-of-range access. It return a true if its valid, false of otherwise.<br><br>

<h5>Copy Method</h5>

```cpp
void my_string::copy(const my_string& rhs) {
    data = rhs.data;
    length = rhs.length;
}
```


The copy method is used by both the copy constructor and the copy assignment operator. It performs a shallow copy (a copy of an object that contains references of the original object, rather than copies of the actual elements themselves.) of the data and length from one <strong>my_string</strong> object to another.<br><br>

<h4>Task 1 Output</h4>

```
Hello
Hello World
Hello World
Hello World
e: Using get_char
e: Using index operator[]
Hello World
Hello World

Using set_char:
HEllo World
Using index operator[]:
HEllo World
```

<h3 id="task2">Task 2</h2>

<p style="font-style: italic; font-size: 12px;">NOTE: THE REST OF THE TASKS WILL NOT SHOW EVERYTHING IMPLEMENTED DUE TO SIMILIRATIES FROM TASK 1</P>

Task 2 extends the program from task 1. Task 2 implements reference counting for whenever an object is created.<br>

Reference counting is a memory management technique used to track the number of references, or pointers, to a particular object in memory. The idea is to keep a count of how many references point to an object, and when that count drops to zero, it indicates that the object is no longer being used and can be safely deallocated or freed from memory.<br>

Task 2's ref_count is a pointer, because it can be shared between 2 objects for example.

<h4>Default Constructor</h4>

```cpp
my_string::my_string(): data(nullptr), length(0), ref_count(new int(1)) {}
```

The default constructor has an added initialisation from the previous task of ref_count. It initialises refcount to 1 by allocating memory to it.<br><br>

<h4>Constructor Overload</h4>

```cpp
my_string::my_string(const char* str): data(nullptr), length(0), ref_count(nullptr) {
    if (str) {
        // ... previous implementation (shortened)
        ref_count = new int(1);
    } else throw std::invalid_argument("String is null.");
}
```

Does the same as the constructor overload in task 1, but checks is the const char* str is not null first then allocated memory for ref_count with a value of 1.<br><br>

<h4>Copy Constructor</h4>

Does the same as the copy constructor in task 1 but increments ref_count after copying.<br><br>

<h4>Assignment Operator</h4>

```cpp
my_string& my_string::operator=(my_string const& rhs) {
    if (this != &rhs) {
        cleanup();
        copy(rhs);
        (*ref_count)++;
    }
    return *this;
}
```

Similar to the copy constructor. The copy assignment operator first checks if ref_count is 0, and then deallocates memory if so. It then increments the reference count when updating an existing instance with the contents of another instance.<br>

Consider the following scenario to understand the importance of cleanup in the copy assignment operator:

```cpp
my_string s1 = "Hello";
my_string s2 = "World";

s1 = s2; // Copy assignment
```
<li>Before Copy Assignment:</li>

s1 contains "Hello" and has its own allocated memory.
s2 contains "World" and has its own allocated memory.

<li>During Copy Assignment:</li>

cleanup is called on s1, deallocating its existing memory.
The content of s2 ("World") is copied into s1.
After Copy Assignment:

Both s1 and s2 now share the same dynamically allocated memory for the string data, and the reference count is correctly updated.<br>


<h4>Print Method</h4>

```cpp
void my_string::print() const {
    std::printf("%s [%d]\n", data, *ref_count);
}
```

The print() method now outputs the data alongside the reference_count.<br>

<h4>Destructor</h4>

```cpp
my_string::~my_string() {
    cleanup();
}
```

The destructor now calls cleanup().<br>

<h4>Helper Methods</h4>

<h5>Deallocating Memory</h5>

```cpp
void my_string::cleanup() {
    if (ref_count && --(*ref_count) == 0) {
        delete ref_count;
        delete[] data;
    }
}
```

The cleanup method is introduced to deallocate memory for both data and ref_count when the reference count reaches 0, indicating that there are no more references to the current object.<br>

<h5>Copy Method</h5>

```cpp
void my_string::copy(const my_string& rhs) {
    // ...
    ref_count = rhs.ref_count;
}
```

The copy() method now assigns the ref_count of rhs (object) to the current object (this).<br><br>

<h4>Output</h4>

```
Hello [1]
Hello World [1]
Hello World [2]
Hello World [2]
e: Using get_char
e: Using index operator[]
Hello World [2]
Hello World [2]

Using set_char:
HEllo World [1]
Using index operator[]:
HEllo World [1]
```

<h3 id="task3">Task 3</h3>

The purpose of task 3 is to demonstrate a reference count of 0. However this is impossible because if an object has a reference count of 0 that means it no longer exists in memory, thus having no way to access it. The only way to demonstrate this was to add a print() method call before deallocating memory in the the cleanup method that was being called in the destructor.

<h4>Deallocating Memory (used in destructor)</h4>

```cpp
void my_string::cleanup() {
    if (ref_count && --(*ref_count) == 0) {
        print(); /* Demonstrates a ref_count of 0 */
        delete ref_count;
        delete[] data;
    }
}
```

<h4>Output</h4>

```
Hello [1]
Hello World [1]
Hello World [2]
Hello World [2]
e: Using get_char
e: Using index operator[]
Hello World [2]
Hello World [2]

Using set_char:
HEllo World [1]
Using index operator[]:
HEllo World [1]
HEllo World [0]
```

<h3 id="task4">Task 4</h3>

The purpose of task 4 is to remove all previous implementation of reference counting in my_string, and to create a new template class for reference counting that can count the reference of any datatype being passed through.

Steps:
<ol>
    <li>Remove anything related to reference counting from my_string class.</li>
    <li>Implemet the reference counting template class.</li>
    <li>Allow for integration of my_string to be used with the reference counting class.</li>
</ol>

<h4>Step 1 - remove ref_counting from my_string</h4>

```cpp
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
```

<h4>Step 2 - Implement reference count template class</h4>

<h5>Default Constructor</h3>

```cpp
ReferenceCounter() = delete;
```
This statement disallows the default constructor from being referenced whatsoever. The reason is this would show no beneficial use case.<br>

<h5>Constructor Overload</h5>

```cpp
ReferenceCounter(T* object_ptr) {
    if (!object_ptr) 
        throw std::invalid_argument("Null pointer passed to constructor.");

    ptr = object_ptr;
    ref_count = new int(1);
}
```

This constructor takes a pointer to an object (object_ptr) of type T for initialisation. It checks if the pointer being passed through is not null before assigning its value to ptr. It allocates memory for the reference count (ref_count) and sets its initial value to 1 (since an object gets created when this connstructor gets called).<br>

<h5>Copy Constructor and Assignment</h5>

Both the copy constructor and copy assignment operator do the same as the previous tasks. They perform shallow copies of the content from the right-hand side (rhs) to the current object (this). They increment the reference count appropriately.

<h5>Other operator overloads</h5>

The class overloads several operators, including the dereference operator (*), equality operator (==), allowing instances of this class to be used similarly to regular pointers.

```cpp
/* Dereference pointer operator - allows you to dereference an object to return ONLY its value */
T& operator*() const { return *ptr; }

/* Equality operator overload - allows you to compare two objects of type ReferenceCounter */
T& operator==(const ReferenceCounter& rhs) const { return ptr == rhs.ptr; }

```

<h5>Output Stream Operator Overload</h5>

```cpp
friend std::ostream& operator<<(std::ostream& os, ReferenceCounter& other) {
    os << *(other.ptr);
    std::cout << " [" << other.get_refcount() << "]";
    return os;
}
```

This function outputs the dereferenced pointer of ptr and the current ref_count alongside it when using cout to print the object.

<li>The friend keyword is used to declare a function as a friend of a class (access to private members). In this case, the operator<< function is a friend of the ReferenceCounter class, allowing it access to private members of the class.</li>
<br>
<li>std::ostream& os is a reference to the output stream, in this case the cout stream.</li>
<br>
<li>ReferenceCounter& other is a reference to the ReferenceCounter object that is being printed.</li>
<br>
<li>os << *(other.ptr) outputs the value pointed to by the ptr member of the ReferenceCounter object. It dereferences the pointer and prints the actual value of the managed object.</li>
<br>
<li>std::cout << " [" << other.get_refcount() << "]" prints the reference count enclosed in square brackets. The get_refcount() method is used to obtain the reference count of the ReferenceCounter object.</li>


<h4>Step 3 - Integrating features to use reference_coount instance of type my_string</h4>

<h5>Arrow Operator in reference_count.hpp</h5>

```cpp
/* Arrow operator overload - allows you to access the members of the object pointed to by the pointer
Example: an object of my_string has members.
    If you create an object of type ReferenceCount<T> named obj,
    with T being "my_string", you would be able to
    access those mebers with the arrow opeartor: 
        obj->get_char(1); 
*/
T* operator->() const { return ptr; }
```

<h5>Output Stream Operator Overload in my_string.hpp</h5>

```cpp
/* Outputs the data of the my_string object to the ostream. */
std::ostream& operator<<(std::ostream& os, const my_string& rhs) {
    os << rhs.data;
    return os;
}
```

Allows you to be able to dereference an object of type ReferenceCount\<my_string> and then output the contents of the my_string instance using cout.<br> <em>Shown in the test file of Task 4 (main.cpp)</em>

<h4>Output</h4>

```
var1<int> value: 123
var1<int> ref_count after var2<int> creation: 2
var1<int> value & ref_count after var3<int> creation: 123 [3]
var2<int> value & ref_count after var3<int> creation: 123 [3]
var1<int> value & ref_count after var3<int> destruction: 123 [2]
var1<int> value & ref_count after var2<int> destruction: 123 [1]

var1<double> value: 123.456
var1<double> ref_count after var2<double> creation: 2
var1<double> value & ref_count after var3<double> creation: 123.456 [3]
var2<double> value & ref_count after var3<double> creation: 123.456 [3]
var1<double> value & ref_count after var3<double> destruction: 123.456 [2]
var1<double> value & ref_count after var2<double> destruction: 123.456 [1]

var1<my_string> value: Hello, world!
var1<my_string> ref_count after var2<my_string> creation: 2
var1<my_string> value & ref_count after var3<my_string> creation: Hello, world! [3]
var1<my_string> value at index [2] using index operator[]: l
var1<my_string> value at index [2] using ->get_char: l
var2<my_string> value & ref_count after var3<my_string> creation: Hello, world! [3]
var1<my_string> value & ref_count after var3<my_string> destruction: Hello, world! [2]
var1<my_string> value & ref_count after var2<my_string> destruction: Hello, world! [1]
```

<h2 id="task1-3_file">Task 1-3 Test File</h2>

```cpp
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
```

The test file demonstrates the ability to initialise and copy object using both the copy constructor and the assignment operator as well as redifiniton of the string.It also demonstrates using the index operator in comparison to the the the member methods set_char and get_char.

<h2 id="task4_file">Task 4 Test File</h2>

```cpp
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
```

This test program demnonstrates the use of:
<li>The dereference operator.</li>
<li>The arrow operator.</li>
<li>The index operator.</li>
<li>The output stream operator.</li>
<li>Copy Contructor initialisation.</li>
<li>Copy Assignment initialisation.</li>
<li>Copy Assignment redefinition.</li>

<h2 id="extra">Extra</h2>

In Task1 my_string.hpp

```cpp
/* Tried to implement strcmp replica overloads but didnt work */
// static int my_strcmp(const char*, const my_string&);
// static int my_strcmp(const my_string&, const my_string&);
// static int my_strcmp(const my_string&, const char*);
```

In Task1 my_string.cpp

```cpp
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
```

The test file:

```cpp
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
```

Also couldn't get the equality operator to work in task4:

```cpp
/* Equality operator overload - allows you to compare two objects of type ReferenceCounter */    
// T& operator==(const ReferenceCounter& rhs) const { return ptr == rhs.ptr; }

```

<h2><a href="#top">Back to top</a></h2>