#include "request.h"

#include <fcgi_stdio.h>
#include <string.h>

#include "lib/response.h"
#include "controllers/user_controller.h"

struct cookie {
  char name[32];
  char value[256];
  struct cookie* next;
};

static struct cookie* head_cookie;

void free_cookie_list() {
  struct cookie* c = head_cookie;
  struct cookie* oldc;
  
  while(c != NULL) {
    oldc = c;
    c = c->next;
    free(oldc);
  }
  
  head_cookie = NULL;
}

void make_cookie_list() {
  char* ptr = getenv("HTTP_COOKIE");
  char* term;
  struct cookie* new_cookie;
  int length;
  
  free_cookie_list();
  
  while(*ptr != '\0') {
    new_cookie = (struct cookie*)malloc(sizeof(struct cookie));
    
    // copy name portion into struct
    term = strchr(ptr, '=');
    length = ptr + (term - ptr);
    strncpy(new_cookie->name, ptr, length+1);
    new_cookie->name[length] = '\0';
    ptr += length + 1;
    
    // copy value portion into struct
    term = strchr(ptr, ';');
    if(term == NULL) {
      term = strchr(ptr, '\0');
    }
    length = ptr + (term - ptr);
    strncpy(new_cookie->value, ptr, length+1);
    new_cookie->value[length] = '\0';
    ptr += length;
    
    // add struct to linked list
    new_cookie->next = head_cookie;
    head_cookie = new_cookie;
    
    // skip over delimiter and whitespace
    if(*ptr == ';') {
      ptr++;
    }
    while(*ptr == ' ') {
      ptr++;
    }
  }
}

char* get_cookie(const char* name) {
  struct cookie* c = head_cookie;
  
  while(c != NULL) {
    if(strcmp(c->name, name) == 0) {
      return c->value;
    }
    c = c->next;
  }
  
  return NULL;
}

void route_request() {
  char* uri = getenv("REQUEST_URI");
  
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
    print_404();
  }
}
