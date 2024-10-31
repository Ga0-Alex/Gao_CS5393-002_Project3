#include "DSString.h"
using namespace std;  // Use standard namespace for implementation

// Get the length of the C-string, return 0 if null
size_t DSString::getLength(const char* str) {
    if (!str) return 0;
    size_t length = 0;
    while (str[length] != '\0') length++;
    return length;
}

// Copy string data with null terminator
void DSString::copyData(char* dest, const char* src, size_t length) {
    if (!dest || !src) return;
    for (size_t i = 0; i < length; i++) {
        dest[i] = src[i];
    }
    dest[length] = '\0';
}

// Initialize empty string
DSString::DSString() : data(nullptr), len(0) {}

// Construct from C-string, handling null case
DSString::DSString(const char* str) {
    if (str) {
        len = getLength(str);
        data = new char[len + 1];
        copyData(data, str, len);
    } else {
        data = nullptr;
        len = 0;
    }
}

// Deep copy constructor
DSString::DSString(const DSString& other) : len(other.len) {
    if (other.data) {
        data = new char[len + 1];
        copyData(data, other.data, len);
    } else {
        data = nullptr;
    }
}

// Deep copy assignment, protect against self-assignment
DSString& DSString::operator=(const DSString& other) {
    if (this != &other) {
        delete[] data;
        len = other.len;
        if (other.data) {
            data = new char[len + 1];
            copyData(data, other.data, len);
        } else {
            data = nullptr;
        }
    }
    return *this;
}

// Free dynamic memory
DSString::~DSString() {
    delete[] data;
}

// Create new lowercase version of string
DSString DSString::toLower() const {
    DSString result(*this);
    for (size_t i = 0; i < len; i++) {
        if (result.data[i] >= 'A' && result.data[i] <= 'Z') {
            result.data[i] = result.data[i] + ('a' - 'A');
        }
    }
    return result;
}

// Return raw C-string (empty string if null)
const char* DSString::c_str() const {
    return data ? data : "";
}

// Return string length
size_t DSString::length() const {
    return len;
}

// Check string equality character by character
bool DSString::operator==(const DSString& other) const {
    if (len != other.len) return false;
    for (size_t i = 0; i < len; i++) {
        if (data[i] != other.data[i]) return false;
    }
    return true;
}

// Lexicographical comparison
bool DSString::operator<(const DSString& other) const {
    size_t minLen = min(len, other.len);
    for (size_t i = 0; i < minLen; i++) {
        if (data[i] < other.data[i]) return true;
        if (data[i] > other.data[i]) return false;
    }
    return len < other.len;
}
