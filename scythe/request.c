#include "request.h"

#include <fcgi_stdio.h>
#include <string.h>
#include <stdlib.h>

#include "scythe/response.h"
#include "scythe/routes.h"

struct param {
  char name[32];
  char value[256];
  struct param* next;
};

static struct param* head_cookie;
static struct param* head_param;

void process_request() {
  make_cookie_list();
  route_request();
  free_params_and_cookies();
}

void make_cookie_list() {
  char* ptr = getenv("HTTP_COOKIE");
  char* term;
  struct param* new_cookie;
  int len;
    
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

char* cookie(char* name) {
  struct param* c = head_cookie;
  
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
  struct route* route = determine_route(uri);
  
  if(route != NULL) {
    set_params_for_route(route, uri);
    (*route->action)();
  }
  else {
    print_404();
  }
}

int set_param(char* name, char* value) {
  struct param* new_param;
  
  if(param(name) != NULL) {
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

char* param(char* name) {
  struct param* p = head_param;
  
  while(p != NULL) {
    if(strcmp(p->name, name) == 0) {
      return p->value;
    }
    p = p->next;
  }
  
  return NULL;
}

void free_params_and_cookies() {
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
