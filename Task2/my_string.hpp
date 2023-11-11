#pragma once /* include guard to prevent multiple declarations of the header file. */

class my_string {
public:
    /* Constructors */
    my_string();                            /* default constructor */
    my_string(const char*);                 /* constructor overload */
    my_string(const my_string&);            /* copy constructor */
    my_string& operator=(my_string const&); /* copy assignment operator overload */
    my_string& operator=(const char*);      /* assignment operator overload */
    char& operator[](const int);            /* index operator overload */   
    ~my_string();                           /* destructor */

    /* Methods */
    char get_char(const int) const;          /* get character at index */
    void set_char(const int, const char& c); /* set character at index */
    void print() const;                      /* print string */

private:
    int length; /* length of string */
    char* data; /* pointer to string data */
    int* ref_count; /* reference count */

    /* Helper methods */
    void cleanup();                       /* clean up memory */
    bool is_valid_index(const int) const; /* check if index is valid */
    void copy(const my_string&);          /* copy data, length and ref_count from another string */
};