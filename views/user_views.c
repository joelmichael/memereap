#include "user_views.h"

#include <fcgi_stdio.h>
#include "lib/request.h"
#include "lib/template.h"

static struct tcache* show_user_tcache;

void print_show_user(struct user user) {
  char test[32];
  char bar[32];
  
  use_template(show_user_tcache, "users/show_user.html");
  
  add_tvar("id", user.id);
  add_tvar("login", user.login);
  add_tvar("created_at", user.created_at);

  print_tcache(show_user_tcache);
  
  get_cookie(test, "test");
  get_cookie(bar, "bar");
  
  printf("test: %s\n", test);
  printf("bar: %s\n", bar);
}
