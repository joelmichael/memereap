#include "routes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/response.h"
#include "controllers/user_controller.h"

void route(const char* host, const char* uri, const char* method, const char* referer) {
  if(strstr(uri, "/users/new") == uri) {
    //new_user(method);
  }
  else if(strstr(uri, "/users/edit/") == uri) {
    //edit_user(atoi(uri+12), method);
  }
  else if(strstr(uri, "/users/") == uri) {
    show_user(atoi(uri+7));
  }
  else if(strstr(uri, "/users/delete/") == uri) {
    //delete_user(atoi(uri+14));
  }
  else {
    set_response_code(404);
    print_headers();
    printf("404 Not Found\n");
  }
}
