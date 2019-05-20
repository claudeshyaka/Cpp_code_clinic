// main.cpp
// Test bed for CSLib
// reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#include <cstdio>
#include <vector>
#include <memory>
#include <map>
#include "CSUnitTest.h"
#include "CSString.h"

int main(int argc, const char *argv[])
{
    printf("CSUnitTest version: %s\n", CSUnitTest::version());
    printf("CSString version: %s\n", CSString::version());

    // CSString
    printf("\nTesting CSString -----\n\n");
    CSUnitTest u("CSString");

    const char *_ctest = "   \tfoo   \r\n";
    CSString ttest = _ctest;
    u.test("cstring ctor", ttest.length() == 12);
    ttest.trim();
    u.test("trim", ttest.length() == 3);

    u.report();

    return 0;
}