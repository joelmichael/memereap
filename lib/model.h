#ifndef model_h
#define model_h

#include <mysql.h>

int select_model(void* model, const char* stmt, void (*map_row)(void*, MYSQL_ROW));

#endif
