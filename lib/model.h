#ifndef model_h
#define model_h

#include <mysql.h>

// handy generic statement buffer
char sb[256];

int select_model(void* model, const char* stmt, void (*map_row)(void*, MYSQL_ROW));

int select_all_models(void* models, int struct_size, const char* stmt, void (*map_row)(void*, MYSQL_ROW), int limit);

#endif
