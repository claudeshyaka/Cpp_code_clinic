// CSDB.cpp
// A simple database wrapper for SQLite
// reference: Bill Weinman <http://bw.org/>
// by Claude Shyaka

#include "CSDB.h"

#pragma mark - CSDB constructors & destructors

// just one constructor -- need a filename
CSDB::CSDB(const char *fn)
{
    _filename = fn;
    int rc = sqlite3_open(_filename, &_dbh);
    if (rc == SQLITE_OK)
    {
        db_okay = true;
    }
}

// destructor closes the database
CSDB::~CSDB()
{
    this->close();
}

#pragma mark - _value setter/getters

void CSDB::_set_value(const char *s)
{
    _value = s;
}

const char *CSDB::_get_value() const
{
    if (_value.have_value())
        return _value.c_str();
    else
        return nullptr;
}

void CSDB::_clear_row()
{
    if (rowp)
    {
        delete rowp;
        rowp = nullptr;
    }
}

void CSDB::_clear_value()
{
    _value.reset();
}

#pragma mark -utilities

bool CSDB::status()
{
    return db_okay;
}

const char *CSDB::filename() const
{
    return _filename;
}

const sqlite3 *CSDB::dbh() const
{
    return _dbh;
}

void CSDB::_finalize()
{
    if (stmt)
    {
        sqlite3_finalize(stmt);
        stmt = nullptr;
    }
    _clear_row();
}

void CSDB::close()
{
    _clear_value();
    _finalize();
    if (_dbh)
        sqlite3_close(_dbh);
    db_okay = false;
    _dbh = nullptr;
}

#pragma mark - errors

const char *CSDB::get_error() const
{
    return sqlite3_errmsg(_dbh);
}

const int CSDB::error_code() const
{
    return sqlite3_errcode(_dbh);
}

bool CSDB::have_error() const
{
    int rc = error_code();

    // 0 is SQLITE_OK and 100+ are sqlite3_step() success codes
    if (rc > SQLITE_OK && rc < SQLITE_ROW)
        return true;
    else
        return false;
}

#pragma mark - queries

long CSDB::count(const CSString &table_name)
{
    CSString q = "SELECT COUNT(*) FROM ";
    q += table_name;
    CSString rc = get_query_value(q, {table_name});
    if (rc.length())
    {
        return std::stol(rc);
    }
    else
    {
        return 0L;
    }
}

bool CSDB::table_exists(const CSString &table_name)
{
    CSString rs = get_query_value("SELECT name FROM sqlite_master WHERE type = ? and name = ?", {"table", table_name});

    if (rs.have_value())
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

bool CSDB::do_query(const char *q)
{
    if (sqlite3_prepare_v2(_dbh, (char *)q, -1, &stmt, NULL) != SQLITE_OK)
    {
        _finalize();
        return false;
    }

    sqlite3_step(stmt);
    _finalize();
    return true;
}

bool CSDB::do_query(const CSString &q)
{
    return do_query(q.c_str());
}

bool CSDB::do_query(const CSString &sQuery, const std::vector<CSString> &params)
{
    const char *q = sQuery.c_str();
    if (sqlite3_prepare_v2(_dbh, q, -1, &stmt, NULL) != SQLITE_OK)
    {
        _finalize();
        return false;
    }

    for (unsigned int i = 0; i < params.size(); ++i)
    {
        sqlite3_bind_text(stmt, i + 1, params[i].c_str(), -1, SQLITE_TRANSIENT);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        _set_value((const char *)sqlite3_column_text(stmt, 0));
        _finalize();
        return true;
    }
    else
    {
        _finalize();
        return false;
    }
}

CSString CSDB::get_query_value(const CSString &q)
{
    _clear_value();
    if (sqlite3_prepare_v2(_dbh, q.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        _finalize();
        return _value;
    }
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        char *rc = (char *)sqlite3_column_text(stmt, 0);
        if (rc)
            _set_value(rc);
    }
    _finalize();
    return _value;
}

CSString CSDB::get_query_value(const CSString &sQuery, const std::vector<CSString> &vParams)
{
    _clear_value();
    if (sqlite3_prepare_v2(_dbh, sQuery, -1, &stmt, NULL) != SQLITE_OK)
    {
        _finalize();
        _get_value();
    }
    for (unsigned int i = 0; i < vParams.size(); ++i)
    {
        sqlite3_bind_text(stmt, i + 1, vParams[i].c_str, -1, SQLITE_TRANSIENT);
    }

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        char *rc = (char *)sqlite3_column_text(stmt, 0);
        if (rc)
            _set_value(rc);
    }
    _finalize();
    return _get_value();
}

bool CSDB::prepare_query(const CSString &sQuery, const std::vector<CSString> &vParams)
{
    _clear_value();
    const char *q = sQuery.c_str();
    if (sqlite3_prepare_v2(_dbh, q, -1, &stmt, NULL) != SQLITE_OK)
    {
        _finalize();
        return false;
    }
    for (unsigned int i = 0; i < vParams.size(); ++i)
    {
        sqlite3_bind_text(stmt, i + 1, vParams[i].c_str(), -1, SQLITE_TRANSIENT);
    }
    return true;
}

const CSDB::dbrow *CSDB::get_prepared_row()
{
    _clear_row();
    rowp = new (row);
    int colcount = sqlite3_column_count(stmt);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        for (int i = 0; i < colcount; ++i)
        {
            const char *colname = (const char *)sqlite3_column_name(stmt, i);
            const char *colval = (const char *)sqlite3_column_text(stmt, i);
            if (colname && colval)
            {
                rowp->insert({colname, colval});
            }
        }
        return rowp;
    }
    else
    {
        _finalize();
        return nullptr;
    }
}

CSString CSDB::get_prepared_value()
{
    _clear_value();
    rowp = new (row);
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        _value = (const char *)sqlite3_column_text(stmt, 0);
    }
    else
    {
        _finalize();
    }
    return _value;
}