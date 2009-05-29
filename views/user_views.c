#include "views/user_views.h"

#include "lib/template.h"

static struct tcache* show_user_tcache;

void print_show_user(struct user* user) {  
  if(show_user_tcache == NULL) {
    show_user_tcache = cache_template("users/show_user.html");
  }
  
  add_tvar("id", user->id_str);
  add_tvar("login", user->login);
  add_tvar("created_at", user->created_at_str);

  print_tcache(show_user_tcache);
}
