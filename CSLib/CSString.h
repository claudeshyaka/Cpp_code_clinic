// CSString.h
// A simple smart string class
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#ifndef __CSLIB__CSString__
#define __CSLIB__CSString__

#ifdef _MS_VER
// disable _s warnings
#pragma _CRT_SECURE_NO_WARNINGS
// disable pragma warnings
#pragma warning(disable : 4068)
#include "bw_msposix.h"
#endif

#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <string>
#include <vector>

#define __CSString__VERSION "1.0.0"
#define __CSString__MAX_LEN 65535

// simple smart C-string
class CSString
{
private:
    char *_str = nullptr;
    size_t _str_len = 0;

public:
    static const char *version() { return __CSString__VERSION; }
    CSString(); // default constructor
    CSString(const char *s);
    CSString(const CSString &); // copy constructor
    ~CSString();

    const char *alloc_str(size_t sz);   // smart alloc string
    void reset();                       // frees the string
    const char *value() const;          // getter (legacy)
    const char *c_str() const;          // getter
    const char *copy_str(const char *); // alloc & copy

    // operators
    CSString &operator=(const char *);         // assigment operator
    CSString &operator=(const CSString &);     // assigment operator
    CSString &operator+=(const char *);        // concatenation operator
    CSString &operator+=(const CSString &rhs); // concatenation operator

    // comparisons
    bool operator==(const CSString &) const;
    bool operator!=(const CSString &) const;
    bool operator>(const CSString &) const;
    bool operator<(const CSString &) const;
    bool operator>=(const CSString &) const;
    bool operator<=(const CSString &) const;

    // conversion operators
    operator const char *() const; // c-string type
    operator std::string() const;  // c++ string class

    // Utility methods
    bool have_value() const;
    size_t length() const;
    CSString &format(const char *format, ...);
    CSString &trim();
    const char &last_char() const;
    const std::vector<CSString> split(const char *match) const;
    const std::vector<CSString> split(const char *match, int max_split) const;
    const CSString &char_repl(const char &match, const char &repl);
};

// function overloads
CSString operator+(const CSString &lbs, const CSString &rhs);

#endif // defined(__CSLIB__CSString__)