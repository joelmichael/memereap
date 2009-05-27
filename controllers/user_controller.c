#include "controllers/user_controller.h"

#include <stdio.h>

#include "views/user_views.h"
#include "models/user.h"

void handle_show_user(int id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {  
    // print_headers();
    // printf("login: %s\n", user.login);
    print_show_user(user);
  }
  else {
    // set_response_code(404);
    // print_headers();
    // printf("could not find user id %d\n", id);
    print_404();
  }
}

