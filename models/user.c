#include "user.h"

#include <fcgi_stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scythe/db.h"

// static

static void map_row(void* model, char** row) {
  set_model_id(model, row[0]);
  set_user_login(model, row[1]);
  set_user_created_at(model, row[2]);
}

// selects

int select_user(struct user* user, const char* stmt) {
  return select_model(user, stmt, map_row);
}

int select_all_users(struct user* users, const char* stmt, int limit) {
  return select_all_models(users, stmt, map_row, sizeof(struct user), limit);
}

int select_user_by_id(struct user* user, const char* id) {  
  sprintf(stbf, "select * from users where id = %s", id);
  return select_user(user, stbf);
}

int select_user_by_login(struct user* user, const char* login) {
  stresc(esc[0], login);
  sprintf(stbf, "select * from users where login = '%s'", esc[0]);
  return select_user(user, stbf);
}

// attributes

void set_user_login(struct user* user, const char* login) {
  strcpy(user->login, login);
  stresc(user->login_esc, login);
}

void set_user_created_at(struct user* user, const char* created_at) {
  strcpy(user->created_at, created_at);
  parse_db_time(&user->created_at_tm, created_at);
}

// writes

int insert_user(struct user* user) {
  sprintf(stbf, "insert into users (login) values ('%s')", user->login_esc);
  return insert_model(user, stbf);
}

int update_user(struct user* user) {
  sprintf(stbf, "update users set login = '%s' where id = %s", user->login_esc, user->id);
  return query(stbf);
}

int delete_user(const char* id) {  
  sprintf(stbf, "delete from users where id = %s", id);
  return query(stbf);
}
