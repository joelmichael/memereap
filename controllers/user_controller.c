#include "models/user.h"
#include <stdio.h>
#include <stdlib.h>

void show_user() {
  struct user user;
  int id = atoi(params("id"));
  
  printf("Content-type: text/plain\n\n");
  
  if(select_user(&user, id) == 0) {  
    printf("login: %s\n", user.login);
  }
  else {
    printf("could not find user id %d\n", id);
  }
}
