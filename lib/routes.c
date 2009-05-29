#include "routes.h"

#include <stdio.h>
#include <string.h>

#include "lib/response.h"
#include "controllers/user_controller.h"

void route(const char* host, const char* uri, const char* method, const char* referer) {
  if(strstr(uri, "/users/new") == uri) {
    //handle_new_user(method);
  }
  else if(strstr(uri, "/users/edit/") == uri) {
    //handle_edit_user(uri+12, method);
  }
  else if(strstr(uri, "/users/") == uri) {
    handle_show_user(uri+7);
  }
  else if(strstr(uri, "/users/delete/") == uri) {
    //handle_delete_user(uri+14);
  }
  else {
    set_response_code(404);
    print_headers();
    printf("404 Not Found\n");
  }
}
