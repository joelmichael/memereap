#ifndef db_h
#define db_h

#include <time.h>

void connect_db(const char* db);

void escape_str(char* to, const char* restrict from);

int select_str(char* buf, const char* stmt);

void parse_db_time(struct tm* buf, const char* str);

void make_db_time(char* buf, const struct tm* tm);

int query(const char* stmt);

unsigned long last_insert_id();

#endif
