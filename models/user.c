#include "models/user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "lib/db.h"
#include "lib/model.h"

static void map_row(void* model, MYSQL_ROW row) {
  struct user* user = model;
  
  user->id = atoi(row[0]);
  strcpy(user->id_str, row[0]);
  strcpy(user->login, row[1]);
  escape_str(user->login_esc, row[1]);
  parse_db_time(&user->created_at, row[2]);
  strcpy(user->created_at_str, row[2]);
}

int select_user(struct user* user, const char* stmt) {
  return select_model(user, stmt, map_row);
}

int select_all_users(struct user* users, const char* stmt, int limit) {
  return select_all_models(users, sizeof(struct user), stmt, map_row, limit);
}

int insert_user(struct user* user) {
  char stmt[256];
  char escaped_login[sizeof(user->login)*2+1];
  
  escape_str(escaped_login, user->login);
  
  sprintf(stmt, "insert into users (login) values ('%s')", escaped_login);
  
  if(query(stmt) == 0) {
    user->id = mysql_insert_id(&mysql);
    return 0;
  }
  else {
    return 1;
  }
}

int update_user(struct user* user) {
  sprintf(sb, "update users set login = '%s' where id = %d", user->login_esc, user->id);
  return query(sb);
}

int delete_user(int id) {  
  sprintf(sb, "delete from users where id = %d", id);
  return query(sb);
}

int select_user_by_id(struct user* user, int id) {  
  sprintf(sb, "select * from users where id = %d", id);
  return select_user(user, sb);
}

int select_user_by_login(struct user* user, const char* login) {
  char escaped[32];
  escape_str(escaped, login);
  sprintf(sb, "select * from users where login = '%s'", escaped);
  return select_user(user, sb);
}
