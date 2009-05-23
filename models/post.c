#ifndef post_c
#define post_c

#include "lib/model.c"

struct post {
  int id;
  int user_id;
  char body[256];
  struct tm created_at;
};

static int map_row(void* model, MYSQL_ROW row) {
  struct post* post = model;
  
  post->id = atoi(row[0]);
  post->user_id = atoi(row[1]);
  strcpy(post->body, row[2]);
}

// int select_post(struct post* post, const char* stmt) {
//   MYSQL_RES* res;
//   MYSQL_ROW row;
// 
//   if(mysql_query(&mysql, stmt) == 0) {
//     res = mysql_use_result(&mysql);
//     row = mysql_fetch_row(res);
// 
//     if(row == NULL) {
//       mysql_free_result(res);
//       return 1;
//     }
//     else {
//       post->id = atoi(row[0]);
//       post->user_id = atoi(row[1]);
//       strcpy(post->body, row[2]);
//       parse_mysql_time(&post->created_at, row[3]);
// 
//       mysql_free_result(res);
//       return 0;
//     }
//   }
//   else return 2;
// }

int insert_post(struct post* post) {
  char stmt[256];
  char escaped_body[sizeof(post->body)*2+1];
  
  escape_str(escaped_body, post->body);
  
  sprintf(stmt, "insert into posts (user_id, body) values (%d, '%s')", post->user_id, escaped_body);
  
  if(mysql_query(&mysql, stmt) == 0) {
    post->id = mysql_insert_id(&mysql);
    return 0;
  }
  else return 1;
}

int update_post(struct post* post) {
  char stmt[256];
  char escaped_body[sizeof(post->body)*2+1];
  
  escape_str(escaped_body, post->body);
  
  sprintf(stmt, "update posts set user_id = %d, body = '%s' where id = %d",
          post->user_id, escaped_body, post->id);
  
  return mysql_query(&mysql, stmt);
}

int delete_post(const int id) {
  char stmt[256];
  
  sprintf(stmt, "delete from posts where id = %d", id);
  
  return mysql_query(&mysql, stmt);
}

int select_post_by_id(struct post* post, const int id) {
  char stmt[256];
  
  sprintf(stmt, "select * from posts where id = %d", id);
  
  return select_model(post, stmt);
}

#endif