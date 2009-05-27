#include "controllers/user_controller.h"

#include <stdio.h>

#include "lib/response.h"
#include "views/user_views.h"
#include "models/user.h"

void handle_show_user(int id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {  
    print_show_user(user);
  }
  else {
    print_404();
  }
}

