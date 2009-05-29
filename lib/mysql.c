#include "db.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <mysql.h>

static MYSQL mysql;

void connect_db(const char* db) {
  MYSQL* conn = 
    mysql_real_connect(
      &mysql,
      NULL,
      "root",
      NULL,
      db,
      0,
      "/opt/local/var/run/mysql5/mysqld.sock",
      0
    );
  
  if(conn == NULL) {
    fprintf(stderr, "error connecting to mysql: %s\n", mysql_error(&mysql));
    exit(EXIT_FAILURE);
  }
}

void disconnect_db() {
  mysql_close(&mysql);
}

void stresc(char* to, const char* restrict from) {
  mysql_real_escape_string(&mysql, to, from, strlen(from));
}

int select_str(char* buf, const char* stmt) {
  MYSQL_RES* res;
  MYSQL_ROW row;
    
  if(query(stmt) == 0) {
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);

    if(row == NULL) {
      mysql_free_result(res);
      return 1;
    }
    else {
      strcpy(buf, row[0]);
      mysql_free_result(res);
      return 0;
    }
  }
  else {
    return 2;
  }
}

void parse_db_time(struct tm* buf, const char* str) {
  // 2009-05-20 18:57:18
  char tmp[5];
  
  strncpy(tmp, str, 4);
  tmp[4] = '\0';
  buf->tm_year = atoi(tmp) - 1900;
  
  strncpy(tmp, str+5, 2);
  tmp[2] = '\0';
  buf->tm_mon = atoi(tmp) - 1;
  
  strncpy(tmp, str+8, 2);
  buf->tm_mday = atoi(tmp);
  
  strncpy(tmp, str+11, 2);
  buf->tm_hour = atoi(tmp);
  
  strncpy(tmp, str+14, 2);
  buf->tm_min = atoi(tmp);
  
  strncpy(tmp, str+17, 2);
  buf->tm_sec = atoi(tmp);
}

void make_db_time(char* buf, const struct tm* tm) {
  strftime(buf, 20, "%Y-%m-%d %H:%M:%S", tm);
}

int query(const char* stmt) {
  return mysql_query(&mysql, stmt);
}

unsigned long last_insert_id() {
  return mysql_insert_id(&mysql);
}

int select_model(void* model, const char* stmt, void (*map_row)(void*, char**)) {
  MYSQL_RES* res;
  MYSQL_ROW row;
    
  if(query(stmt) == 0) {
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);
    
    if(row == NULL) {
      mysql_free_result(res);
      return 1;
    }
    else {
      (*map_row)(model, (char**)row);
      
      mysql_free_result(res);
      return 0;
    }
  }
  else {
    return 2;
  }
}

int select_all_models(void* models, const char* stmt, void (*map_row)(void*, char**), int struct_size, int limit) {
  MYSQL_RES* res;
  MYSQL_ROW row;
  int i = 0;
  
  if(query(stmt) == 0) {
    res = mysql_use_result(&mysql);

    while((row = mysql_fetch_row(res)) && i < limit) {
      (*map_row)((char*)models+(i*struct_size), (char**)row);
      
      i++;
    }
    
    mysql_free_result(res);
    return 0;
  }
  else {
    return 1;
  }
}

int insert_model(void* model, const char* stmt) {
  struct model* m = model;
  
  if(query(stmt) == 0) {
    m->id_ul = last_insert_id();
    sprintf(m->id, "%lu", m->id_ul);
    return 0;
  }
  else {
    return 1;
  }
}

void set_model_id(void* model, const char* id) {  
  struct model* m = model;
  
  strcpy(m->id, id);
  m->id_ul = strtoul(id, NULL, 10);
}
