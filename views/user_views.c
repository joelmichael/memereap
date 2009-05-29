#include "views/user_views.h"

#include <stdio.h>
#include <stdlib.h>

#include "lib/template.h"
#include "lib/response.h"

static struct tcache show_user_tc;

void print_show_user(struct user user) {
  print_headers();
  
  use_template(&show_user_tc, "users/show_user.html");
  
  add_tvar("id", user.id_str);
  add_tvar("login", user.login);
  add_tvar("created_at", user.created_at_str);
  
  print_template(show_user_tc);
}
