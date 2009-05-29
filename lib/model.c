#include "lib/model.h"

#include "lib/db.h"

int select_model(void* model, const char* stmt, void (*map_row)(void*, MYSQL_ROW)) {
  MYSQL_RES* res;
  MYSQL_ROW row;
    
  if(mysql_query(&mysql, stmt) == 0) {
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);
    
    if(row == NULL) {
      mysql_free_result(res);
      return 1;
    }
    else {
      (*map_row)(model, row);
      
      mysql_free_result(res);
      return 0;
    }
  }
  else {
    return 2;
  }
}

int select_all_models(void* models, int struct_size, const char* stmt, void (*map_row)(void*, MYSQL_ROW), int limit)
{
  MYSQL_RES* res;
  MYSQL_ROW row;
  int i = 0;
  
  if(mysql_query(&mysql, stmt) == 0) {
    res = mysql_use_result(&mysql);

    while((row = mysql_fetch_row(res)) && i < limit) {
      (*map_row)((char*)models+(i*struct_size), row);
      
      i++;
    }
    
    mysql_free_result(res);
    return 0;
  }
  else {
    return 1;
  }
}
