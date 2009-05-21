#include "user.h"
#include <stdio.h>
#include <string.h>

int select_user(struct user* user, const int id) {
  char stmt[256];
  MYSQL_RES* res;
  MYSQL_ROW row;
  
  sprintf(stmt, "select * from users where id = %d", id);
  
  if(mysql_query(&mysql, stmt) == 0) {
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);
    
    if(row == NULL) {
      mysql_free_result(res);
      return 1;
    }
    else {
      user->id = id;
      strcpy(user->login, row[1]);
      parse_mysql_time(&user->created_at, row[2]);
      mysql_free_result(res);
      return 0;
    }
  }
  else return 2;
}

int insert_user(struct user* user) {
  char stmt[256];
  
  sprintf(stmt, "insert into users (login) values ('%s')", user->login);
  
  if(mysql_query(&mysql, stmt) == 0) {
    user->id = mysql_insert_id(&mysql);
    return 0;
  }
  else return 1;
}

int update_user(struct user* user) {
  char stmt[256];
  
  sprintf(stmt, "update users set login = '%s' where id = %d", user->login, user->id);
  
  return mysql_query(&mysql, stmt);
}

int delete_user(const int id) {
  char stmt[256];
  
  sprintf(stmt, "delete from users where id = %d", id);
  
  return mysql_query(&mysql, stmt);
}
