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
static struct param* head_param;

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
  free_param_lists();
  make_cookie_list();
  route_request();
}

int add_param(char* name, char* value) {
  struct param* new_param;
  
  if(get_param(name) != 0) {
    return 1;
  }
  else {
    new_param = (struct param*)malloc(sizeof(struct param));
    strcpy(new_param->name, name);
    strcpy(new_param->value, value);
    new_param->next = head_param;
    head_param = new_param;
    return 0;
  }
}

int get_param(char* buf, const char* name) {
  struct param* p = head_param;
  
  while(p != NULL) {
    if(strcpy(p->name, name) == 0) {
      strcpy(buf, p->value);
      return 0;
    }
    p = p->next;
  }
  
  return 1;
}

void free_param_lists() {
  // frees both cookies and params
  struct param* p = head_param;
  struct param* oldp;
  
  while(p != NULL) {
    oldp = p;
    p = p->next;
    free(oldp);
  }
  
  p = head_cookie;
  
  while(p != NULL) {
    oldp = p;
    p = p->next;
    free(oldp);
  }
  
  head_param = NULL;
}
