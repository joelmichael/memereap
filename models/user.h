#ifndef user_h
#define user_h

#include <time.h>

struct user {
  int id;
  char id_str[16];
  char login[24];
  struct tm created_at;
  char created_at_str[32];
};

int select_user(struct user* user, const char* stmt);

int select_all_users(struct user* users, const char* stmt, int limit);

int insert_user(struct user* user);

int update_user(struct user* user);

int delete_user(int id);

int select_user_by_id(struct user* user, int id);

int select_user_by_login(struct user* user, const char* login);

#endif
