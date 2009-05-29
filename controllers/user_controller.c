#include "controllers/user_controller.h"

#include <stdio.h>

#include "lib/response.h"
#include "lib/template.h"
#include "models/user.h"

static struct tcache* show_user_tcache;

void handle_show_user(int id) {
  struct user user;
    
  if(select_user_by_id(&user, id) == 0) {    
    print_headers();
    
    if(show_user_tcache == NULL) {
      show_user_tcache = cache_template("users/show_user.html");
    }
    
    add_tvar("id", user.id_str);
    add_tvar("login", user.login);
    add_tvar("created_at", user.created_at_str);

    print_tcache(show_user_tcache);
  }
  else {
    print_404();
  }
}
