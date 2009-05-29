#include "models/post.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>

#include "lib/db.h"
#include "lib/model.h"

static void map_row(void* model, MYSQL_ROW row) {
  struct post* post = model;
  
  post->id = atoi(row[0]);
  post->user_id = atoi(row[1]);
  strcpy(post->body, row[2]);
}

int select_post(struct post* post, const char* stmt) {
  return select_model(post, stmt, map_row);
}

int select_all_posts(struct post* posts, const char* stmt, int limit) {
  return select_all_models(posts, sizeof(struct post), stmt, map_row, limit);
}

int insert_post(struct post* post) {
  char stmt[256];
  char escaped_body[sizeof(post->body)*2+1];
  
  escape_str(escaped_body, post->body);
  
  sprintf(stmt, "insert into posts (user_id, body) values (%d, '%s')", post->user_id, escaped_body);
  
  if(mysql_query(&mysql, stmt) == 0) {
    post->id = mysql_insert_id(&mysql);
    return 0;
  }
  else {
    return 1;
  }
}

int update_post(struct post* post) {
  char stmt[256];
  char escaped_body[sizeof(post->body)*2+1];
  
  escape_str(escaped_body, post->body);
  
  sprintf(stmt, "update posts set user_id = %d, body = '%s' where id = %d",
          post->user_id, escaped_body, post->id);
  
  return mysql_query(&mysql, stmt);
}

int delete_post(int id) {
  char stmt[256];
  
  sprintf(stmt, "delete from posts where id = %d", id);
  
  return mysql_query(&mysql, stmt);
}

int select_post_by_id(struct post* post,int id) {
  char stmt[256];
  
  sprintf(stmt, "select * from posts where id = %d", id);
  
  return select_model(post, stmt);
}
