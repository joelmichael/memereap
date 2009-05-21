#ifndef user_controller_c
#define user_controller_c

#include <stdio.h>
#include <stdlib.h>

#include "models/user.c"

void show_user(int id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {  
    printf("login: %s\n", user.login);
  }
  else {
    printf("could not find user id %d\n", id);
  }
}

#endif
