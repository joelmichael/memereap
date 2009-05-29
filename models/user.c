#include "models/user.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/db.h"

// selects

static void map_row(void* model, char** row) {  
  set_user_id(model, row[0]);
  set_user_login(model, row[1]);
  set_user_created_at(model, row[2]);
}

int select_user(struct user* user, const char* stmt) {
  return select_model(user, stmt, map_row);
}

int select_all_users(struct user* users, const char* stmt, int limit) {
  return select_all_models(users, sizeof(struct user), stmt, map_row, limit);
}

int select_user_by_id(struct user* user, const char* id) {  
  sprintf(stbf, "select * from users where id = %s", id);
  return select_user(user, stbf);
}

int select_user_by_login(struct user* user, const char* login) {
  escape_str(esc[0], login);
  sprintf(stbf, "select * from users where login = '%s'", esc[0]);
  return select_user(user, stbf);
}

// change attributes

void set_user_id(struct user* user, const char* id) {
  strcpy(user->id, id);
  user->id_ul = strtoul(id, NULL, 10);
}

void set_user_login(struct user* user, const char* login) {
  strcpy(user->login, login);
  escape_str(user->login_esc, login);
}

void set_user_created_at(struct user* user, const char* created_at) {
  strcpy(user->created_at, created_at);
  parse_db_time(&user->created_at_tm, created_at);
}

// writes

int insert_user(struct user* user) {
  sprintf(stbf, "insert into users (login) values ('%s')", user->login_esc);
  
  if(query(stbf) == 0) {
    sprintf(insid, "%lu", last_insert_id());
    set_user_id(user, insid);
    return 0;
  }
  else {
    return 1;
  }
}

int update_user(struct user* user) {
  sprintf(stbf, "update users set login = '%s' where id = %s", user->login_esc, user->id);
  return query(stbf);
}

int delete_user(const char* id) {  
  sprintf(stbf, "delete from users where id = %s", id);
  return query(stbf);
}
