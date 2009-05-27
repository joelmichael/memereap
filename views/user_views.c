#include "views/user_views.h"

#include <stdio.h>
#include <stdlib.h>

#include "lib/template.h"
#include "lib/response.h"

static struct tcache show_user_tc;

void print_show_user(struct user user) {
  struct tvar tvars[3];
  char* parsed;
  
  define_tvar(&tvars[0], "id", user.id_str);
  define_tvar(&tvars[1], "login", user.login);
  define_tvar(&tvars[2], "created_at", user.created_at_str);
  
  if(show_user_tc.length == 0) {
    cache_template(&show_user_tc, "users/show_user.html");
  }
  
  parsed = parse_template(show_user_tc, tvars, sizeof(tvars) / sizeof(struct tvar));
  
  print_headers();
  printf("%s", parsed);
  
  free(parsed);
}
