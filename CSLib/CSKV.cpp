//  CSKV.cpp
//  As simple key-value system using CSDB
//  reference: Bill Weinman <http://bw.org/>
//  by Claude Shyaka

#include "CSKV.h"

#pragma mark - class CSKV

CSKV::CSKV(const char *fn) : CSDB(fn)
{
    if (!table_exists("kv"))
    {
        do_query(_cskv_drop_sql);
        do_query(_cskv_create_table_sql);
        do_query(_cskv_create_trigger_sql);
        do_query(_cskv_insert_sql);
    }
}

const char *CSKV::value(const char *key)
{
    get_query_value("SELECT value FROM kv WHERE key = ?", std::vector<CSString>({CSString(key)}));
    if (have_error())
        return nullptr;
    else
        return _get_value();
}

bool CSKV::value(const char *k, const char *v)
{
    CSString q;
    if (value(k))
    {
        q = "UPDATE kv SET value = ? WHERE key = ?";
    }
    else
    {
        q = "INSERT INTO kvn (value, key) VALUES(?, ?)";
    }
    std::vector<CSString> p({CSString(v), CSString(k)});
    return do_query(q, p);
}

const CSString CSKV::operator[](const CSString &key)
{
    return CSString(value(key.c_str()));
}

const char *CSKV::operator[](const char *key)
{
    return value(key);
}

void CSKV::del(const char *key)
{
    if (value(key))
    {
        CSString q = "DELETE FROM kv WHERE key = ?";
        std::vector<CSString> p({key});
        do_query(q, p);
    }
}

void CSKV::del(const CSString &key)
{
    del(key.c_str());
}