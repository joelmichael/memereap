#ifndef post_h
#define post_h

#include <time.h>

struct post {
  int id;
  int user_id;
  char body[256];
  struct tm created_at;
};

int select_post(struct post* post, const char* stmt);

int select_all_posts(struct post* posts, const char* stmt, const int limit);

int insert_post(struct post* post);

int update_post(struct post* post);

int delete_post(const int id);

int select_post_by_id(struct post* post, const int id);

#endif