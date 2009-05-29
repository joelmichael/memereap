#ifndef user_h
#define user_h

#include <time.h>

struct user {
  char id[32];
  unsigned long id_ul;
  char login[24];
  char login_esc[24];
  char created_at[32];
  struct tm created_at_tm;
};

// selects

int select_user(struct user* user, const char* stmt);

int select_all_users(struct user* users, const char* stmt, int limit);

int select_user_by_id(struct user* user, const char* id);

int select_user_by_login(struct user* user, const char* login);

// change attributes

void set_user_id(struct user* user, const char* id);

void set_user_login(struct user* user, const char* login);

void set_user_created_at(struct user* user, const char* created_at_str);

// writes

int insert_user(struct user* user);

int update_user(struct user* user);

int delete_user(const char* id);

#endif
