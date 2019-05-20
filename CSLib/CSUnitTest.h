// A simple unit test class
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#ifndef __CSLib__CSUnitTest__
#define __CSLib__CSUnitTest__

#include <cstdio>

#define __CSUnitTest_VERSION "1.0.0"

const static char *_pass_str = "pass";
const static char *_fail_str = "fail";

class CSUnitTest
{
private:
    unsigned long int _pass_count = 0;
    unsigned long int _fail_count = 0;

    const char *_test_str = nullptr;

    CSUnitTest(CSUnitTest &);           // no copy constructor
    CSUnitTest operator=(CSUnitTest &); // no assignment operator
    CSUnitTest() {}                     // no default construtor
public:
    static const char *version() { return __CSUnitTest_VERSION; }
    CSUnitTest(const char *);
    void init(const char *);
    void test(const char *, const int);
    void report() const;
};

#endif // define(__CSLib__CSUnitTest__)