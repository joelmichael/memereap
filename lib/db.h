#ifndef db_h
#define db_h

#include <time.h>

// handy generic statement buffer
char sb[1024];

// handy generic buffer for escaping inputs
char esc[512][32];

void connect_db(const char* db);

void disconnect_db();

void escape_str(char* to, const char* restrict from);

int select_str(char* buf, const char* stmt);

void parse_db_time(struct tm* buf, const char* str);

void make_db_time(char* buf, const struct tm* tm);

int query(const char* stmt);

unsigned long last_insert_id();

int select_model(void* model, const char* stmt, void (*map_row)(void*, char**));

int select_all_models(void* models, int struct_size, const char* stmt, void (*map_row)(void*, char**), int limit);

#endif
