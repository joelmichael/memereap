#ifndef user_views_h
#define user_views_h

#include "models/user.h"

#define use_template(tcache, filename) if(tcache == NULL) tcache = cache_template(filename)

void print_show_user(struct user user);

#endif
