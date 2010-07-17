#include "user_controller.h"

#include "lib/request.h"
#include "lib/response.h"
#include "models/user.h"
#include "views/user_views.h"

void handle_show_user() {
  const char* id = param("id");
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {
    print_show_user(user);
  }
  else {
    print_404();
  }
}
