#ifndef DSSTRING_H
#define DSSTRING_H
#include <iostream>
#include <string>
using namespace std;

// Custom string class with dynamic memory management
class DSString {
private:
    // Raw character data and string length
    char* data;
    size_t len;

    // Helper functions for string manipulation
    static size_t getLength(const char* str);
    static void copyData(char* dest, const char* src, size_t length);

public:
    // Constructors and destructor for memory management
    DSString(); // Default constructor
    DSString(const char* str); 
    DSString(const DSString& other);
    DSString& operator=(const DSString& other);
    ~DSString(); // Destructor

    // Basic string operations
    DSString toLower() const; // Convert to lowercase
    const char* c_str() const;          
    size_t length() const;         

    // Comparison operators
    bool operator==(const DSString& other) const;  
    bool operator<(const DSString& other) const;   

    // Input/Output stream operators
    friend ostream& operator<<(ostream& os, const DSString& str); // Output 
    friend istream& operator>>(istream& is, DSString& str); // Input 
};

#endif // DSSTRING_H
