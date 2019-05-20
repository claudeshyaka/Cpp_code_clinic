// CSNumber.h
// A simple number library
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#ifndef __CSLib__CSNumber__
#define __CSLib__CSNumber__

#ifdef _MSC_VER
//disable _s warnings
#define _CRT_SECURE_NO_WARNINGS
// disable pragma warnings
#pragma warning(disable : 4068)
#endif

#include <cstdlib>
#include "CSString.h"

#define __CSNumber_VERSION "1.0.0"
#define __CSNumber_BUFSIZE 32

class CSNumber
{
private:
    long _lnum;
    double _dnum;

    char _buffer[__CSNumber_BUFSIZE];

public:
    static const char *version() { return __CSNumber_VERSION; }
    CSNumber(); // default constructor
    CSNumber(const int &);
    CSNumber(const long &);
    CSNumber(const double &);
    CSNumber(const char *);
    CSNumber(const CSNumber &); // Copy constructor
    ~CSNumber();

    void reset();
    const char *c_str_long();
    const char *c_str_double();

    CSNumber &add(const CSNumber &n);
    CSNumber &sub(const CSNumber &n);
    CSNumber &div(const CSNumber &n);
    CSNumber &mul(const CSNumber &n);

    CSNumber &operator=(const CSNumber &);
    CSNumber &operator=(const long &);
    CSNumber &operator=(const double &);

    CSNumber &operator+=(const CSNumber &);
    CSNumber &operator-=(const CSNumber &);
    CSNumber &operator/=(const CSNumber &);
    CSNumber &operator*=(const CSNumber &);

    bool operator==(const CSNumber &) const;
    bool operator!=(const CSNumber &) const;
    bool operator<(const CSNumber &) const;
    bool operator>(const CSNumber &) const;
    bool operator>=(const CSNumber &) const;
    bool operator<=(const CSNumber &) const;

    CSNumber &operator++();
    CSNumber operator++(int);
    CSNumber &operator--();
    CSNumber operator--(int);

    operator int() const;
    operator long() const;
    operator double() const;
    operator CSString() const;
};

CSNumber operator+(const CSNumber &lhs, const CSNumber &rhs);
CSNumber operator-(const CSNumber &lhs, const CSNumber &rhs);
CSNumber operator/(const CSNumber &lhs, const CSNumber &rhs);
CSNumber operator*(const CSNumber &lhs, const CSNumber &rhs);

#endif // defined(__CSLib__CSNumber__)