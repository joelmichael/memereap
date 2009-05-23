#include "controllers/user_controller.h"

#include <stdio.h>

#include "lib/response.h"
#include "models/user.h"

void show_user(int id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {  
    print_headers();
    printf("login: %s\n", user.login);
  }
  else {
    set_response_code(404);
    print_headers();
    printf("could not find user id %d\n", id);
  }
}
