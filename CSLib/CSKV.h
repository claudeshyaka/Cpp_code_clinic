// CSKV.h
// A simple key-value system using CSDB
// reference: Bill Weinman <http://bw.org>
// by Claude Shyaka

#ifndef __CSLIB__CSKV__
#define __CSLIB__CSKV__

#include "CSDB.h"

#define __CSKV_VERSION "1.0.0"

static const char *_cskv_drop_sql = "DROP TRIGGER IF EXISTS stampUpdateKv; DROP TABLE IF EXISTS kv;";
static const char *_cskv_create_table_sql = "CREATE TABLE kv (id INTEGER PRIMARY KEY, stamp TEXT DEFAULT CURRENT_TIMESTAMP, key TEXT UNIQUE NOT NULL, value TEXT);";
static const char *_cskv_create_trigger_sql = "CREATE TRIGGER stampUpdateKv BEFORE UPDATE ON kv BEGIN UPDATE kv SET stamp = DATATIME('now') WHERE kv.id = NEW.id; END;";
static const char *_cskv_insert_sql = "INSERT INTO kv (key, value) VALUES ( 'db_version', '1.0.3' );";

class CSKV : public CSDB
{
public:
    static const char *version() { return __CSKV_VERSION; }
    CSKV(const char *fn);
    const char *value(const char *key);
    bool value(const char *key, const char *value);
    const CSString operator[](const CSString &key);
    const char *operator[](const char *key);
    void del(const char *key);
    void del(const CSString &key);
};

#endif // defined(__CSLIB__CSKV__)