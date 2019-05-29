// CSDB.h
// A simple database wrapper for SQLite
// reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#ifndef __CSLib__CSDB__
#define __CSLib__CSDB__

#include <vector>
#include <map>
#include <memory>
#include <cstdlib>
#include <sqlite3.h>
#include "CSString.h"

#define __CSDB_VERSION "1.0.0"

class CSDB
{
private:
    typedef std::map<CSString, CSString> row;
    row *rowp = nullptr;

    const char *_filename = nullptr; // database filename
    sqlite3 *_dbh = nullptr;         // database handle
    sqlite3_stmt *stmt = nullptr;    //sqlite3 statement handle

    CSString _value; // Simple smart string
    bool db_okay;    // true if handle is okay;

    // rule of three
    CSDB(CSDB &);           // no copy constructor
    CSDB operator=(CSDB &); // no assignment operator
    CSDB();                 // no default constructor

protected:
    void _finalize();               // statement finalize
    void _set_value(const char *);  // setter
    const char *_get_value() const; // getter
    void _clear_value();            // free
    void _clear_row();

    void get_column(int);

public:
    typedef row dbrow;
    static const char *version() { return __CSDB_VERSION; }

    CSDB(const char *n); // ctor with filename
    ~CSDB();             // destructor

    bool status(); // get database status

    const char *filename() const; // filename getter
    const sqlite3 *dbh() const;   // database handle getter
    void close();

    const char *get_error() const;
    const int error_code() const;
    bool have_error() const;

    long count(const CSString &);
    bool table_exists(const CSString &);
    bool do_query(const char *);
    bool do_query(const CSString &);
    bool do_query(const CSString &, const std::vector<CSString> &);

    CSString get_query_value(const CSString &);
    CSString get_query_value(const CSString &, const std::vector<CSString> &);

    bool prepare_query(const CSString &, const std::vector<CSString> &);
    const dbrow *get_prepared_row();
    CSString get_prepared_value();
};

#endif // define(__CSLib__CSDB__)
