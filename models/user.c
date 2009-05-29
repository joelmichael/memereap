#include "models/user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/db.h"

// selects

static void map_row(void* model, char** row) {
  struct user* user = model;
  
  set_user_id(user, atoi(row[0]));
  set_user_login(user, row[1]);
  set_user_created_at(user, row[2]);
}

int select_user(struct user* user, const char* stmt) {
  return select_model(user, stmt, map_row);
}

int select_all_users(struct user* users, const char* stmt, int limit) {
  return select_all_models(users, sizeof(struct user), stmt, map_row, limit);
}

int select_user_by_id(struct user* user, int id) {  
  sprintf(sb, "select * from users where id = %d", id);
  return select_user(user, sb);
}

int select_user_by_login(struct user* user, const char* login) {
  escape_str(esc[0], login);
  sprintf(sb, "select * from users where login = '%s'", esc[0]);
  return select_user(user, sb);
}

// change attributes

void set_user_id(struct user* user, int id) {
  user->id = id;
  sprintf(user->id_str, "%d", id);
}

void set_user_login(struct user* user, const char* login) {
  strcpy(user->login, login);
  escape_str(user->login_esc, login);
}

void set_user_created_at(struct user* user, const char* created_at_str) {
  parse_db_time(&user->created_at, created_at_str);
  strcpy(user->created_at_str, created_at_str);
}

// writes

int insert_user(struct user* user) {
  escape_str(esc[0], user->login);
  
  sprintf(sb, "insert into users (login) values ('%s')", esc[0]);
  
  if(query(sb) == 0) {
    set_user_id(user, last_insert_id());
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
