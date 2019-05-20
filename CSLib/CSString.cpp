// CSString.cpp
// A simple smart string class
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#include "CSString.h"

#pragma mark - constructors/destructors

CSString::CSString()
{
    reset();
}

CSString::CSString(const char *s)
{
    copy_str(s);
}

CSString::CSString(const CSString &old)
{
    copy_str(old);
}

CSString::~CSString()
{
    reset();
}

#pragma mark - public methods

const char *CSString::alloc_str(size_t sz)
{
    if (_str)
    {
        reset();
    }
    _str_len = (sz > __CSString__MAX_LEN) ? __CSString__MAX_LEN : sz;
    _str = (char *)calloc(1, _str_len + 1);
    return _str;
}

void CSString::reset()
{
    if (_str)
    {
        free((void *)_str);
    }
    _str = nullptr;
    _str_len = 0;
}

const char *CSString::value() const
{
    return _str;
}

const char *CSString::c_str() const
{
    return _str;
}

const char *CSString::copy_str(const char *s)
{
    if (s)
    {
        size_t len = strnlen(s, __CSString__MAX_LEN);
        alloc_str(len);
        strncpy((char *)_str, s, len);
        _str_len = len;
    }
    return _str;
}

#pragma mark - operators
CSString &CSString::operator=(const char *cs)
{
    copy_str(cs);
    return *this;
}

CSString &CSString::operator=(const CSString &cs)
{
    copy_str(cs.c_str());
    return *this;
}

CSString &CSString::operator+=(const char *rhs)
{
    if (rhs)
    {
        size_t new_len = _str_len + strnlen(rhs, __CSString__MAX_LEN);
        if (new_len > __CSString__MAX_LEN)
        {
            new_len = __CSString__MAX_LEN;
        }
        char *buf = (char *)calloc(1, new_len + 1);
        if (!buf)
        {
            return *this;
        }
        if (_str && _str_len)
        {
            strncpy(buf, _str, _str_len);
        }
        strncpy(buf + _str_len, rhs, new_len - _str_len);
        buf[new_len] = '\0';
        copy_str(buf);
        free(buf);
    }
    return *this;
}

CSString &CSString::operator+=(const CSString &rhs)
{
    operator+=(rhs.c_str());
    return *this;
}

#pragma mark - comparison operators

bool CSString::operator==(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) == 0)
        return true;
    else
        return false;
}
bool CSString::operator!=(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) != 0)
        return true;
    else
        return false;
}
bool CSString::operator>(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) > 0)
        return true;
    else
        return false;
}
bool CSString::operator<(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) < 0)
        return true;
    else
        return false;
}
bool CSString::operator>=(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) >= 0)
        return true;
    else
        return false;
}
bool CSString::operator<=(const CSString &rhs) const
{
    if (std::strncmp(this->c_str(), rhs.c_str(), __CSString__MAX_LEN) <= 0)
        return true;
    else
        return false;
}

#pragma mark - conversion operators

CSString::operator const char *() const
{
    return c_str();
}
CSString::operator std::string() const
{
    return std::string(c_str());
}

#pragma mark - Utility methods

bool CSString::have_value() const
{
    if (_str)
        return true;
    else
        return false;
}

size_t CSString::length() const
{
    return _str_len;
}

// String format
CSString &CSString::format(const char *format, ...)
{
    char *buffer;

    va_list args;
    va_start(args, format);

    vasprintf(&buffer, format, args);
    copy_str(buffer);
    free(buffer);

    return *this;
}

// trim leading and trailing spaces
CSString &CSString::trim()
{
    const static char *whitespace = "\x20\x1b\t\r\n\v\b\f\a";

    if (!have_value())
        return *this;

    size_t begin = 0;
    size_t end = length() - 1;

    for (begin = 0; begin <= end; ++begin)
    {
        if (strchr(whitespace, _str[begin]) == nullptr)
        {
            break;
        }
    }

    for (; end > begin; --end)
    {
        if (strchr(whitespace, _str[end]) == nullptr)
        {
            break;
        }
        else
        {
            _str[end] = '\0';
        }
    }

    if (begin)
    {
        for (size_t i = 0; _str[i]; ++i)
        {
            _str[i] = _str[begin++];
        }
    }
    _str_len = strlen(_str);
    return *this;
}

const char &CSString::last_char() const
{
    return _str[length() - 1];
}

const std::vector<CSString> CSString::split(const char *match) const
{
    return split(match, -1);
}

const std::vector<CSString> CSString::split(const char *match, int max_split) const
{
    std::vector<CSString> rv;
    if (length() < 1)
        return rv;

    size_t match_len = strnlen(match, __CSString__MAX_LEN);
    if (match_len >= __CSString__MAX_LEN)
        return rv;

    char *mi;          // match index
    char *pstr = _str; // string pointer
    while ((mi = strstr(pstr, match)) && (max_split < 0 || --max_split))
    {
        if (mi != pstr)
        {
            size_t lhsz = mi - pstr;
            char *cslhs = (char *)malloc(lhsz + 1);
            cslhs[lhsz] = '\0';                          // strncpy doesn't terminate it
            rv.emplace_back(strncpy(cslhs, pstr, lhsz)); // calls CSString copy ctor
            pstr += lhsz;
            free(cslhs);
        }
        pstr += match_len;
    }

    if (*pstr != '\0')
    {
        rv.emplace_back(pstr);
    }
    return rv;
}

const CSString &CSString::char_repl(const char &match, const char &repl)
{
    for (size_t i = 0; _str[i]; ++i)
    {
        if (_str[i] == match)
            _str[i] = repl;
    }
    return *this;
}

#pragma mark - function overloads

CSString operator+(const CSString &lhs, const CSString &rhs)
{
    CSString rs = lhs;
    rs += rhs;
    return rs;
}