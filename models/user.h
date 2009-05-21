#ifndef _user_h
#define _user_h

#include "db.h"

struct user {
  int id;
  char login[256];
  struct tm created_at;
};

int select_user(struct user* user, const int id);

int insert_user(struct user* user);

int update_user(struct user* user);

int delete_user(const int id);

#endif