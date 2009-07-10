#include "response.h"

#include <fcgi_stdio.h>
#include <string.h>
#include <stdlib.h>

static int response_code = 200;
static char content_type[32] = "text/html";
static char redirect_location[256];

struct cookie {
  char name[32];
  char value[256];
  struct cookie* next;
};

static struct cookie* head_cookie;

void print_headers() {
  struct cookie* c = head_cookie;
  struct cookie* oldc;
  
  printf("Status: ");
  
  switch(response_code) {
    case 200:
    printf("200 OK\n");
    break;
    
    case 302:
    printf("302 Found\n");
    printf("Location: %s\n", redirect_location);
    break;
    
    case 403:
    printf("403 Forbidden\n");
    
    case 404:
    printf("404 Not Found\n");
  }
  
  printf("Content-type: %s\n", content_type);
  
  while(c != NULL) {
    printf("Set-Cookie: %s=%s\n", c->name, c->value);
    oldc = c;
    c = c->next;
    free(oldc);
  }
  
  head_cookie = NULL;
    
  printf("\n");
}

void redirect_to(const char* url) {
  strcpy(redirect_location, url);
  response_code = 302;
}

void set_response_code(int code) {
  response_code = code;
}

void set_content_type(const char* type) {
  strcpy(content_type, type);
}

void print_404() {
  set_response_code(404);
  print_headers();
  printf("404 Not Found");
}

void add_cookie(const char* name, const char* value) {
  struct cookie* new_cookie;
  
  new_cookie = (struct cookie*)malloc(sizeof(struct cookie));
  
  strcpy(new_cookie->name, name);
  strcpy(new_cookie->value, value);
  
  new_cookie->next = head_cookie;
  head_cookie = new_cookie;
}
