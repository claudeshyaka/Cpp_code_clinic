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
#include "CSNumber.h"
#include "CSKV.h"

const char *const database_filename = "test_database.db";

int main(int argc, const char *argv[])
{

    std::unique_ptr<CSKV> db(new CSKV(database_filename));
    int counter = 0;

    printf("CSUnitTest version: %s\n", CSUnitTest::version());

    printf("CSString Version: %s\n", CSString::version());
    printf("CSNumber version: %s\n", CSNumber::version());
    printf("CSDB version: %s\n", CSDB::version());
    printf("CSKV version: %s\n", CSKV::version());
    printf("SQLite version: %s\n", db->get_query_value("SELECT sqlite_version()").c_str());
    printf("CSKV table version: %s\n", db->get_query_value("SELECT value FROM kv WHERE key = ?", {"db_version"}).c_str());

    // CSString
    printf("\nTesting CSString -----\n\n");
    CSUnitTest u("CSString");

    const char *_ctest = "   \tfoo   \r\n";
    CSString ttest = _ctest;
    u.test("cstring ctor", ttest.length() == 12);
    ttest.trim();
    u.test("trim", ttest.length() == 3);

    u.report();

    // CSNumber
    printf("\nTesting CSNumber -----\n\n");
    u.init("CSNumber");
    CSNumber a = 1;
    CSNumber b = 2.0;
    CSNumber c = 3;

    u.test("number ctors", (double)a == 1.0 && (int)b == 2 && (int)c == 3);

    u.report();

    // CSDB & CSKV
    u.init("CSDB/KV");
    printf("\nTesting CSDB and CSKV\n");

    if (!db->status())
    {
        printf("database failed to open.\n");
        return 1;
    }

    u.test("database open", db->status());

    u.report();

    return 0;
}