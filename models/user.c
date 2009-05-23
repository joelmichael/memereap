#ifndef user_c
#define user_c

#include "lib/model.c"

struct user {
  int id;
  char login[24];
  struct tm created_at;
};

static void map_row(void* model, MYSQL_ROW row) {
  struct user* user = model;
  
  user->id = atoi(row[0]);
  strcpy(user->login, row[1]);
  parse_mysql_time(&user->created_at, row[2]);
}

int select_user(struct user* user, const char* stmt) {
  return select_model(user, stmt, map_row);
}

int insert_user(struct user* user) {
  char stmt[256];
  char escaped_login[sizeof(user->login)*2+1];
  
  escape_str(escaped_login, user->login);
  
  sprintf(stmt, "insert into users (login) values ('%s')", escaped_login);
  
  if(mysql_query(&mysql, stmt) == 0) {
    user->id = mysql_insert_id(&mysql);
    return 0;
  }
  else return 1;
}

int update_user(struct user* user) {
  char stmt[256];
  char escaped_login[sizeof(user->login)*2+1];
  
  escape_str(escaped_login, user->login);
  
  sprintf(stmt, "update users set login = '%s' where id = %d", escaped_login, user->id);
  
  return mysql_query(&mysql, stmt);
}

int delete_user(const int id) {
  char stmt[256];
  
  sprintf(stmt, "delete from users where id = %d", id);
  
  return mysql_query(&mysql, stmt);
}

int select_user_by_id(struct user* user, const int id) {
  char stmt[256];
  
  sprintf(stmt, "select * from users where id = %d", id);
  
  return select_user(user, stmt);
}

int select_user_by_login(struct user* user, const char* login) {
  char stmt[256];
  char escaped[32];
  
  escape_str(escaped, login);
  
  sprintf(stmt, "select * from users where login = '%s'", escaped);
  
  return select_user(user, stmt);
}

#endif
