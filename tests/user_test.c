#include <fcgi_stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "scythe/db.h"
#include "models/user.h"

void test_select_user() {
  struct user user;  
  
  assert(select_user_by_id(&user, "1") == 0);
  assert(strcmp(user.login, "aristotle") == 0);
  assert(user.created_at_tm.tm_year == 2009 - 1900);
  
  assert(select_user_by_login(&user, "aristotle") == 0);
  assert(user.id_ul == 1);
  
  assert(select_user_by_id(&user, "2") == -1);
  assert(strcmp(user.login, "aristotle") == 0);
}

void test_insert_user() {
  struct user user;
  
  set_user_login(&user, "plato");
  
  assert(insert_user(&user) == 0);
  assert(user.id_ul == 2);
  assert(insert_user(&user) == -1);
}

void test_select_all_users() {
  struct user users[2];  
  
  assert(select_all_users(users, "select * from users", 2) == 0);
  
  assert(users[0].id_ul == 1);
  assert(strcmp(users[0].login, "aristotle") == 0);
  assert(users[0].created_at_tm.tm_year == 2009 - 1900);
    
  assert(users[1].id_ul == 2);
  assert(strcmp(users[1].login, "plato") == 0);
}

void test_update_user() {
  struct user user;
  
  select_user_by_id(&user, "2");
  set_user_login(&user, "socrates");
  assert(update_user(&user) == 0);
  set_user_login(&user, "kant");
  select_user_by_id(&user, "2");
  assert(strcmp(user.login, "socrates") == 0);
}

void test_delete_user() {
  struct user user;
  
  assert(delete_user("2") == 0);
  assert(select_user_by_id(&user, "2") == -1);
}

int main(int argc, char** argv) {
  connect_db("memereap_test");
  
  test_select_user();
  test_insert_user();
  test_select_all_users();
  test_update_user();
  test_delete_user();
  
  disconnect_db();
  
  return EXIT_SUCCESS;
}
