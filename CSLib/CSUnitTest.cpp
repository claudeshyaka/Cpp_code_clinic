// A simple unit test class
// Reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#include "CSUnitTest.h"

CSUnitTest::CSUnitTest(const char *test_str)
{
    init(test_str);
}

void CSUnitTest::init(const char *test_str)
{
    _test_str = test_str;
    _pass_count = _fail_count = 0;
}

void CSUnitTest::test(const char *description, const int flag)
{
    const char *pass_fail_str = nullptr;
    if (flag)
    {
        pass_fail_str = _pass_str;
        ++_pass_count;
    }
    else
    {
        pass_fail_str = _fail_str;
        ++_fail_count;
    }
    printf("%s: %s -> %s\n", _test_str, description, pass_fail_str);
}

void CSUnitTest::report() const
{
    printf("%s: pass: %ld, fail: %ld\n", _test_str, _pass_count, _fail_count);
}