#ifndef db_h
#define db_h

#include <time.h>

// handy generic statement buffer
char stbf[2048];

// handy generic buffer for escaping select conditions
char esc[512][8];

// handy buffer for converting last insert id
char insid[32];

void connect_db(const char* db);

void disconnect_db();

void stresc(char* to, const char* restrict from);

int select_str(char* buf, const char* stmt);

void parse_db_time(struct tm* buf, const char* str);

void make_db_time(char* buf, const struct tm* tm);

int query(const char* stmt);

unsigned long last_insert_id();

int select_model(void* model, const char* stmt, void (*map_row)(void*, char**));

int select_all_models(void* models, int struct_size, const char* stmt, void (*map_row)(void*, char**), int limit);

#endif
