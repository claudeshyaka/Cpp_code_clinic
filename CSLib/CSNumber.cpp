// CSNumber.cpp
// A simple number library
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#include "CSNumber.h"

#pragma mark - constructors

CSNumber::CSNumber() : _lnum(0L), _dnum(0.0) {}

CSNumber::CSNumber(const int &n)
{
    _lnum = n;
    _dnum = double(_lnum = n);
}

CSNumber::CSNumber(const long &n)
{
    _lnum = n;
    _dnum = double(_lnum = n);
}

CSNumber::CSNumber(const double &d)
{
    _lnum = long(_dnum = d);
    _dnum = d;
}

CSNumber::CSNumber(const char *s)
{
    _lnum = atol(s);
    _dnum = atof(s);
}

CSNumber::CSNumber(const CSNumber &csn)
{
    _lnum = csn._lnum;
    _dnum = csn._dnum;
}

CSNumber::~CSNumber()
{
    _dnum = _lnum = 0;
}

#pragma mark - utilities

void CSNumber::reset()
{
    _lnum = 0L;
    _dnum = 0.0;
}

const char *CSNumber::c_str_long()
{
    snprintf(_buffer, __CSNumber_BUFSIZE, "%ld", _lnum);
    return _buffer;
}

const char *CSNumber::c_str_double()
{
    snprintf(_buffer, __CSNumber_BUFSIZE, "%lf", _dnum);
    return _buffer;
}

#pragma mark - arithmetic

CSNumber &CSNumber::add(const CSNumber &n)
{
    _lnum += n._lnum;
    _dnum += n._dnum;
    return *this;
}
CSNumber &CSNumber::sub(const CSNumber &n)
{
    _lnum -= n._lnum;
    _dnum -= n._dnum;
    return *this;
}
CSNumber &CSNumber::div(const CSNumber &n)
{
    _lnum /= n._lnum;
    _dnum /= n._dnum;
    return *this;
}
CSNumber &CSNumber::mul(const CSNumber &n)
{
    _lnum *= n._lnum;
    _dnum *= n._dnum;
    return *this;
}

#pragma mark - assignment overloads

CSNumber &CSNumber::operator=(const CSNumber &n)
{
    _lnum = n._lnum;
    _dnum = n._dnum;
    return *this;
}

CSNumber &CSNumber::operator=(const long &n)
{
    _lnum = int(n);
    _dnum = (double)n;
    return *this;
}

CSNumber &CSNumber::operator=(const double &n)
{
    _lnum = int(n);
    _dnum = n;
    return *this;
}

#pragma mark - operators

CSNumber &CSNumber::operator+=(const CSNumber &n)
{
    return this->add(n);
}

CSNumber &CSNumber::operator-=(const CSNumber &n)
{
    return this->sub(n);
}

CSNumber &CSNumber::operator/=(const CSNumber &n)
{
    return this->div(n);
}

CSNumber &CSNumber::operator*=(const CSNumber &n)
{
    return this->mul(n);
}

#pragma mark - comparison operators

bool CSNumber::operator==(const CSNumber &rhs) const
{
    if ((_lnum == rhs._lnum) && (_dnum == rhs._dnum))
        return true;
    else
        return false;
}

bool CSNumber::operator!=(const CSNumber &rhs) const
{
    if ((_lnum != rhs._lnum) && (_dnum != rhs._dnum))
        return true;
    else
        return false;
}

bool CSNumber::operator>(const CSNumber &rhs) const
{
    if ((_lnum > rhs._lnum) && (_dnum > rhs._dnum))
        return true;
    else
        return false;
}

bool CSNumber::operator<(const CSNumber &rhs) const
{
    if ((_lnum < rhs._lnum) && (_dnum < rhs._dnum))
        return true;
    else
        return false;
}

bool CSNumber::operator>=(const CSNumber &rhs) const
{
    if ((_lnum >= rhs._lnum) && (_dnum >= rhs._dnum))
        return true;
    else
        return false;
}

bool CSNumber::operator<=(const CSNumber &rhs) const
{
    if ((_lnum <= rhs._lnum) && (_dnum <= rhs._dnum))
        return true;
    else
        return false;
}

#pragma mark - increment/decrement operators

CSNumber &CSNumber::operator++()
{
    _lnum += 1;
    _dnum += 1.0;
    return *this;
}

CSNumber CSNumber::operator++(int)
{
    CSNumber temp = *this;
    ++(*this);
    return temp;
}

CSNumber &CSNumber::operator--()
{
    _lnum -= 1;
    _dnum -= 1.0;
    return *this;
}

CSNumber CSNumber::operator--(int)
{
    CSNumber temp = *this;
    --(*this);
    return temp;
}

#pragma mark - conversion operators

CSNumber::operator int() const
{
    return (int)_lnum;
}
CSNumber::operator long() const
{
    return _lnum;
}
CSNumber::operator double() const
{
    return _dnum;
}

#pragma mark - binary operators

CSNumber operator+(const CSNumber &lhs, const CSNumber &rhs)
{
    CSNumber rn = lhs;
    rn += rhs;
    return rn;
}

CSNumber operator-(const CSNumber &lhs, const CSNumber &rhs)
{
    CSNumber rn = lhs;
    rn -= rhs;
    return rn;
}

CSNumber operator/(const CSNumber &lhs, const CSNumber &rhs)
{
    CSNumber rn = lhs;
    rn /= rhs;
    return rn;
}

CSNumber operator*(const CSNumber &lhs, const CSNumber &rhs)
{
    CSNumber rn = lhs;
    rn *= rhs;
    return rn;
}