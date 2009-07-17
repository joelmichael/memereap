#include "request.h"

#include <fcgi_stdio.h>
#include <string.h>
#include <stdlib.h>

#include "lib/response.h"
#include "controllers/user_controller.h"

struct param {
  char name[32];
  char value[256];
  struct param* next;
};

static struct param* head_cookie;

void free_cookie_list() {
  struct param* c = head_cookie;
  struct param* oldc;
  
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
  struct param* new_cookie;
  int len;
  
  free_cookie_list();
  
  if(ptr == NULL) {
    return;
  }
  
  while(*ptr != '\0') {
    new_cookie = (struct param*)malloc(sizeof(struct param));
    
    // copy name portion into struct
    term = strchr(ptr, '=');
    len = term - ptr;
    strncpy(new_cookie->name, ptr, len+1);
    new_cookie->name[len] = '\0';
    ptr = term + 1;
    
    // copy value portion into struct
    term = strchr(ptr, ';');
    if(term == NULL) {
      term = strchr(ptr, '\0');
    }
    len = term - ptr;
    strncpy(new_cookie->value, ptr, len+1);
    new_cookie->value[len] = '\0';
    ptr = term;
    
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

int get_cookie(char* buf, const char* name) {
  struct param* c = head_cookie;
  
  while(c != NULL) {
    if(strcmp(c->name, name) == 0) {
      strcpy(buf, c->value);
      return 0;
    }
    c = c->next;
  }
  
  return 1;
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

void process_request() {
  make_cookie_list();
  route_request();
}
