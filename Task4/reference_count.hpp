#pragma once

#include <iostream>
#include <stdexcept>

template<class T>
class ReferenceCounter {
public:
    /* Defualt constructor - disallowed from being referenced in main */
    ReferenceCounter() = delete;
    
    /* Constructor overload = pass an pointer of type T for initialisation if not null */
    ReferenceCounter(T* object_ptr) {
        if (!object_ptr) 
            throw std::invalid_argument("Null pointer passed to constructor.");

        ptr = object_ptr;
        ref_count = new int(1);
    }

    /* Copy constructor - copies (shallow copy) content from object 'rhs' to current object */
    ReferenceCounter(const ReferenceCounter& rhs)  { copy(rhs); }
    
    /* Copy assignment operator overload - copies (shallow copy) content from object 'rhs' to current object using '=' */
    ReferenceCounter& operator=(const ReferenceCounter& rhs) {
        if (this != &rhs) {
            cleanup();
            copy(rhs);
        }
        return *this;
    }

    /* Dereference pointer operator - allows you to dereference an object to return ONLY its value */
    T& operator*() const { return *ptr; }

    /* Equality operator overload - allows you to compare two objects of type ReferenceCounter */
    // T& operator==(const ReferenceCounter& rhs) const { return ptr == rhs.ptr; }

    /* Arrow operator overload - allows you to access the members of the object pointed to by the pointer */
    T* operator->() const { return ptr; }

    /* Destructor - deletes the pointer and decrements the reference count */
    ~ReferenceCounter() { cleanup(); }

    /* Friend function - allows you to print the value of the object and its reference count tp ostream */
    friend std::ostream& operator<<(std::ostream& os, ReferenceCounter& other) {
        os << *(other.ptr);
        std::cout << " [" << other.get_refcount() << "]";
        return os;
    }

    /* Returns the reference count of the object */
    int get_refcount() const { return *ref_count; }

private:
    T* ptr; /* Pointer to the object */
    int* ref_count; /* Pointer to the reference count of the object */

    /* Helper functions */

    /* Deallocates memory of ptr and ref_count */
    void cleanup() {
        if (ref_count && --(*ref_count) == 0) {
            delete ref_count;
            delete ptr;
        }
    }
    
    /* Copies(shallow copy) the contents of 'rhs' to the current object */
    void copy(const ReferenceCounter& rhs) {
        ptr = rhs.ptr;
        ref_count = rhs.ref_count;
        (*ref_count)++;
    }
};