#ifndef user_h
#define user_h

#include <time.h>

struct user {
  int id;
  char id_str[16];
  char login[24];
  char login_esc[24];
  struct tm created_at;
  char created_at_str[32];
};

// selects

int select_user(struct user* user, const char* stmt);

int select_all_users(struct user* users, const char* stmt, int limit);

int select_user_by_id(struct user* user, int id);

int select_user_by_login(struct user* user, const char* login);

// modify attributes

void set_user_id(struct user* user, int id);

void set_user_login(struct user* user, const char* login);

void set_user_created_at(struct user* user, const char* created_at_str);

// writes

int insert_user(struct user* user);

int update_user(struct user* user);

int delete_user(int id);

#endif
