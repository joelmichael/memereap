#ifndef routes_c
#define routes_c

#include <string.h>

#include "controllers/user_controller.c"

void route(const char* request_uri) {
  if(strstr(request_uri, "/users/") == request_uri) {
    show_user(atoi(request_uri+7));
  }
}

#endif