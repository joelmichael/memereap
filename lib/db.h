#ifndef db_h
#define db_h

#include <time.h>

// all standard model structs should start with these two variables
struct model {
  char id[32];
  unsigned long id_ul;
};

// handy generic statement buffer
char stbf[2048];

// handy generic buffer for escaping select conditions
char esc[512][16];

void connect_db(const char* db);

void disconnect_db();

void stresc(char* to, const char* restrict from);

int query(const char* stmt);

unsigned long last_insert_id();

void parse_db_time(struct tm* buf, const char* str);

void make_db_time(char* buf, const struct tm* tm);

int select_str(char* buf, const char* stmt);

int select_model(void* model, const char* stmt, void (*map_row)(void*, char**));

int select_all_models(void* models, const char* stmt, void (*map_row)(void*, char**), int struct_size, int limit);

int insert_model(void* model, const char* stmt);

void set_model_id(void* model, const char* id);

#endif
