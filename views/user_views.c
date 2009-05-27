#include "views/user_views.h"

#include <stdio.h>
#include <stdlib.h>

#include "lib/template.h"
#include "lib/response.h"

static struct tcache show_user_tc;

void print_show_user(struct user user) {
  struct tvar tvars[1];
  char* parsed;
  
  define_tvar(tvars, "login", user.login);
  
  if(show_user_tc.length == 0) {
    cache_template(&show_user_tc, "users/show_user.html");
  }
  
  parsed = parse_template(show_user_tc, tvars, 1);
  print_headers();
  printf("%s", parsed);
  free(parsed);
}
