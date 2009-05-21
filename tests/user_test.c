#include "models/user.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

void test_select_user() {
  struct user user;  
  
  assert(select_user_by_id(&user, 1) == 0);
  assert(strcmp(user.login, "aristotle") == 0);
  assert(user.created_at.tm_year == 2009 - 1900);
  
  assert(select_user_by_login(&user, "aristotle") == 0);
  assert(user.id == 1);
  
  assert(select_user_by_id(&user, 2) == 1);
  assert(strcmp(user.login, "aristotle") == 0);
}

void test_insert_user() {
  struct user user;
  
  strcpy(user.login, "plato");
  
  assert(insert_user(&user) == 0);
  assert(user.id == 2);
  assert(insert_user(&user) == 1);
}

void test_update_user() {
  struct user user;
  
  select_user_by_id(&user, 2);
  strcpy(user.login, "socrates");
  assert(update_user(&user) == 0);
  strcpy(user.login, "kant");
  select_user_by_id(&user, 2);
  assert(strcmp(user.login, "socrates") == 0);
}

void test_delete_user() {
  struct user user;
  
  assert(delete_user(2) == 0);
  assert(select_user_by_id(&user, 2) == 1);
}

int main(int argc, char** argv) {
  connect_db("memereap_test");
  
  test_select_user();
  test_insert_user();
  test_update_user();
  test_delete_user();
  
  mysql_close(&mysql);
  
  return EXIT_SUCCESS;
}
