#include "user_views.h"

#include <fcgi_stdio.h>
#include "lib/request.h"
#include "lib/template.h"

static struct template* show_user_template;

void print_show_user(struct user user) {
  use_template(show_user_template, "users/show_user.html");
  
  add_tvar("id", user.id);
  add_tvar("login", user.login);
  add_tvar("created_at", user.created_at);

  print_template(show_user_template);
}
