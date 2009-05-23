#ifndef db_h
#define db_h

#include <time.h>
#include <mysql.h>

MYSQL mysql;

void connect_db(const char* db);

void escape_str(char* to, const char* restrict from);

int select_str(char* buf, const char* stmt);

void parse_mysql_time(struct tm* buf, const char* str);

void make_mysql_time(char* buf, const struct tm* tm);

#endif
