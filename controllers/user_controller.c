#include "user_controller.h"

#include "lib/response.h"
#include "models/user.h"
#include "views/user_views.h"

void handle_show_user(const char* id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {
    print_headers();
    print_show_user(user);
  }
  else {
    print_404();
  }
}
